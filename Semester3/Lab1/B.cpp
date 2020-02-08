


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

void showList(list<int> &l, string s = "") {
    if (!s.empty())
        cout << s << endl;
    for (auto i : l) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
//#ifdef MY_DEBUG
    std::ifstream cin("chvatal.in");
    std::ofstream cout("chvatal.out");
//#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;//n<=100
    cin >> n;

    vector<vector<int>> edges(n + 1, vector<int>(n + 1, 0));
    list<pair<int, int>> added;

    for (int i = 2; i <= n; i++) {
        string s;
        cin >> s;
        int ptr = 1;
        for (char c : s) {
            if (c == '0') {
                added.push_back({i, ptr});
            }
            edges[i][ptr] = 1;
            edges[ptr][i] = 1;
            ptr++;
        }
    }
    reverse(added.begin(), added.end());
    list<int> l;
//    vector<vector<int>> cycleEdges(n+1, vector<int>(n+1,0));


    for (int i = 1; i <= n; i++) {

        l.push_back(i);
    }
//    showList(l);
    int c = 0;
//    cout << "HERE";

    while (!added.empty()) {
        c++;
//        if (c > 100) return 0;
        auto[u, v]= added.front();
        added.pop_front();
        edges[u][v] = 0;
        edges[v][u] = 0;
//        cout << u << " " << v << endl;
//        showList(l, "u v ^");

        auto ptr = l.begin();
        for (; ptr != l.end(); ++ptr) {

            auto uu = *ptr;
            int vv;
            if (++ptr == l.end()) {
                vv = *l.begin();
//                cout << " HERE";
            } else {
                vv = *(ptr);
            }
            --ptr;
//            cout << "cur edge " << uu << " " << vv << endl;
            if ((uu == u && vv == v) || (uu == v && vv == u)) {
//                showList(l, "found");
                if (ptr!=l.begin()) l.splice(l.begin(), l, ptr, l.end());
//                showList(l, "after slice");

                auto iter_0 = l.begin();
                auto iter_i = ++(l.begin());
                if (!edges[*iter_0][*iter_i]) {
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
//                    cout << counter << "=counter\n";
                    for (int i = 1; i <= counter / 2; i++) {
                        swap(*iterA, *iterB);
                        iterA++;
                        iterB--;
                    }
//                    l.push_back((*l.begin()));
//                    l.pop_front();
//                    showList(l, "after swap");

                }
                break;
            }
        }
    }
//    cout << " ans";
    for (auto i : l) {
        cout << i << " ";
    }
}