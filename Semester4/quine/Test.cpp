#include <iostream>

using namespace std;

string encode(const string &s);

string getCode() {
    string s = "#include <iostream>

    using namespace std;

    string encode(const string &s);

    string getCode() {
        string s = "%";
        return encode(s);
    }

    string mirror(const string &s) {
        string res;
        for (char ch : s){
            switch(ch) {
                case '\\' :
                    res += "\\\\";
                    break;
                case '\'' :
                    res += "\\'";
                    break;
                case '\"' :
                    res += "\\\"";
                    break;
                case '\n' :
                    res += "\\n";
                    break;
                case '\r' :
                    res += "\\r";
                    break;
                default:
                    res+= ch;
                    break;
            }
        }
        return res;
    }

    string encode(const string &s) {
        string res = s;
        res.replace(res.find('%'), 1, res);
        return res;
    }

    int main() {
        string s = getCode();
        cout << s;
    }";
    return encode(s);
}

string mirror(const string &s) {
    string res;
    for (char ch : s){
        switch(ch) {
            case '\\' :
                res += "\\\\";
                break;
            case '\'' :
                res += "\\'";
                break;
            case '\"' :
                res += "\\\"";
                break;
            case '\n' :
                res += "\\n";
                break;
            case '\r' :
                res += "\\r";
                break;
            default:
                res+= ch;
                break;
        }
    }
    return res;
}

string encode(const string &s) {
    string res = s;
    res.replace(res.find('%'), 1, res);
    return res;
}

int main() {
    string s = getCode();
    cout << s;
}