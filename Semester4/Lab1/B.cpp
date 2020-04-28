#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int mode = 998244353;

int n, m;


long long module(long long a) {
    a %= mode;
    if (a < 0) a += mode;
    return a;
}

long long add(long long a, long long b) {
    return module(a + b);
}

long long mul(long long a, long long b) {
    return module(a * b);
}


vector<vector<int>> mDegrees(vector<int> &input) {
//    try {
    for (int i = input.size(); i < m; i++) {
        input.push_back(0);
    }
    vector<vector<int>> res(m);
    if (m < 2) {
        return res;
    }
    res.at(1) = input;
    for (int i = 2; i < res.size(); i++) {
        vector<int> current_p(m, 0);
        for (int j = 0; j < m; j++) {
            for (int k = 0; k + j < m; k++) {
                current_p.at(j + k) = add(current_p.at(j + k), mul(res.at(i - 1).at(j), input.at(k)));
            }
        }
        res.at(i) = current_p;
    }
    return res;
//    }catch (out_of_range e){
//        cout << "fds";
//        throw out_of_range("dsf");
//    }
}


long long gcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}


long long getMinus1(long long a) {

    long long x, y;
    long long g = gcd(a, mode, x, y);
    if (g != 1 && mode % g == 0 && g <= 0 && a < 0)
        x = (x % mode + mode) % mode;
    return x;
}

vector<int> getExpK() {
    vector<int> res(m);
    res.at(0) = 1;
    for (int i = 1; i < m; i++) {
        res.at(i) = mul(res.at(i - 1), getMinus1(i));
    }
    return res;
}

vector<int> getSqrtK(vector<int> &expK) {
    vector<int> res(m, 1);
    res.at(0) = -1;
    for (int i = 1; i < m; i++) {
        res.at(i) = mul(-res.at(i - 1), getMinus1(i * 2));
        if (i > 2) {
            res.at(i) = mul(res.at(i), 2 * (i - 2) + 1);
        }
    }
    res.at(0) = 1;
    return res;
}

vector<int> getLnK() {
    vector<int> res(m);
    res.at(0) = 0;
    for (int i = 1; i < m; i++) {
        res.at(i) = module(mul((i % 2 == 0) ? -1 : 1, getMinus1(i)));
    }
    return res;
}

vector<int> createAns(vector<vector<int>> &inputDegrees, vector<int> &K) {
//    auto K = getExpK();
    vector<int> res(m);
    res.at(0) = K.at(0);
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < m; j++) {
            res.at(j) = add(res.at(j), mul(inputDegrees.at(i).at(j), K.at(i)));
        }
    }
    return res;

}


void showOutput(vector<int> &vector) {
    for (auto t : vector) {
        cout << t << " ";
    }
    cout << "\n";
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
    vector<int> KExp;
    vector<int> KLn;
    vector<int> KSqrt;
    vector<int> resExp;
    vector<int> resSqrt;
    vector<int> resLn;
    vector<vector<int>> degree_m;
    cin >> n >> m;

    vector<int> input(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> input.at(i);
    }
   degree_m = mDegrees(input);
    KExp = getExpK();
    KLn = getLnK();
    KSqrt = getSqrtK(KExp);

    resExp = createAns(degree_m, KExp);
    resSqrt = createAns(degree_m, KSqrt);
    resLn = createAns(degree_m, KLn);

    showOutput(resSqrt);
    showOutput(resExp);
    showOutput(resLn);
}