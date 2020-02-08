/*
//
// Created by lnv20 on 09.05.2019.
//




#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;
std::ifstream cin("useless.in");
std::ofstream cout("useless.out");

void check_term(string &str, int &t, int &nt, int num, unordered_map<char, unordered_set<int>> &in_rules,
                vector<bool> &used) {
    unordered_set<char> ts, nts;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] <= 'z' && str[i] >= 'a') ts.insert(str[i]);
        else {
            used[str[i] - 'A'] = true;
            nts.insert(str[i]);
            in_rules[str[i]].insert(num);
        }
    }
    t = ts.size();
    nt = nts.size();
}


static bool low_letter(char ch){
    return (ch >= 'a' && ch <='z');
}
static bool upper_letter(char ch){
    return (ch >= 'A' && ch <='Z');
}
void generate(vector<pair<char, string>> &rules, vector<bool> &is_gen) {
    vector<bool> added(rules.size(), false);
    unordered_set<char> seta;
    while (true) {
        int size_bef = seta.size();
        for (int i = 0; i < rules.size(); i++) {
            if (!added[i]) {
                string &str = rules[i].second;
                bool to_add = true;
                for (int j = 0; j < str.length(); j++) {
                    if (!(low_letter(str[j])) && (seta.find(str[j]) == seta.end())) {
                        to_add = false;
                    }
                }
                if (to_add) {
                    seta.insert(rules[i].first);
                    added[i] = true;
                }
            }

        }
        if (seta.size() == size_bef) break;
    }
    for (char ch : seta) {
        is_gen[ch - 'A'] = true;
    }
}

void form_new_rules_set_used(vector<pair<char, string>> &rules, vector<pair<char, string>> &rules_res, vector<bool> &is_gen,
                             vector<bool> &used){
        for (int i = 0; i < rules.size(); i++) {
            string & r = rules[i].second;
            bool to_add = true;
            for (int j = 0; j < r.length(); j++) {
                if (!(r[j] <= 'z' && r[j] >= 'a')) {
                    used[r[j] - 'A'] = true;
                    if (!is_gen[r[j] - 'A']) {
                        to_add = false;
                    }
                }
            }
            used[rules[i].first-'A'] = true;
            if (to_add) rules_res.push_back(rules[i]);
        }
};

void not_generate(vector<pair<char, string>> &rules, vector<pair<char, string>> &rules_res, vector<bool> &is_gen,
                  vector<bool> &used) {
    unordered_map<char, unordered_set<int>> in_rules;
    vector<int> counter;
    queue<char> queue;

    for (int i = 0; i < rules.size(); i++) {
        string r = rules[i].second;
        char l = rules[i].first;
        used[l - 'A'] = true;
        int t, nt;
        check_term(r, t, nt, i, in_rules, used);
        if (nt == 0) {
            is_gen[l - 'A'] = true;
            queue.push(l);
        }
        counter.push_back(nt);
    }
    while (!queue.empty()) {
        char cur = queue.front();
        for (int rule : in_rules[cur]) {
            if (counter[rule] == 1) {
                if (!is_gen[rules[rule].first - 'A']) queue.push(rules[rule].first);
                counter[rule] = 0;
                is_gen[rules[rule].first - 'A'] = true;
            } else --counter[rule];
        }
        queue.pop();
    }
//    for (int i = 0; i < 26; i++) {
//        if (is_gen[i]) cout << (char) (i + 'A') << " ";
//    }
    for (int i = 0; i < rules.size(); i++) {
        string r = rules[i].second;
        bool to_add = true;
        for (int j = 0; j < r.length(); j++) {
            if (!(r[j] <= 'z' && r[j] >= 'a'))
                if (!is_gen[r[j] - 'A']) {
                    to_add = false;
                    break;
                }
        }
        if (to_add) rules_res.push_back(rules[i]);
    }

}

void dfs(char ch, vector<unordered_set<char>> &connections, vector<bool> &connect_start) {
    int i = ch - 'A';
    connect_start[i] = true;
    for (char c : connections[i]) {
        if (!connect_start[c - 'A']) dfs(c, connections, connect_start);
    }
}

void connect_start(char start, vector<pair<char, string>> &rules, vector<bool> &connect_start) {
    vector<unordered_set<char>> connections(26);
    for (int i = 0; i < rules.size(); i++) {
        int l = rules[i].first;
        string r = rules[i].second;
        for (int j = 0; j < r.length(); j++) {
            char ch = r[j];
            if (ch <= 'Z' && ch >= 'A') connections[l - 'A'].insert(ch);
        }
    }
    dfs(start, connections, connect_start);
}

void connect_start_(char start, vector<pair<char, string>> &rules, vector<bool> &connect_start) {
    vector<bool> added(rules.size(), false);
    unordered_set<char> connected;
    connected.insert(start);
    while (true) {
        int size_bef = connected.size();
        for (int i = 0; i < rules.size(); i++) {
            if (!added[i]) {
                if (connected.find(rules[i].first) != connected.end()) {
                    string &r = rules[i].second;
                    for (int j = 0; j < r.size(); j++) {
                        if (r[j] >= 'A' && r[j] <= 'Z') connected.insert(r[j]);
                    }
                    added[i] = true;
                }
            }
        }
        if (connected.size() == size_bef) break;
    }
    for (char ch : connected) {
        connect_start[ch - 'A'] = true;
    }
}

int main236() {
 //   bool debug = 0;

    vector<pair<char, string>> rules;
//    vector<bool> used(26, false);
    vector<bool> used_func(26, false);
//    vector<pair<char, string>> gen_rules;
    vector<pair<char, string>> gen_rules_2;
//    vector<bool> is_gen(26, false);
    vector<bool> is_gen_2(26, false);
    vector<bool> is_start(26, false);
    char start;
    int n;
    string divider;
    char prev;
    cin >> n >> start >> prev >> divider;

    for (int i = 0; i < n - 1; i++) {
        string suppose_start;
        cin >> suppose_start >> divider;
      //  used[prev-'A'] = true;
        if (divider == "->") {
            rules.push_back({prev, ""});
            prev = suppose_start[0];
        } else {
         //   add_used(suppose_start, used);
            rules.push_back({prev, suppose_start});
            prev = divider[0];
            cin >> divider;
        }
    }
  //  used[prev-'A'] = true;
    cin >> divider;
    if (divider == "->") rules.push_back({prev, ""});
    else {
       // add_used(divider, used);
        rules.push_back({prev, divider}
    );}


//   not_generate(rules, gen_rules, is_gen, used_func);
    generate(rules, is_gen_2);
    form_new_rules_set_used(rules, gen_rules_2, is_gen_2, used_func);
    */
/*cout << "used_func\n";
    for (int i = 0; i < 26; i++) {
        if (used_func[i]) cout << (char) (i + 'A') << " ";
    }
    cout << "\nused_main\n";
    for (int i = 0; i < 26; i++) {
        if (used[i]) cout << (char) (i + 'A') << " ";
    }
    cout << "\ngen_1\n";
    for (int i = 0; i < 26; i++) {
        if (is_gen[i]) cout << (char) (i + 'A') << " ";
    }
    cout << "\ngen_2\n";
    for (int i = 0; i < 26; i++) {
        if (is_gen_2[i]) {
            cout << (char) (i + 'A') << " ";
        }
    }
    cout << "\ngen_rules_1\n";
    for (int i = 0; i < gen_rules.size(); i++) {
        cout << gen_rules[i].first << " -> " << gen_rules[i].second << endl;
    }
    cout << "\ngen_rules_2\n";
    for (int i = 0; i < gen_rules.size(); i++) {
        cout << gen_rules_2[i].first << " -> " << gen_rules[i].second << endl;
    }*//*

    connect_start(start, gen_rules_2, is_start);
    used_func[start - 'A'] = true;
    for (int i = 0; i < 26; i++) {
        if (used_func[i] && (!(is_start[i]) || !(is_gen_2[i]))) cout << (char) (i + 'A') << " ";
    }
//    for (int i = 0; i < 26; i++) {
//        if (used[i] ) cout << (char) (i + 'A') << " ";
//    }

    return 0;
}
*/
