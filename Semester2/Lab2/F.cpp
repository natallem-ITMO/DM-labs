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

using namespace std;
std::ifstream cin("a.in");
std::ofstream cout("a.out");
//std::ifstream cin("isomorphism.in");
//std::ofstream cout("isomorphism.out");

static void showVector(vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

static void showSet(unordered_set
                            <int> &set) {
    unordered_set<int>::iterator itr;
    for (itr = set.begin(); itr != set.end(); itr++) {
        cout << (*itr) << " ";
    }
    cout << endl;
}

static void showMatrix(vector<vector<int>> &m) {
    for (int i = 0; i < m.size(); i++) {
        showVector(m[i]);
    }
    cout << endl;
}

bool dfs(int u, int v, unordered_set<int> &end1, unordered_set<int> &end2,
         vector<unordered_map<int, int>> &vec1, vector<unordered_map<int, int>> &vec2,
         vector<bool> &visited) {
    visited[u - 1] = true;
    bool uEnd = (end1.find(u) != end1.end());
    bool vEnd = (end2.find(v) != end2.end());
    if (vEnd != uEnd) return false;
    if (vec1[u-1].size() != vec2[v-1].size())
        return false;
    bool result = true;
    unordered_map<int, int>::iterator itr;
    for (itr = vec1[u - 1].begin(); itr != vec1[u - 1].end(); itr++) {
        int c = (itr->first);
        int q1 = itr->second;
        int q2;
        if (vec2[v-1].find(c) == vec2[v-1].end()) return false;
        else q2 = vec2[v-1][c];
        if (!visited[q1 - 1]) result = result && dfs(q1, q2, end1, end2, vec1, vec2, visited);
    }
    return result;
}

int main() {

    unordered_set<int> endings1;
    unordered_set<int> endings2;


    int n1, m1, k1, n2, k2, m2;
    cin >> n1 >> m1 >> k1;

    for (int i = 0; i < k1; i++) {
        int fd;
        cin >> fd;
        endings1.insert(fd);
    }
    unordered_map<int, int> myMap(26);
    for (int i = 0; i < 26; i++) {
        myMap[i] = 0;
    }

    vector<unordered_map<int, int>> vec1(n1);

    for (int i = 0; i < m1; i++) {
        int beg, end;
        char ch;
        cin >> beg >> end >> ch;
        vec1[beg - 1][ch - 'a'] = end;
    }

    cin >> n2 >> m2 >> k2;
    if (n1 != n2 || m1 != m2 || k1 != k2) cout << w;
    else {
        vector<bool> visited(n1, false);
        for (int i = 0; i < k2; i++) {
            int fd;
            cin >> fd;
            endings2.insert(fd);
        }

        vector<unordered_map<int, int>> vec2(n2);

        for (int i = 0; i < m2; i++) {
            int beg, end;
            char ch;
            cin >> beg >> end >> ch;
            vec2[beg - 1][ch - 'a'] = end;
        }
        int x = 10;
        if (dfs(1,1,endings1, endings2, vec1, vec2, visited)) cout << r;
        else cout << w;
    }
    return 0;
}
*/
