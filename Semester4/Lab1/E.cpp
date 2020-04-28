#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int r, d;

vector<int> p;
static vector<vector<long long>> K = {
        {1},//0
        {0, 1},//1
        {0, 1, 1},//2
        {0, 1, 4,    1},//3
        {0, 1, 11,   11,    1}, //4
        {0, 1, 26,   66,    26,     1}, //5
        {0, 1, 57,   302,   302,    57,      1}, //6
        {0, 1, 120,  1191,  2416,   1191,    120,     1}, //7
        {0, 1, 247,  4293,  15619,  15619,   4293,    247,    1}, // 8
        {0, 1, 502,  14608, 88234,  156190,  88234,   14608,  502,   1}, //9
        {0, 1, 1013, 47840, 455192, 1310354, 1310354, 455192, 47840, 1013, 1} //10
};


vector<long long> mulPoly(const vector<long long> &A, const vector<long long> &B) {
    vector<long long> res(A.size() + B.size() - 1);
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {
            res[i + j] += A[i] * B[j];
        }
    }
    return res;
}

void add(vector<long long> &A, vector<long long> &B) {
    for (int i = 0; i < B.size(); i++) {
        A[i] += B[i];
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
    cin >> r >> d;

    p.resize(d + 1);

    for (int i = 0; i <= d; i++) {
        cin >> p[i];
    }

    vector<long long> P(d + 1, 0);
    vector<long long> Q(1, 1);
    for (int i = 0; i < p.size(); i++) {
        vector<long long> init = mulPoly({p[i]}, K[i]);
        for (int j = i + 1; j <= d; j++) {
            init = mulPoly(init, {1, -1});
        }
        add(P, init);
    }

    for (int i = 0; i < d + 1; i++) {
        Q = mulPoly(Q, {1, -r});
    }

    int realSizeP = P.size();

    for (int i = P.size() - 1; i >= 0; i--) {
        if (P[i] == 0) {
            realSizeP--;
        } else {
            break;
        }
    }

    long long R = 1;
    for (int i = 0; i < realSizeP; i++) {
        P[i] *= R;
        R *= r;
    }

    int realSizeQ = Q.size();

    for (int i = Q.size() - 1; i >= 0; i--) {
        if (Q[i] == 0) {
            realSizeP--;
        } else {
            break;
        }
    }


    cout << realSizeP - 1 << "\n";
    for (int i = 0; i < realSizeP; i++) {
        cout << P[i] << " ";
    }
    cout << "\n" << Q.size() - 1 << "\n";
    for (auto t : Q) {
        cout << t << " ";
    }

}