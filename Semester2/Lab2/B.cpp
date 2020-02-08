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
std::ifstream cin("problem2.in");
std::ofstream cout("problem2.out");
//std::ofstream cout("a.out");

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
        cout << (*itr)<<" ";
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
        cin >> fd;
        endings.insert(fd);
    }

    unordered_map<int, vector<int>> myMap(26);
    for (int i = 0; i < 26; i++) {
        vector<int> ccc(1, 0);
        myMap[i] = ccc;
    }
//    showVector(myMap[3]);
    vector<unordered_map<int, vector<int>>> vec(n, myMap);
//    unordered_map<int, vector<int>> myMap2 = vec[1];
//    showVector(myMap2[1]);
    unordered_set<int> curConditions;

    curConditions.insert(1);


    for (int i = 0; i < m; i++) {
        int start, end;
        char ch;
        cin >> start >> end >> ch;
        vec[start - 1][(ch - 'a')].push_back(end);
    }
    int can = 1;
    for (int i = 0; i < str.length(); i++) {
        unordered_set<int> nextConditions;
        char curChar = str[i];
        unordered_set<int>::iterator itr;
        for (itr = curConditions.begin(); itr != curConditions.end(); itr++) {
            int curCond = (*itr);
            vector<int> possibleConditions = vec[curCond - 1][curChar - 'a'];
            for (int t:possibleConditions) {
                if (t != 0)
                    nextConditions.insert(t);
            }
        }
        //cout<<curChar<< " next=";
//        showSet(nextConditions);
        if (nextConditions.empty()) {
            can = 0;
            break;
        } else
            curConditions = nextConditions;

    }
    if (!can) cout <<"Rejects";
    else {
        can = 0;
        unordered_set<int>::iterator itr;
        for (itr = curConditions.begin(); itr != curConditions.end(); itr++) {
            int endingCond = (*itr);
            if (endings.find(endingCond) != endings.end()) {
                can = 1;
                cout << "Accepts";
                break;
            }
        }
        if (!can) cout <<"Rejects";
    }






/*


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
*/


    return 0;
}
