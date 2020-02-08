#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>

using namespace std;
//std::ifstream cin("a.in");
std::ifstream cin("problem4.in");
std::ofstream cout("problem4.out");
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

bool dfs(long long int u, long long int v, unordered_set<long long int> &end1, unordered_set<long long int> &end2,
         vector<unordered_map<long long int, long long int>> &vec1,
         vector<unordered_map<long long int, long long int>> &vec2,
         vector<bool> &visited) {
    visited[u - 1] = true;
    bool uEnd = (end1.find(u) != end1.end());
    bool vEnd = (end2.find(v) != end2.end());
    if (vEnd != uEnd) return false;
    if (vec1[u - 1].size() != vec2[v - 1].size())
        return false;
    bool result = true;
    unordered_map<long long int, long long int>::iterator itr;
    for (itr = vec1[u - 1].begin(); itr != vec1[u - 1].end(); itr++) {
        long long int c = (itr->first);
        long long int q1 = itr->second;
        long long int q2;
        if (vec2[v - 1].find(c) == vec2[v - 1].end()) return false;
        else q2 = vec2[v - 1][c];
        if (!visited[q1 - 1]) result = result && dfs(q1, q2, end1, end2, vec1, vec2, visited);
    }
    return result;
}

int main() {
    long long int mod = 1000000000 + 7;

    unordered_set<long long int> endings;

    long long int n, m, k, l;

    cin >> n >> m >> k >> l;

    for (long long int i = 0; i < k; i++) {
        long long int fd;
        cin >> fd;
        endings.insert(fd);
    }

    vector<unordered_map<long long int, long long int>> vec(n);
    for (long long int i = 0; i < m; i++) {
        long long int start, end;
        char ch;
        cin >> start >> end >> ch;
        if (vec[end - 1].empty()) {
            unordered_map<long long int, long long int> map;
            vec[end - 1] = map;
            vec[end - 1][start] = 1;
        } else {
            if (vec[end - 1].find(start) != vec[end - 1].end()) {
                vec[end - 1][start]++;
            } else {
                vec[end - 1][start] = 1;
            }
        }
    }
    //for (long long int i = 0 ;)
    vector<long long int> emVec(l + 1, 0);
    vector<vector<long long int>> mat(n, emVec);
//    showMatrix(mat);
    mat[0][0] = 1;
    for (long long int len = 1; len <= l; len++) {
        for (long long int cond = 0; cond < n; cond++) {
            if (!vec[cond].empty()) {
                unordered_map<long long int, long long int> &beforeConds = vec[cond];
                unordered_map<long long int, long long int>::iterator itr;
                for (itr = beforeConds.begin(); itr != beforeConds.end(); itr++) {
                    long long int prevCond = (itr->first);
                    long long int valuePrevCond = mat[prevCond - 1][len - 1];
                    long long int amountOfPath = itr->second;
                    mat[cond][len] += (valuePrevCond * amountOfPath);
                    mat[cond][len] %= mod;
                }
            }
        }
    }
//    showMatrix(mat);
    long long int ans = 0;
    unordered_set<long long int>::iterator itr;
    for (itr = endings.begin(); itr != endings.end(); itr++) {
        ans += mat[(*itr) - 1][l];
        ans %= mod;
    }
    cout << ans;
    return 0;
}
