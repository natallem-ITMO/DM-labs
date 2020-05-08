#include <iostream>

using namespace std;

string replaceCode(const string &s, const string &replacer);

string getCode(const string &replacer);

string replaceCode(const string &s, const string &replacer);

int main() {
    int n = 2;
    string res = "";
    if (n != 1) {
        res = getCode(to_string(n - 1));
    }
    cout << res;
}

string getCode(const string &replacer) {
    string s = "#include <iostream>\n"
               "\n"
               "using namespace std;\n"
               "\n"
               "string replaceCode(const string &s, const string &replacer);\n"
               "\n"
               "string getCode(const string &replacer);\n"
               "\n"
               "string replaceCode(const string &s, const string &replacer);\n"
               "\n"
               "int main() {\n"
               "    int n = 1;\n"
               "    string res = \"\";\n"
               "    if (n != 1) {\n"
               "        res = getCode(to_string(n - 1));\n"
               "    }\n"
               "    cout << res;\n"
               "}\n"
               "\n"
               "string getCode(const string &replacer) {\n"
               "    string s = \"%\";\n"
               "    return replaceCode(s, replacer);\n"
               "}\n"
               "\n"
               "string replaceCode(const string &s, const string &replacer) {\n"
               "    string res = s;\n"
               "    string code = s;\n"
               "    res.replace(res.find('1'), 1, replacer);\n"
               "    res.replace(res.find('%'), 1, code);\n"
               "    return res;\n"
               "}";
    return replaceCode(s, replacer);
}

string replaceCode(const string &s, const string &replacer) {
    string res = s;
    string code = s;
    res.replace(res.find('1'), 1, replacer);
    res.replace(res.find('%'), 1, code);
    return res;
}
