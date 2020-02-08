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

long long maximum = 0;
vector<pair<int, int>> w_pair;
vector<int> w;
int n;
unordered_set<uint32_t> cycles;
//unordered_set<uint32_t> checked;


void recursive_insert(uint32_t num, int ii) {
    if (cycles.find(num)!=cycles.end()) return;
    for (int i = ii; i <= n; i++) {
        if ((num & (1 << (i-1))) == 0) {
            recursive_insert(num | (1 << (i-1)), i+1);
        }
    }
    cycles.insert(num);
}

void add_to_cycles(vector<int> &vec) {
    uint32_t num = 0;
    for (int i = 0; i < vec.size(); i++) {
        num |= (1 << (vec[i]-1));
    }
    recursive_insert(num,1);
}

int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#else
    std::ifstream cin("cycles.in");
    std::ofstream cout("cycles.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int m;
    cin >> n >> m;
    w_pair.resize(n, {0, 0});
    w.resize(n + 1);
    for (int i = 0; i < n; i++) {
        w_pair[i].second = i + 1;
        cin >> w_pair[i].first;
        w[i + 1] = w_pair[i].first;
    }
    std::sort(w_pair.begin(), w_pair.end());
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        vector<int> vec(k);
        for (int j = 0; j < k; j++) {
            cin >> vec[j];
        }
        add_to_cycles(vec);
    }

    uint32_t result = 0;
    unordered_set<uint32_t> &cycles1 = cycles;

    for (int i = w_pair.size() - 1; i >= 0; i--) {
//        int a = w_pair[i].second;

        if (cycles.find(result | (1 << (w_pair[i].second-1))) == cycles.end()) {
            result |= (1 << (w_pair[i].second-1));
        }
    }
    long long sum = 0;

    for (int i = 1; i <= n; i++) {

        if ((result & (1 << (i-1))) != 0) sum += w[i];
    }
//    cout << (1 << 1);

    cout << sum;

    return 0;
}