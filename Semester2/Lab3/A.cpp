

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
//std::ifstream cin("a.in");
//std::ifstream cin("automaton.in");
//std::ofstream cout("automaton.out");
//std::ofstream cout("a.out");
/*
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
*/
int main() {
    std::ifstream cin("automaton.in");
    std::ofstream cout("a.out");
//    std::ifstream cin("automaton.in");
//    std::ofstream cout("automaton.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    //const int max_all = 10000;
    int max_length = 10000;
    unordered_map<char, vector<string>> transfers;
    queue<string> queue;
    int n, m;
    string start;
    cin >> n >> start;
    for (int i = 0; i < n; i++) {
        char first;
        string second;
        cin >> first >> second >> second;
        transfers[first].push_back(second);
    }
    cin >> m;
    //   vector<string> words(m);
    queue.push(start);
    unordered_set<string> terminals;
    string new_cond;
    while (!queue.empty()) {
        for (string x : transfers[queue.front()[queue.front().length() - 1]]) {
            new_cond = queue.front();
            new_cond[queue.front().length() - 1] = x[0];
            if (x.length() > 1) {
                if (queue.front().length() < max_length) {
                    queue.push(new_cond + x[1]);
                }
            } else {
                terminals.insert(new_cond);
            }
        }
        queue.pop();
    }
    string r_str;
    for (int i = 0; i < m; i++) {
        cin >> r_str;
        if (terminals.find(r_str) != terminals.end()) cout << "yes\n";
        else cout << "no\n";
    }

    return 0;
}
