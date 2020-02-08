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

namespace std {
    template<>
    struct hash<pair<int, int>> {
        std::size_t operator()(const pair<int, int> &c) const {
            std::hash<std::string> hash_fn;
            return hash_fn(to_string(c.first) + " " + to_string(c.second));
        }
    };
}

using namespace std;
long long MAX = 1000000000000000000;
// u->v

int main() {

    #ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
    #else
    std::ifstream cin("destroy.in");
    std::ofstream cout("destroy.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    long long s;
    cin >> n >> m >> s;
    vector<unordered_map<int, long long>> edges(n + 1, unordered_map<int, long long>());
//    unordered_map<string, int> edge_to_order_num;
//    vector<string, int> edge_to_order_num;
    unordered_map<pair<int,int>, pair<int, long long>> unused_edges;
//    vector<pair<int, int>> order_num_to_edge(m + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        w = -w;

        if (u == v) continue;
//        edge_to_order_num[to_string(min(u,v)) + " " + to_string(max(u,v))] = i + 1;
        unused_edges[{min(u,v), max(u,v)}] = {i+1, -w};
//        if (u < v) {
//            edge_to_order_num[to_string(u) + " " + to_string(v)] = i + 1;
//            edge_to_order_num[to_string(v) + " " + to_string(u)] = m + i + 1;
//        } else {
//            edge_to_order_num[to_string(u) + " " + to_string(v)] = m + i + 1;
//            edge_to_order_num[to_string(v) + " " + to_string(u)] = i + 1;
//        }

//        order_num_to_edge[i + 1] = {u, v};

        if (edges[u].find(v) != edges[u].end()) {
            edges[u][v] = min(edges[u][v], w);
        } else edges[u][v] = w;
        swap(u, v);
        if (edges[u].find(v) != edges[u].end()) {
            edges[u][v] = min(edges[u][v], w);
        } else edges[u][v] = w;

    }
    unordered_set<int> A({1});
    unordered_set<int> B(n - 1);
    for (int i = 2; i <= n; ++i) {
        B.insert(i);
    }
    vector<pair<int, long long>> weight_to_vertex(n + 1, {0, MAX});
    map<long long, unordered_set<pair<int, int>>> min_edgs;
    for (pair<int, long long> pair : edges[1]) {
        min_edgs[pair.second].insert({1, pair.first});
        weight_to_vertex[pair.first] = {1, pair.second};
    }
    long long res = 0;
    while (!B.empty()) {
        auto min_pair = min_edgs.begin();
        long min_w = min_pair->first;
        auto ptr = min_pair->second.begin();
        int v = ptr->second;

        pair<int,int> to_trash = {ptr->first, ptr->second};
        unused_edges.erase({min(ptr->first, ptr->second), max(ptr->first, ptr->second)});

        A.insert(v);
        res += min_w;
        B.erase(v);
        if (min_pair->second.size() == 1) min_edgs.erase(min_pair);
        else min_pair->second.erase(ptr);
        for (pair<int, long long> p : edges[v]) {
            int u = p.first;
            long long w = p.second;
            pair<int, long long> cur_t_cur_w = weight_to_vertex[u];
            long long cur_w = cur_t_cur_w.second;
            if (B.find(u) != B.end() && w < cur_w) {
                min_edgs[cur_w].erase({cur_t_cur_w.first, u});
                if (min_edgs[cur_w].empty()) min_edgs.erase(cur_w);
                weight_to_vertex[u] = {v, w};
                min_edgs[w].insert({v, u});

            }
        }
    }
    multimap<long long , int> sorted_unused_edges;
    for (auto pair : unused_edges){
        int num_order = pair.second.first;
        long long w = pair.second.second;
        sorted_unused_edges.insert({w,num_order});
    }
    long long sum = 0;
    set<int> result;
    for (auto t : sorted_unused_edges){
        sum+= t.first;
        if (sum > s) break;
        result.insert(t.second);
    }
   cout << result.size() << "\n";

    for (auto t : result){
        cout << t  << " ";
    }

//    cout << res;
}
