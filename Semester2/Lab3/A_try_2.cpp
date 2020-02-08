


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
/*static void showVector(vector<long long int> &vec) {
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
    std::ofstream cout("automaton.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    unordered_map<char, unordered_map<char, vector<char>>> mm;
    int n, m;
    char start;
    cin >> n >> start;
    for (int i = 0; i < n; i++) {
        char first;
        string second;
        cin >> first >> second >> second;
        if (second.length() > 1) {
            mm[first][second[0]].push_back(second[1]);
        } else mm[first][second[0]].push_back('&');
    }
    cin >> m;
    string cur_str;
    for (int i = 0; i < m; i++) {
        cin >> cur_str;
        unordered_set<char> possible_conditions;
        possible_conditions.insert(start);
        for (int i = 0; i < cur_str.length(); i++) {
            if (possible_conditions.empty()) break;
            unordered_set<char> n_possible_conditions;
            char cur_char = cur_str[i];
            for (char x : possible_conditions) {
                if (x != '&')
                for (char y: mm[x][cur_char]) {
                    n_possible_conditions.insert(y);
                }
            }
            possible_conditions = n_possible_conditions;
        }
        if (possible_conditions.find('&') != possible_conditions.end()) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}
