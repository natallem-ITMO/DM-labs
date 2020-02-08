#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <list>
#include <fstream>
#include <string>
#include <climits>
#include <queue>
#include <numeric>
#include <iterator>
#include <random>

using namespace std;
int n;
vector<vector<int>> edges(n + 1, vector<int>(n + 1, 0));

//#include "../../../Helper/show_collections.hpp"


void showList(list<int> &l, string s = "") {
    if (!s.empty())
        cout << s << endl;
    for (auto i : l) {
        cout << i << " ";
    }
    cout << endl;
}

bool comp(int i, int j ){
    return (edges[i][j]);
//    cout << 1 << " "<< i << " " << j << "\n";
//    cout.flush();
//    string ans;
//    cin >> ans;
//    return (ans == yes);//YES
}


int main() {

//#ifdef MY_DEBUG
    std::ifstream cin("guyaury.in");
    std::ofstream cout("guyaury.out");
//#endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

//    int n;
    cin >> n;
    edges.resize(n + 1, vector<int>(n + 1, 0));
//    vector<vector<int>> edges(n + 1, vector<int>(n + 1, 0));
    for (int i = 2; i <= n; i++) {
        string s;
        cin >> s;
        int ptr = 1;
        for (char c : s) {
            if (c == '1') {
                edges[i][ptr] = 1;
            } else {
                edges[ptr][i] = 1;
            }
            ptr++;
        }
    }
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    std::random_device rd;
    std::mt19937 g(rd());

    while(true) {

        std::shuffle(v.begin(), v.end(), g);

//        copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
//        std::cout << "\n";

        stable_sort(v.begin(), v.end(), comp);
        bool ok = true;
        for (int i = 0 ; i < v.size()-1; i++){
            if (!edges[v[i]][v[i+1]]) {
                ok = false;
                break;
            }
        }
        if (!edges[v[n-1]][v[0]]) {
            ok=false;
//            break;
        }
        if (ok) {
            for (auto i : v){
                cout << i << " ";
            }
            return 0;
        }

    }

}