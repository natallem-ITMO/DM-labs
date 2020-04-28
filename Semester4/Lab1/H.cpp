#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//int mode = 2;
long long  mode = 998244353;
int k, n;


long long mod(long long a) {
    long long res = a % mode;
    if (res < 0) res += mode;
    return res;
}


unsigned add(unsigned long long a, unsigned long long b) {
    return (a + b) % mode;
}

unsigned mul(long long a, long long b) {
    return (a * b) % mode;
}

/*

unsigned mod(long long a) {
    a %= mode;
    if (a < 0) return a + mode;
    return a;
}
*/

unsigned sub(long long a, long long b) {

    return mod(a - b);
}


vector<vector<long long>> getPaskaleTable() {
    vector<vector<long long>> res(k + 1, vector<long long>());
    for (int i = 0; i < res.size(); i++) {
        res[i].resize(i + 2);
        res[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            res[i][j] = mod(res[i - 1][j - 1] + res[i - 1][j]);
        }
        res[i][i + 1] = 0;
    }
    return res;
}

vector<long long> formKoef(int k, vector<vector<long long >> &paskale) {
    vector<long long> res;
    int sign = 1;
    for (int i = k - 1, j = 0; i >= j; --i, ++j) {
        res.push_back((mod(paskale[i][j]) * sign));
        sign *= -1;
    }
    return res;
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
    cin >> k >> n;


    vector<vector<long long>> paskale = getPaskaleTable();
    vector<long long> P = formKoef(k - 1, paskale);
    vector<long long> Q = formKoef(k, paskale);
    vector<long long> division(n, 0);
    division[0] = P[0];
    for (int i = 1; i < division.size(); i++) {
        long long cur = 0;
        for (int j = 1; j <= i && Q.size() > j; j++) {
//            auto Qj = Q[j];
//            auto div_ij = division[i - j];
//            auto df = (Q[j] * division[i - j]);
            cur = mod(cur + ((Q[j] * division[i - j])));
        }
        cur = -cur;

        if (i < P.size()) {
            cur += P[i];
        }
        division[i] = mod(cur);
    }

    for (auto t : division) {
        cout << t << "\n";
    }

}