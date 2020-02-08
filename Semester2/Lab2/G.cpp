
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

using namespace std;
//std::ifstream cin("a.in");
//std::ofstream cout("a.out");
std::ifstream cin("equivalence.in");
std::ofstream cout("equivalence.out");

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

bool dfs(unordered_set<int> &end1, unordered_set<int> &end2,
         vector<unordered_map<int, int>> &vec1, vector<unordered_map<int, int>> &vec2) {
    queue<pair<int, int>> queue;
    queue.push({1, 1});
    //unordered_set<pair<int, int>> settic;
    unordered_set<string> settic;
   // settic.insert(to_string(1)+" "+to_string(1));
    while (!queue.empty()) {
        pair<int, int> cur = queue.front();
        int u = cur.first;
        int v = cur.second;
        bool uEnd = (end1.find(u) != end1.end());
        bool vEnd = (end2.find(v) != end2.end());
        if (vEnd != uEnd) return false;

        settic.insert(to_string(cur.first)+" "+to_string(cur.second));
        queue.pop();
        for (int i = 0; i < 26; i++) {
            int newCond1, newCond2;
            if (u == 0) newCond1 = 0;
            else {
                if (vec1[u - 1].empty()) newCond1 = 0;
                else if (vec1[u - 1].find(i) == vec1[u - 1].end()) newCond1 = 0;
                else newCond1 = vec1[u - 1][i];
            }
            if (v == 0) newCond2 = 0;
            else {
                if (vec2[v - 1].empty()) newCond2 = 0;
                else newCond2 = (vec2[v - 1].find(i) == vec2[v - 1].end()) ? 0 : vec2[v - 1][i];
            }
            if (!(newCond1 == newCond2 && newCond1 == 0)) {
                if (settic.find(to_string(newCond1)+" "+to_string(newCond2)) == settic.end())
                    queue.push({newCond1, newCond2});
            }
        }

    }
    return true;
}

int main() {

    unordered_set<int> endings1;
    unordered_set<int> endings2;


    int n1, m1, k1, n2, k2, m2;
    cin >> n1 >> m1 >> k1;
    vector<bool> visited1(n1, false);

    for (int i = 0; i < k1; i++) {
        int fd;
        cin >> fd;
        endings1.insert(fd);
    }

    vector<unordered_map<int, int>> vec1(n1);

    for (int i = 0; i < m1; i++) {
        int beg, end;
        char ch;
        cin >> beg >> end >> ch;
        vec1[beg - 1][ch - 'a'] = end;
    }

    cin >> n2 >> m2 >> k2;

    vector<bool> visited2(n2, false);
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
    if (dfs(endings1, endings2, vec1, vec2)) cout << "YES";
    else cout << "NO";
 //   cout << dfs(endings1, endings2, vec1, vec2);


    return 0;
}
