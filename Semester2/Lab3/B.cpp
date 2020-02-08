/*



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

using namespace std;
std::ifstream cin("a.in");
//std::ifstream cin("automaton.in");
//std::ofstream cout("automaton.out");
std::ofstream cout("a.out");
static void showVector(vector<long long int> &vec) {
    for (long long int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

static void showSet(unordered_set
                            <long long int> &set) {
    unordered_set<long long int>::iterator itr;
    for (itr = set.begin(); itr != set.end(); itr++) {
        cout << (*itr) << " ";
    }
    cout << endl;
}

static void showMatrix(vector<vector<long long int>> &m) {
    for (long long int i = 0; i < m.size(); i++) {
        showVector(m[i]);
    }
    cout << endl;
}

string set_to_str(set<long long int> &set) {
    string toReturn = "";
    for (long long int x : set) {
        toReturn += to_string(x) + " ";
    }
    return toReturn;
}


bool no_term(string &str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] <= 'z' && str[i] >= 'a') return false;
    }
    return true;
}

int main() {
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<bool> is_eps(26, false);
    unordered_map<char, unordered_set<int>> in_rules;
    vector<int> counter;
    queue<char> queue;
    vector<pair<char, string>> rules;
    char start;
    int n;
    string divider;
    char prev;
    cin >> n >> start >> prev >> divider;

    for (int i = 0; i < n - 1; i++) {
        string suppose_start;
        cin >> suppose_start >> divider;
        if (divider == "->") {
            rules.push_back({prev, ""});
            prev = suppose_start[0];
        } else {
            if (no_term(suppose_start)) {
                rules.push_back({prev, suppose_start});

            }
            prev = divider[0];
            cin >> divider;
        }
    }
    cin >> divider;
    if (divider == "->") rules.push_back({prev, ""});
    else if (no_term(divider)) rules.push_back({prev, divider});
    for (int i = 0; i < rules.size(); i++) {
        string r = rules[i].second;
        unordered_set<char> s;
        for (int j = 0; j < r.length(); j++) {
            in_rules[r[j]].insert(i);
            s.insert(r[j]);
        }
        counter.push_back(s.size());
        if (s.size() == 0) {
            is_eps[rules[i].first - 'A'] = true;
            queue.push(rules[i].first);
        }
    }
    while (!queue.empty()) {
        char cur = queue.front();
        for (int rule : in_rules[cur]){
            if (counter[rule] == 1) {
                if (!is_eps[rules[rule].first - 'A']) queue.push(rules[rule].first);
                counter[rule] = 0;
                is_eps[rules[rule].first - 'A'] = true;
            } else --counter[rule];
        }
        queue.pop();
    }
    for (int i = 0; i < 26; i++){
        if (is_eps[i]) cout << (char) (i+'A') << " ";
    }
    return 0;
}
*/
