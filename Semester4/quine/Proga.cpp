#include <iostream>

using namespace std;

string encode(const string &s);

string getCode() {
    string s = "#include <iostream>\n"
               "\n"
               "using namespace std;\n"
               "\n"
               "string encode(const string &s);\n"
               "\n"
               "string getCode() {\n"
               "    string s = \"%\";\n"
               "    return encode(s);\n"
               "}\n"
               "\n"
               "string mirror(const string &s) {\n"
               "    string res;\n"
               "    for (char ch : s){\n"
               "        switch(ch) {\n"
               "            case '\\\\' :\n"
               "                res += \"\\\\\\\\\";\n"
               "                break;\n"
               "            case '\\'' :\n"
               "                res += \"\\\\'\";\n"
               "                break;\n"
               "            case '\\\"' :\n"
               "                res += \"\\\\\\\"\";\n"
               "                break;\n"
               "            case '\\n' :\n"
               "                res += \"\\\\n\";\n"
               "                break;\n"
               "            case '\\r' :\n"
               "                res += \"\\\\r\";\n"
               "                break;\n"
               "            default:\n"
               "                res+= ch;\n"
               "                break;\n"
               "        }\n"
               "    }\n"
               "    return res;\n"
               "}\n"
               "\n"
               "string encode(const string &s) {\n"
               "    string res = s;\n"
               "    res.replace(res.find('%'), 1, res);\n"
               "    return res;\n"
               "}\n"
               "\n"
               "int main() {\n"
               "    string s = getCode();\n"
               "    cout << s;\n"
               "}";
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
    res.replace(res.find('%'), 1, mirror(res));
    return res;
}

int main() {
    string s = getCode();
    cout << s;
}