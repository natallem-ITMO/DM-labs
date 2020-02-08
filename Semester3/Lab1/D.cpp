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


using namespace std;

//#include "../../../Helper/show_collections.hpp"


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
    std::ifstream cin("guyaury.in");
    std::ofstream cout("guyaury.out");
//#endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> edges(n + 1, vector<int>(n + 1, 0));
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
    list<int> path;
//    show_collection(edges);
    path.push_back(1);
    for (int i = 2; i <= n; i++) {
        auto itr = path.begin();
        for (; itr != path.end(); itr++) {
            //uitr -> uk
            if (!edges[*itr][i]) break;
        }
        path.insert(itr, i);
//        showList(path, "after insert" + to_string(i));
    }
    auto itr = ++path.begin();
//    l.splice(l.begin(), l, ptr, l.end());
    for (; itr != path.end() && edges[*itr][*path.begin()]; ++itr);

    //itr = end();
    if (itr==path.end()) {
        for (auto i : path) {
            cout << i << " ";
        }
        return 0;
    }
    list<int> cycle;
    cycle.splice(cycle.begin(), path,path.begin(), itr);
//    showList(cycle, "cycle");
    while(!path.empty()){

        for(auto iter_path = path.begin(); iter_path!=path.end(); ++iter_path){
//            showList(path,"before splice path");
//            showList(cycle, "before cycle path");

            auto iter_cycle = cycle.begin();
            for (; iter_cycle!=cycle.end(); ++iter_cycle){
                if (edges[*iter_path][*iter_cycle]) break;
            }
            if (iter_cycle!=cycle.end()){
                cycle.splice(iter_cycle,path, path.begin(), ++iter_path);
                break;
            }
        }
//        showList(path,"after splice path");
//        showList(cycle, "after cycle path");
    }

    for (auto i : cycle) {
        cout << i << " ";
    }









}