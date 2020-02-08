#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <unordered_set>

using namespace std;
std::ifstream cin("problem1.in");
std::ofstream cout("problem1.out");

static void showVector(vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

static void showMatrix(vector<vector<int>> &m) {
    for (int i = 0; i < m.size(); i++) {
        showVector(m[i]);
    }
    cout << endl;
}

int main() {
    unordered_set<int> endings;
    string str;
    int n, m, k;
    cin >> str;
    cin >> n >> m >> k;

    for (int i = 0; i < k; i++) {
        int fd;
        cin >>fd;
        endings.insert(fd);
    }
    vector<int> vec(26, 0);
    vector<vector<int>> matrix(n, vec);
    for (int i = 0; i < m; i++) {
        int start, end;
        char ch;
        cin >> start >> end >> ch;
        matrix[start - 1][ch - 'a'] = end;
    }
   // showMatrix(matrix);
    int curCond = 1;
    bool can = 1;

    for (int i = 0; i < str.length(); i++) {
        char curChar = str[i];
        int nextCond = matrix[curCond-1][curChar - 'a'];
        if (nextCond == 0) {
            can = 0;
            break;
        } else {
            curCond = nextCond;
        }
    }
    if (!can) cout << "Rejects";
    else{
        if (endings.find(curCond) == endings.end()){
            cout << "Rejects";
        } else cout << "Accepts";
    }


    return 0;
}
