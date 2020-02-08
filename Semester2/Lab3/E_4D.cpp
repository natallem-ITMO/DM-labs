//
// Created by lnv20 on 11.05.2019.
//



//
// Created by lnv20 on 09.05.2019.
//




#include <fstream>
//#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
#include <map>
#include <algorithm>


using namespace std;
std::ifstream cin("cf.in");
std::ofstream cout("cf.out");
//std::ifstream cin("a.in");
//std::ofstream cout("a.out");

static void show_vector(vector<bool> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

static void show_matrix(vector<vector<bool>> &m) {
    for (int i = 0; i < m.size(); i++) {
        show_vector(m[i]);
    }
    cout << endl;
}

void show_matrix(vector<vector<vector<bool>>> &dp, string mes) {
    cout << mes << endl;
    for (int i = 0; i < 26; i++) {
        cout << (char) ('A' + i) << endl;
        show_matrix(dp[i]);
    }
}

void show_matrix(vector<vector<vector<vector<bool>>>> &h, unsigned int mrule, vector<pair<char, string>> &rules,
                 string mes) {

    cout << mes << endl;
    for (int i = 0; i < rules.size(); i++) {
        for (int k = 0; k < mrule; k++) {
            cout << rules[i].first << " -> " << rules[i].second << " k=" << k << endl;
            show_matrix(h[i][k]);
        }
    }
}

bool is_term(char ch) {
    if (ch <= 'z' && ch >= 'a') return true;
    return false;
}

int main() {
    vector<pair<char, string>> rules;
    char start;
    string divider, word;
    int n;
    int mrule = 0;
    set<char> nterm_contain_eps;
    map<char, set<char>> letter_rules;
    string str;
    cin >> n >> start;
    getline(cin, str);
    for (int i = 0; i < n; i++) {
        getline(cin, str);
        string tmp;
        for (int j = 5; j < str.length(); j++)
            tmp += str[j];
        if (tmp.length() > mrule) mrule = tmp.length();
        rules.push_back({str[0], tmp});
    }
    getline(cin, word);
    mrule++;
    vector<vector<vector<bool>>> dp(26,
                                    vector<vector<bool>>(word.length() + 1, vector<bool>(word.length() + 1, false)));
    vector<vector<vector<vector<bool>>>> h(n, vector<vector<vector<bool>>>
            (mrule, vector<vector<bool>>(word.length() + 1, vector<bool>(word.length() + 1, false))));

    for (pair<char, string> pp  : rules) {
        if (pp.second.length() == 1) {
            char ch = pp.second[0];
            if (is_term(ch)) {
                letter_rules[ch].insert(pp.first);
            }
        }
        if (pp.second.length() == 0) {
            nterm_contain_eps.insert(pp.first);
        }
    }
    for (int i = 0; i < 26; i++) {
        bool flag = (nterm_contain_eps.find(i + 'A') != nterm_contain_eps.end());
        for (int j = 0; j < word.length(); j++) {
            char ch = word[j];
            if (j != word.length()) {
                if (letter_rules[ch].find((char) 'A' + i) != letter_rules[ch].end()) {
                    dp[i][j][j + 1] = true;
                }
            }
            dp[i][j][j] = flag;
        }
        dp[i][word.length()][word.length()] = flag;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < word.length(); j++) {
            h[i][0][j][j] = true;
        }
    }
    int i, j;
    i = j = 0;
    for (int k = 1; k < mrule; k++) {
        for (int i_rule = 0; i_rule < rules.size(); i_rule++) {
            pair<char, string> cur_rule = rules[i_rule];
            char left = cur_rule.first;
            string right = cur_rule.second;
            if (k <= right.length() && is_term(right[k - 1])) {
                for (int r = i; r < j + 1; r++) {
                    if (j - r == 1 && word[r] == right[k - 1]) {//
                        h[i_rule][k][i][j] = h[i_rule][k][i][j] || h[i_rule][k - 1][i][r];
                    }
                }
            } else if (k <= right.length()) {
                for (int r = i; r < j + 1; r++) {
                    h[i_rule][k][i][j] =
                            h[i_rule][k][i][j] || (h[i_rule][k - 1][i][r] && dp[right[k - 1] - 'A'][r][j]);
                }
            }
        }
    }

    for (int i = 0; i < 13; i++) {
        for (int dif_i_j = 1; dif_i_j <= word.length(); dif_i_j++) {//длина подстроки
            for (int i = 0; i + dif_i_j <= word.length(); i++) {//передвигаемся по строке со сдвигом
                int j = i + dif_i_j;
                for (int k = 1; k < mrule; k++) {//TODO check k<mrule
                    for (int i_rule = 0; i_rule < rules.size(); i_rule++) {
                        pair<char, string> cur_rule = rules[i_rule];
                        string right = cur_rule.second;
                        if (k <= right.length() && is_term(right[k - 1])) {
                            for (int r = i; r < j + 1; r++) {
                                if (j - r == 1 && word[r] == right[k - 1]) {
                                    h[i_rule][k][i][j] = h[i_rule][k][i][j] || h[i_rule][k - 1][i][r];
                                }
                            }
                        } else if (k <= right.length()) {
                            for (int r = i; r < j + 1; r++) {
                                h[i_rule][k][i][j] =
                                        h[i_rule][k][i][j] || (h[i_rule][k - 1][i][r] && dp[right[k - 1] - 'A'][r][j]);
                            }
                        }
                    }
                }
                for (int letters = 0; letters < 26; letters++) {
                    for (int i_rule = 0; i_rule < rules.size(); i_rule++) {
                        if (rules[i_rule].first - 'A' == letters) {
                            dp[letters][i][j] = dp[letters][i][j] || h[i_rule][rules[i_rule].second.length()][i][j];
                        }
                    }
                }
            }
        }
    }
    if (dp[start - 'A'][0][word.length()]) cout << "yes";
    else cout << "no";
    return 0;
}






