/*
//#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <queue>
//#include <iostream>
#define ll long long
#define f first
#define s second
using namespace std;

struct rule {
    int l;
    char c;
    int next;
};
vector <vector <pair <char, int> > > vv(26);
bool dfs(int v, string &data, int pos) {
    bool ok = 0;
    for (int i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i].s;
        char char_ = vv[v][i].f;
        // cout << v << " " << to << " " << char_ << " " << data[pos] << '\n';
        if (to == -1)
            ok |= pos == data.length() - 1 && char_ == data.back();
        else
        if (data[pos] == char_)
            ok |= dfs(to, data, pos + 1);
    }
    return ok;
}

int main()
{
    ifstream cin("a.in");
    ofstream cout("a.out");
    char x;
    int n, start;
    cin >> n >> x;
    string str;
    getline(cin, str);
    vector <rule> rules;
    start = x - 'A';
    for (int i = 0; i < n; i++) {
        bool ok = 1;
        getline(cin, str);
        // cout << str << " " << str.length() << '\n';
        if (str.length() == 6) {
            vv[str[0] - 'A'].push_back({str[5], -1});
        } else {
            vv[str[0] - 'A'].push_back({str[5], str[6] - 'A'});
        }
    }
    // cout << vv[0].size() << '\n';
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        if (dfs(start, s, 0))
            cout << "yes\n";
        else
            cout << "no\n";
    }
}
*/
