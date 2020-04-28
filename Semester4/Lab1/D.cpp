#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

using ui = uint64_t;

struct num {
    ui up;
    ui down;
    int sign;

    num() : up(0), down(1), sign(1) {}

    num(ui up, ui down, ui sing) : up(up), down(down), sign(sing) {}

    num(const pair<ui, ui> &p, int sign) : up(p.first), down(p.second), sign(sign) {

    }

    string toString() {
        string s = (sign < 0) ? "-" : "";
        return s + to_string(up) + "/" + to_string(down);
    }
};

int r, k;
ui kfuc;
int signr;

vector<num> a;
vector<int> p;
vector<num> q;
vector<ui> degr;

int getSign(long long t) {
    if (t >= 0) return 1;
    return -1;
}

void signR() {
    signr = 1;
    if (r < 0) signr = -1;
}

void degree() {
    degr.resize(k + 1);
    degr[0] = 1;
    ui rr = (r < 0) ? -r : r;
    for (int i = 1; i <= k; i++) {
        degr[i] = degr[i - 1] * rr;
    }
}

ui gcd(ui x, ui y) {
    while (x != 0 && y != 0) {
        if (x > y) {
            x = x % y;
        } else {
            y = y % x;
        }
    }
    return (x == 0) ? y : x;
}

pair<ui, ui> simplify(ui u, ui d) {
    auto GCD = gcd(u, d);
    if (GCD == 0) {
        return {u, d};
    }
    return {u / GCD, d / GCD};
}

ui fact(ui t) {
    ui st = 1;
    for (ui i = 1; i <= t; i++) {
        st *= i;
    }
    return st;
}


num mul(const num &a, const num &b) {
    ui up = a.up * b.up;
    ui down = a.down * b.down;
    int s = a.sign * b.sign;
    return num(simplify(up, down), s);
}

// a/b + c/d

num sum(const num &a, const num &b) {
    ui nod = gcd(a.down, b.down);
    ui d_nod = b.down / nod;
    ui b_nod = a.down / nod;

    ui aa = a.up * d_nod;
    ui cc = b.up * b_nod;

    int sign = 1;

    if (a.sign < 0 && b.sign < 0) {
        aa += cc;
        sign = -1;
    } else if (a.sign < 0) {
        if (aa > cc) {
            aa -= cc;
            sign = -1;
        } else {
            aa = cc - aa;
        }
    } else if (b.sign < 0) {
        if (aa < cc) {
            aa = cc - aa;
            sign = -1;
        } else {
            aa -= cc;
        }
    } else {
        aa += cc;
    }
    ui down = a.down * d_nod;
    return num(simplify(aa, down), sign);

/*
    if (a.sign < 0 && b.sign < 0 ||
        a.sign < 0 && a.
            ) {
        sign = -1;
    }

    long long x = b.down * a.up * a.sign;
    long long y = a.down * b.up * b.sign;
    long long xy = x + y;
    ui by = a.down * b.down;
    if (xy < 0) xy *= -1;
    return num(simplify(xy, by), sign);*/
}

vector<long long> mulPoly(vector<long long> &A, const vector<long long> &B) {
    vector<long long> res(A.size() + B.size() - 1);
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {
            res[i + j] += A[i] * B[j];
        }
    }
    return res;
}

vector<long long> getPoly(int i) {
    vector<long long> res = {k - i, 1};
    for (int j = k - i - 1; j >= 1 - i; j--) {
        res = mulPoly(res, {j, 1});
    }
    return res;
}

void makeRes(vector<num> &result) {

    for (int i = 0; i <= k; i++) {
        if (i == 3) {
            int x = 13;
        }
        vector<long long> poly = getPoly(i);
        int sign = signr;
        if (p[i] < 0) sign = -sign;
        if (signr == -1 && i % 2 == 0) sign = -sign;
        ui down = degr[i] * kfuc;
        auto kk = kfuc;
        ui up = (p[i] > 0) ? p[i] : -p[i];
        auto pair = simplify(down, up);
        down = pair.first;
        up = pair.second;
        for (int j = 0; j < poly.size(); j++) {
            int s = getSign(poly[j]);
            long long uu = poly[j] * s;
            s *= sign;
            ui u = uu;
            auto pair = simplify(u, down);
            u = pair.first;
            ui d = pair.second;
            u *= up;
            num res = num(simplify(u, d), s);
            result[j] = sum(result[j], res);
        }

    }

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

    cin >> r >> k;
    signR();
    a.resize(k + 1);
    p.resize(k + 1);
    degree();
    kfuc = fact(k);

    for (int i = 0; i <= k; i++) {
        cin >> p[i];
    }

    vector<num> result(k + 1);

    makeRes(result);
    for (auto &t : result) {
        cout << t.toString() << " ";
    }

}