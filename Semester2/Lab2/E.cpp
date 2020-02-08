
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

using namespace std;
//std::ifstream cin("a.in");
std::ifstream cin("problem5.in");
std::ofstream cout("problem5.out");
//std::ofstream cout("a.out");

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

 int main() {
    long long int mod = 1000000000 + 7;

    unordered_set<long long int> terminal_states_NFA;
    unordered_set<long long int> terminal_states_DFA;

    long long int n, m, k, l;

    cin >> n >> m >> k >> l;

    for (long long int i = 0; i < k; i++) {
        long long int fd;
        cin >> fd;
        terminal_states_NFA.insert(fd);
    }
    unordered_map<long long int, set<long long int>> sample;
    for (long long int i = 0; i < 26; i++) sample[i] = {0};
    vector<unordered_map<long long int, set<long long int>>> edges_NFA(n, sample);
    for (long long int i = 0; i < m; i++) {
        long long int start, end;
        char ch;
        cin >> start >> end >> ch;
        edges_NFA[start - 1][ch - 'a'].insert(end);
    }
    //BUILD DFA
    unordered_map<long long int, string> num_str_DFA;
    unordered_map<long long int, set<long long int>> num_set_DFA;
    unordered_map<string, long long int> str_num_DFA;
    num_set_DFA[1] = {1};
    num_str_DFA[1] = "1 ";
    str_num_DFA["1 "] = 1;
    if (terminal_states_NFA.find(1)!=terminal_states_NFA.end()) terminal_states_DFA.insert(1);
    long long int lastCond = 1;
    unordered_map<long long int, vector<long long int>> path_state_DFA;
    queue<long long int> queue;
    queue.push(1);

    while (!queue.empty()) {
        long long int cur = queue.front();
        queue.pop();
        set<long long int> conditions_NFA = num_set_DFA[cur];
        for (long long int i = 0; i < 26; i++) {
            set<long long int> conditions_DFA;
            for (long long int cond : conditions_NFA) {
                if (edges_NFA[cond-1][i].size() != 1)
                    for (long long int x : edges_NFA[cond-1][i]){
                        if (x!=0) conditions_DFA.insert(x);
                    }
            }
            if (!conditions_DFA.empty()) {
                string cond_str = set_to_str(conditions_DFA);
                long long int vertex_arrive = 0;
                if (str_num_DFA.find(cond_str) == str_num_DFA.end()) {
                    lastCond++;
                    num_set_DFA[lastCond] = conditions_DFA;
                    num_str_DFA[lastCond] = cond_str;
                    str_num_DFA[cond_str] = lastCond;
                    vertex_arrive = lastCond;
                    queue.push(lastCond);
                    for (long long int x : terminal_states_NFA){
                        if (conditions_DFA.find(x) != conditions_DFA.end()) {
                            terminal_states_DFA.insert(lastCond);
                            break;
                        }
                    }
                } else vertex_arrive = str_num_DFA[cond_str];
                if (path_state_DFA[vertex_arrive].empty()) {
                    path_state_DFA[vertex_arrive] = {cur};
                } else path_state_DFA[vertex_arrive].push_back(cur);
            }
        }
    }
    n = lastCond;

    vector<long long int> emVec(l + 1, 0);
    vector<vector<long long int>> mat(n, emVec);
    mat[0][0] = 1;
    for (long long int len = 1; len <= l; len++) {
        for (long long int cond = 0; cond < n; cond++) {
            if (!path_state_DFA[cond+1].empty()){
                for (long long int x : path_state_DFA[cond+1]){
                    long long int valuePrevCond = mat[x-1][len-1];
                    mat[cond][len] += valuePrevCond ;
                    mat[cond][len] %= mod;
                }
            }
        }
    }
    //showMatrix(mat);
    long long int ans = 0;
    for (long long int x : terminal_states_DFA){
        ans += mat[x-1][l];
        ans %= mod;
    }
    cout << ans;
    return 0;
}
