#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>

#include <set>
#include <map>
//#include "../../../Helper/show_collections.hpp"
using namespace std;


bool kyhn(int v, vector<bool> & used, vector<vector<int>> & edges, vector<int> & matchings){
    if (used[v]) return false;
    used[v]=true;
    for (auto t : edges[v]){
        if (matchings[t]==0 || kyhn(matchings[t],used,edges,matchings)) {
            matchings[t] = v;
            return true;
        }
    }
    return false;
}

int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#else
    std::ifstream cin("matching.in");
    std::ofstream cout("matching.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> edges(n+1);
//    vector<int> w(n + 1);
    vector<pair<int,int>> w_order(n , {0,0});
    for (int i = 0; i < n; i++) {
//        w_order.push_back({})
        w_order[i].second=i+1;
        cin >> w_order[i].first;
    }
    for (int i = 1; i <=n; i++){
        int b;
        cin >> b;
        edges[i] = vector<int>(b);
        for (int j = 0; j < b; j++){
            cin >>edges[i][j];
        }
    }
    std::sort(w_order.begin(), w_order.end());

    vector<int> matchings(n+1,0);
    vector<bool>used(n+1, false);
    for (int i = w_order.size()-1; i >=0; i--){
        std::fill(used.begin(),used.end(),0);
        kyhn(w_order[i].second,used, edges, matchings);
    }
//    for (auto pair : w_order){
//        std::fill(used.begin(),used.end(),0);
//        kyhn(pair.second,used, edges, matchings);
//    }
    vector<int> reverse_matchings(n + 1,0);

    for (int i = 1; i <= n; i++) {
//        int j  = matchings[i];
        reverse_matchings[matchings[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        cout << reverse_matchings[i] << ' ';
    }

    return 0;


}