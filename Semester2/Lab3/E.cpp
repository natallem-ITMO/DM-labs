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
bool debug = 1;
int vertex_dfs;

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
    if (i == -1) return '_';
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

bool contains_terminal(pair<int, int> pair) {
    return (is_term_char(pair.first) || is_term_char(pair.second));
}

void show_set(unordered_set<int> &sets, string mes) {
    cout << mes << endl;
    set<int> ss;
    for (int x : sets) {
        ss.insert(x);
    }
    for (int x : ss) {
        cout << x << "(" << ic(x) << ") ";
    }
    cout << endl;
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
            cout << itr->first << "(" << ic(itr->first) << ")=" << "(" << ic(pp.first)
                 << ic(pp.second) << ")" << pp.first << "," << pp.second << endl;
        }
    }
}

void show_rules(unordered_map<int, vector<int>> &rules, string mes) {
    cout << endl << mes << endl;
    map<int, vector<int>> rules_order;
    auto itr = rules.begin();
    for (auto itr = rules.begin(); itr != rules.end(); itr++) {
        rules_order[itr->first] = itr->second;
    }
    for (auto itr = rules_order.begin(); itr != rules_order.end(); itr++) {
        for (int pp : itr->second) {
            cout << itr->first << "(" << ic(itr->first) << ")=" << "(" << ic(pp) << ")" << endl;
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


void to_nlong(vector<pair<char, string>> &rules, unordered_map<int, vector<pair<int, int>>> &short_gr) {
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

            }
            pair<int, int> cur_pair = {ci(str[str.length() - 2]), ci(str[str.length() - 1])};
            short_gr[cur_free_letter].push_back(cur_pair);

            // short_gr[next_int()].push_back({ci(str[str.length() - 2]), ci(str[str.length() - 1])});
        } else {
            switch (str.length()) {
                case 0 :
                    short_gr[ci(l)].push_back({-1, -1});
                    break;
                case 1:
                    short_gr[ci(l)].push_back({str[0], -1});
                    break;
                case 2:
                    short_gr[ci(l)].push_back({str[0], str[1]});
                    break;
            }
        }
    }
    if (debug) show_rules(short_gr, "1) nlong:");
}

void to_nesp(unordered_map<int, vector<pair<int, int>>> &rules_input,
             unordered_map<int, vector<pair<int, int>>> &rules_output) {
    vector<pair<int, pair<int, int>>> rules;
    vector<pair<int, pair<int, int>>> rules_added;
    unordered_map<int, unordered_set<int>> in_rules;//список номеров тех правил, в правой части которых нетерминал встречается
    vector<int> counter;//счетчик количества нетерминалов в правой части, которые еще не помечены ε-порождающими
    queue<int> queue;
    unordered_map<int, bool> is_eps;
    for (pair<int, vector<pair<int, int>>> pair1 : rules_input) {
        int cur_l = pair1.first;
        for (pair<int, int> pair2 : pair1.second) {
            if (contains_terminal(pair2)) rules_output[cur_l].push_back(pair2);
            else rules.push_back({cur_l, pair2});
        }
    }
    if (debug) {
        // show_rules(rules_input, "input no eps");
        show_rules(rules, "2) no_term");
        show_rules(rules_output, "2) contains terminals");
    }
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

    for (pair<int, pair<int, int>> pair1 : rules){
        int left = pair1.first;//left -> AB
        int A = pair1.second.first;
        int B = pair1.second.second;
        if (is_eps_char(A) && is_eps_char(B)){}
        else (is_eps_char(B)){
            if (is_eps[A]) {
                rules_added.push_back(left, {-1,-1});
            }
        }

    }


    cout << "here eps";
    for (pair<int, bool> pair1: is_eps){
        if (pair1.second) cout << pair1.first <<"("<<ic(pair1.first)<<")"<<endl;
    }
    for (int i = 0; i < rules.size(); i++) {
        if (counter[i] != 0) rules_output[rules[i].first].push_back(rules[i].second);
    }
    if (debug) show_rules(rules_output, "2) output no_eps");
}

void dfs(int cur_vertex, unordered_map<int, vector<int>> &rules, unordered_map<int, vector<int>> &units,
         unordered_set<int> &used) {
//if (!used[cur_vertex]);
    used.insert(cur_vertex);
    units[vertex_dfs].push_back(cur_vertex);
    for (int x : rules[cur_vertex]) {
        if (used.find(x) == used.end()) dfs(x, rules, units, used);
    }
}

void to_nunit(unordered_map<int, vector<pair<int, int>>> &rules_input,
              unordered_map<int, vector<pair<int, int>>> &rules_output) {
    unordered_map<int, vector<pair<int, int>>> rules_nunit;
    unordered_map<int, vector<int>> graph;
    unordered_map<int, vector<int>> units;
    unordered_set<int> vertex;

    for (pair<int, vector<pair<int, int>>> pair1 : rules_input) {
        int cur_l = pair1.first;
        for (pair<int, int> pair2 : pair1.second) {
            int f = pair2.first;
            int s = pair2.second;
            if (is_not_term_char(f) && is_eps_char(s)) {
                vertex.insert(f);
                vertex.insert(cur_l);
                graph[cur_l].push_back(f);
                //   rules_all[cur_l].push_back(f);
            } else {
                rules_output[cur_l].push_back(pair2);
                rules_nunit[cur_l].push_back(pair2);
            }
        }
    }
    show_rules(rules_nunit, "3) rules non unit");
    show_rules(graph, "3) rules unit");
    show_rules(rules_output, "3) rules out");
    show_set(vertex, "3) vertexes");
    for (int x : vertex) {
        vertex_dfs = x;
        unordered_set<int> used;
        used.insert(x);
        dfs(x, graph, units, used);
    }
    show_rules(units, "3) after dfs rules");
    for (pair<int, vector<int>> pair1 : units) {
        int left = pair1.first;
        for (int right: pair1.second) {
            if (left != right)
            for (pair<int, int> pair3 : rules_nunit[right]){
                rules_output[left].push_back(pair3);
            }
        }
    }
    show_rules(rules_output, "3) result output");

}

//TODO start == eps
int main() {
    vector<pair<char, string>> rules;
    unordered_map<int, vector<pair<int, int>>> nlong;
    unordered_map<int, vector<pair<int, int>>> nlong_nesp;
    unordered_map<int, vector<pair<int, int>>> nlong_nesp_nunit;
//    unordered_map<int, vector<pair<int, int>>> short_gr_no_term_map;
//    vector<pair<int, pair<int, int>>> short_gr_no_term_vector;
    //  vector<pair<int, pair<int, int>>> short_gr_no_term_vector;
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
    to_nlong(rules, nlong);
//    if (debug) show_rules(nlong, "nlong");
    to_nesp(nlong, nlong_nesp);
    to_nunit(nlong_nesp, nlong_nesp_nunit);


    return 0;
}
