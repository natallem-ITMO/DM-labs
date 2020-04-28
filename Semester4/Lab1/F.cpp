#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;
int mode = 1000000007;

unsigned add(unsigned long long a, unsigned long long b) {
    return (a + b) % mode;
}

unsigned mul(unsigned long long a, unsigned long long b) {
    return (a * b) % mode;
}

int main() {
#ifdef MY_DEBUG
    string filename = "a";
    std::ifstream cin(filename + ".in");
    std::ofstream cout(filename + ".out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int k,m;
    cin >> k >> m;
    set<int> c;
    for (int i = 0; i < k; i++){
        int a;
        cin >> a;
        c.insert(a);
    }
    vector<unsigned> w(m+1);
    w[0] = 1;
    unordered_map<unsigned, unsigned> mapa;
    mapa.insert({0,1});
    for (int i = 1; i <= m; i++){
        unsigned possible = 0;
        for (auto core : c){
            if (core > i) continue;
            possible = add(possible, mapa[i-core]);
        }
        w[i] = possible;
        for (int j = 0; j < i; j++){
            mapa[i+j] = add(mapa[i+j], mul(w[j]*2, w[i]));
        }
        mapa[i+i] = add(mapa[i+i], mul(w[i], w[i]));
    }
    for (int i = 1; i <= m; i++){
        cout << w[i] << " ";
    }
}