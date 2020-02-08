


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


//#include "../../../Helper/show_collections.hpp"

using namespace std;

int main() {
//#ifdef MY_DEBUG
    std::ifstream cin("fullham.in");
    std::ofstream cout("fullham.out");
//#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;//n<=4000
    cin >> n;
    vector<vector<int>> edges(n + 1, vector<int>(n + 1, 0));
    for (int i = 2; i <= n; i++) {
        string s;
        cin >> s;
        int ptr = 1;
        for (char c : s) {
            if (c == '1') {
                edges[i][ptr] = 1;
                edges[ptr][i] = 1;
            }
            ptr++;
        }
    }
    list<int> l;

    for (int i = 1; i <= n; i++) {
        l.push_back(i);
    }
    for (int k = 0; k < n * (n - 1); k++) {
        auto iter_0 = l.begin();
        auto iter_i = ++(l.begin());
        if (!edges[*iter_0][*iter_i]) {
//            cout << " here";
            int counter = 2;
            auto iter_1 = iter_i;
            iter_i++;
            auto iter_i1 = ++iter_i;
            --iter_i;
            while (!(edges[*iter_0][*iter_i] && edges[*iter_1][*iter_i1])) {
                counter++;
                ++iter_i;
                ++iter_i1;
            }
            auto iter_end = iter_i;
            auto iterA = ++l.begin();
            auto iterB = iter_i;
            for (int i = 1; i <= counter / 2; i++) {
                swap(*iterA,*iterB);
                iterA++;
                iterB--;
            }
        }
        l.push_back((*l.begin()));
        l.pop_front();
    }
    for (auto i : l) {
        cout << i << " ";
    }
}