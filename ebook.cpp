#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <numeric>
#include <vector>
#include <iomanip>

using namespace std;

enum ReqType {
    CHEER,
    READ
};

ReqType GetReqType(string & input) {
    using namespace literals;
    ReqType result = ReqType::CHEER;
    int cut_count = 0;
    if (input.find("CHEER"sv) != string::npos) {
        result = ReqType::CHEER;
        cut_count = 5;
    } else if (input.find("READ"sv) != string::npos) {
        result = ReqType::READ;
        cut_count = 4;
    }
    input.erase(0, cut_count);
    return result;
}

int TakeIntAndErase (string & input) {
    auto position  = input.find_first_not_of(' ');
    input.erase(0, position);
    position = input.find_first_of(' ');
    int result = 0;
    if (position == string_view::npos) {
        result = stoi(input);
    } else {
        string s(input);
        s.resize(position);
        result = stoi(s);
        input.erase(0, position);
    }
    return result;
}

class BookReaders {
public:
    BookReaders () { }
    ~BookReaders () { }
    void Read(int user, int page) {
        if (user_pages_.size() < user) {
            user_pages_.resize(user, 0);
        }
        if (usercount_.count(user) == 0) {
            usercount_.insert(user);
        } else {
            int userpage = user_pages_.at(user-1);
            people_at_page_[userpage - 1] -= 1;
        }
        user_pages_[user-1] = page;
        if (people_at_page_.size() < page) {
            people_at_page_.resize(page, 0);
        }
        people_at_page_[page-1] += 1;
    }

    double Cheer (int user) const {
        double result = 0.;
        if (usercount_.count(user) == 0) {
            return 0;
        }
        if (usercount_.size() == 1) {
            return 1;
        }
        if (usercount_.count(user) != 0) {
            int userpage = user_pages_.at(user-1);
            result = accumulate(people_at_page_.begin(), people_at_page_.begin() + userpage - 1, 0);
            result /= usercount_.size() - 1;
        }
        return result;
    }

private:
    vector<int> user_pages_;
    vector<int> people_at_page_;
    set<int> usercount_;
};

int main (void) {
    BookReaders br;
    string request;
    getline(cin, request);
    int request_count = stoi(request);
 
    for (int i = 0; i != request_count; ++i) {
        getline(cin, request);
        const auto reqtype = GetReqType(request);
        switch (reqtype) {
            case (ReqType::CHEER): {
                cout << setprecision(6) << br.Cheer(TakeIntAndErase(request)) << endl;
                break;
            }
            case (ReqType::READ): {
                int user = TakeIntAndErase(request);
                int page = TakeIntAndErase(request);
                br.Read(user, page);
                break;
            }
        }
    }
    return 0;
}