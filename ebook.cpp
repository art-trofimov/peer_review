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

ReqType GetReqType(string& input) {
    using namespace literals;
    ReqType result = ReqType::CHEER;
    if (input.find("CHEER"sv) != string::npos) {
        result = ReqType::CHEER;
    } else if (input.find("READ"sv) != string::npos) {
        result = ReqType::READ;
    }
    return result;
}

class BookReaders {
public:
    BookReaders () { }
    ~BookReaders () { }
    void Read(size_t user, size_t page) {
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

    double Cheer (size_t user) const {
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

    void HandleRequest (istream& is, ostream& os) {
        string request;
        is >> request;
        const auto reqtype = GetReqType(request);
        size_t user;
        switch (reqtype) {
            case (ReqType::CHEER): {
                is >> user;
                os << setprecision(6) << Cheer(user) << endl;
                break;
            }
            case (ReqType::READ): {
                size_t page;
                is >> user >> page;
                Read(user, page);
                break;
            }
        }
    }
private:
    vector<int> user_pages_;
    vector<int> people_at_page_;
    set<int> usercount_;
};

int main (void) {
    BookReaders br;
    int request_count;
    cin >> request_count;
    for (int i = 0; i != request_count; ++i) {
        string request;
        getline(cin, request);
        br.HandleRequest(cin, cout);
    }
    return 0;
}