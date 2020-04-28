#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int mode = 998244353;

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

    int degP, degQ;
    cin >> degP >> degQ;
    vector<unsigned> P(degP + 1);
    vector<unsigned> Q(degQ + 1);

    for (int i = 0; i < P.size(); i++) {
        cin >> P[i];
    }

    for (int i = 0; i < Q.size(); i++) {
        cin >> Q[i];
    }

    vector<unsigned> sum(max(degP, degQ) + 1);

    for (int i = 0; i < sum.size(); i++) {
        unsigned a = 0, b = 0;
        if (P.size() > i) a = P[i];
        if (Q.size() > i) b = Q[i];
        sum[i] = add(a, b);
    }

    vector<unsigned> product(degP + degQ + 1, 0);
    for (int i = 0; i < P.size(); i++) {
        for (int j = 0; j < Q.size(); j++) {
            product[i + j] = add(product[i + j], mul(P[i], Q[j]));
        }
    }

    vector<unsigned> division(1000, 0);
    for (int i = 0; i < division.size(); i++) {
        unsigned long long acc = 0;
        int min = Q.size();
        if (min > i + 1) min = i + 1;
        for (int j = 1; j < min; j++) {
            acc = add(acc, mul(division[i - j], Q[j]));
        }
        long long a = ((P.size() > i) ? P[i] : 0) - acc;
        if (a < 0) a += mode;
        division[i] = a;
    }
    cout << sum.size() - 1 << "\n";
    for (auto t : sum) {
        cout << t << " ";
    }
    cout << "\n" << product.size() - 1 << "\n";
    for (auto t : product) {
        cout << t << " ";
    }
    cout << "\n";
    for (auto t : division) {
        cout << t << " ";
    }

}