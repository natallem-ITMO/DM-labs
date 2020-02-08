#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>
#include <map>

using namespace std;
std::ifstream cin("a.in");
std::ofstream cout("a.out");

const int let_beg = 123;
int cur_free_letter = 123;

int next_int() {
    cur_free_letter++;
    return cur_free_letter - 1;
}

bool low_letter(char ch) {
    return (ch >= 'a' && ch <= 'z');
}

bool upper_letter(char ch) {
    return (ch >= 'A' && ch <= 'Z');
}

int ci(char ch) {
    return (int) ch;
}

char ic(int i) {
    if (i <= 'z' && i >= 'a') return (char) i;
    if (i >= 'A' && i <= 'Z') return (char) i;
    else return '!';

}

bool is_eps_char(int ch) {
    return ch == -1;
}

bool is_term_char(int ch) {
    if (is_eps_char(ch)) return false;
    if (low_letter((char) ch)) return true;
    return false;
}

bool is_not_term_char(int ch) {
    if (is_eps_char(ch)) return false;
    if (is_term_char(ch)) return false;

    return true;
}


bool is_term(pair<int, int> pair) {
    if (is_term_char(pair.first) && is_term_char(pair.second)) return true;
    if (is_term_char(pair.first) && is_eps_char(pair.second)) return true;
    return false;
}

void show_rules(unordered_map<int, vector<pair<int, int>>> &rules, string mes) {
    cout << endl << mes << endl;
    map<int, vector<pair<int, int>>> rules_order;
    auto itr = rules.begin();
    for (auto itr = rules.begin(); itr != rules.end(); itr++) {
        rules_order[itr->first] = itr->second;
    }
    for (auto itr = rules_order.begin(); itr != rules_order.end(); itr++) {
        for (pair<int, int> pp : itr->second) {
            cout << itr->first << "(" << ic(itr->first) << ")=" << pp.first << "," << pp.second << "(" << ic(pp.first)
                 << ic(pp.second) << ")" << endl;
        }
    }
}

void show_rules(vector<pair<int, pair<int, int>>> &rules, string mes) {
    cout << endl << mes << endl;
    for (pair<int, pair<int, int>> pair : rules) {
        cout << pair.first << "(" << ic(pair.first) << ")=" << pair.second.first << "," << pair.second.second << "("
             << ic(pair.second.first) << ic(pair.second.second) << ")" << endl;
    }

}


void to_short(vector<pair<char, string>> &rules, unordered_map<int, vector<pair<int, int>>> &short_gr,
              unordered_map<int, vector<pair<int, int>>> &short_gr_no_terminal,
              vector<pair<int, pair<int, int>>> &no_term) {
    for (pair<char, string> rule : rules) {
        string &str = rule.second;
        char l = rule.first;
        if (str.length() > 2) {
            for (int i = 0; i < str.length() - 2; i++) {
                int let, next_let;
                if (i == 0) {
                    let = ci(l);
                    next_let = cur_free_letter;
                } else {
                    let = next_int();
                    next_let = let + 1;
                }
                pair<int, int> cur_pair = {ci(str[i]), next_let};
                short_gr[let].push_back(cur_pair);
                if (!is_term(cur_pair)) {
                    short_gr_no_terminal[let].push_back(cur_pair);
                    no_term.push_back({let, cur_pair});
                }
            }
            pair<int, int> cur_pair = {ci(str[str.length() - 2]), ci(str[str.length() - 1])};
            short_gr[cur_free_letter].push_back(cur_pair);
            if (!is_term(cur_pair)) {
                short_gr_no_terminal[cur_free_letter].push_back(cur_pair);
                no_term.push_back({next_int(), cur_pair});
            }
            // short_gr[next_int()].push_back({ci(str[str.length() - 2]), ci(str[str.length() - 1])});
        } else {
            switch (str.length()) {
                case 0 :
                    short_gr[ci(l)].push_back({-1, -1});
                    short_gr_no_terminal[ci(l)].push_back({-1, -1});
                    no_term.push_back({ci(l), {-1, -1}});
                    break;
                case 1:
                    short_gr[ci(l)].push_back({str[0], -1});
                    if (!is_term_char(str[0])) {
                        short_gr_no_terminal[ci(l)].push_back({str[0], -1});
                        no_term.push_back({ci(l), {str[0], -1}});
                    }
                    break;
                case 2:
                    short_gr[ci(l)].push_back({str[0], str[1]});
                    if (!is_term({str[0], str[1]})) {
                        short_gr_no_terminal[ci(l)].push_back({str[0], str[1]});
                        no_term.push_back({ci(l), {str[0], str[1]}});
                    };
                    break;
            }
        }
    }
}

void to_no_eps(vector<pair<int, pair<int, int>>> &rules, unordered_map<int, bool> &is_eps,
               vector<pair<int, pair<int, int>>> &rules_no_eps) {

    unordered_map<int, unordered_set<int>> in_rules;//список номеров тех правил, в правой части которых нетерминал встречается
    vector<int> counter;//счетчик количества нетерминалов в правой части, которые еще не помечены ε-порождающими
    queue<int> queue;
    for (int i = 0; i < rules.size(); i++) {
        pair<int, int> r = rules[i].second;
        is_eps[rules[i].first] = false;
        is_eps[r.first] = false;
        is_eps[r.second] = false;
    }
    for (int i = 0; i < rules.size(); i++) {
        pair<int, int> r = rules[i].second;
        unordered_set<char> s;
        if (is_not_term_char(r.first)) {
            in_rules[r.first].insert(i);
            s.insert(r.first);
        }
        if (is_not_term_char(r.second)) {
            in_rules[r.second].insert(i);
            s.insert(r.second);
        }
        counter.push_back(s.size());
        if (s.size() == 0) {
            is_eps[rules[i].first] = true;
            queue.push(rules[i].first);
        }
    }
    while (!queue.empty()) {
        int cur = queue.front();
        for (int rule : in_rules[cur]) {
            if (counter[rule] == 1) {
                if (!is_eps[rules[rule].first]) queue.push(rules[rule].first);
                counter[rule] = 0;
                is_eps[rules[rule].first] = true;
            } else --counter[rule];
        }
        queue.pop();
    }
    for (int i = 0; i < rules.size(); i++) {
        if (counter[i] != 0) rules_no_eps.push_back(rules[i]);
    }

}

int main() {
    vector<pair<char, string>> rules;
    unordered_map<int, vector<pair<int, int>>> short_gr;
    unordered_map<int, vector<pair<int, int>>> short_gr_no_term_map;
    vector<pair<int, pair<int, int>>> short_gr_no_term_vector;
    vector<pair<int, pair<int, int>>> short_gr_no_term_vector;
    unordered_map<int, bool> is_eps;
    char start, prev;
    string divider;
    int n;

    cin >> n >> start >> prev >> divider;

    for (int i = 0; i < n - 1; i++) {
        string suppose_start;
        cin >> suppose_start >> divider;
        if (divider == "->") {
            rules.push_back({prev, ""});
            prev = suppose_start[0];
        } else {
            rules.push_back({prev, suppose_start});
            prev = divider[0];
            cin >> divider;
        }
    }
    cin >> divider;
    if (divider == "->") rules.push_back({prev, ""});
    else rules.push_back({prev, divider});
    int let_beg = 123;
    to_short(rules, short_gr, short_gr_no_term_map, short_gr_no_term_vector);
    show_rules(short_gr, "short_gr");
    show_rules(short_gr_no_term_map, "short_gr_no_term_map");
    show_rules(short_gr_no_term_vector, "short_gr_no_term_vector");
    to_no_eps(short_gr_no_term_vector, is_eps);


    return 0;
}
