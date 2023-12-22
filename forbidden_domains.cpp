#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;
class Domain {
public:

    Domain(const string & name) : name_(name) {
        //разваорот строк чтобы сделать их суффиксами поддоменов
        reverse(name_.begin(), name_.end());  
        name_ += '.';      
    }

    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами

    // разработайте operator==
    bool operator==(const Domain& other) const {
        return name_ == other.name_;
    }

    bool operator<(const Domain& other) const { 
        return lexicographical_compare(name_.begin(), name_.end(), other.name_.begin(), other.name_.end());
    }

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain (const Domain & other) const {
        return name_.find(other.name_) == 0;
    }
private:
    string name_;
};

template <typename Iterator>
class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    DomainChecker (const Iterator begin, const Iterator end) : domain_list_(begin, end) {

        sort(domain_list_.begin(), domain_list_.end());
        auto it = unique(domain_list_.begin(), domain_list_.end()
            , [] (auto lhs, auto rhs) {
             return (lhs.IsSubdomain(rhs) || rhs.IsSubdomain(lhs));
        });
        domain_list_.erase(it, domain_list_.end());

    }

    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(const Domain& name) {  
        auto first = upper_bound(domain_list_.begin(), domain_list_.end(), name);
        if (first != domain_list_.begin()) {
            auto prev = first - 1;
            return name.IsSubdomain(*prev);
        } 
        return false;
    }
private:
    vector<Domain> domain_list_;
};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа
template <typename Number>
vector<Domain> ReadDomains (istream& input, Number num) {
    vector<Domain> result;
    string line;
    while (num--) {
        getline(input, line);
        result.push_back({line});
    }
    return result;
}

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);
    Number num;
    istringstream(line) >> num;
    return num;
}

int main() {
    const vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());
    const vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
    return 0;
}
