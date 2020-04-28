#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

long long mode = 104857601;

long long Q_t(vector<long long> &q, long long n) {
    long long a = q[n];
    if (n % 2 == 1) a=-a;
    a %= mode;
    if (a < 0) a+= mode;
    return a;
}

long long add(long long a, long long b) {
    long long aa = (a + b) % mode;
    if (aa < 0) aa += mode;
    return aa;
}

long long mul(long long a, long long b) {
    long long mm = (a * b) % mode;
    if (mm < 0) mm += mode;
    return mm;
}

long long ans(long long n, long long k, vector<long long> A, vector<long long> q) {
    n--;
    while (n >= k) {
        for (long long i = k; i < 2 * k; i++) {
            A[i] = 0;
            for (long long j = 1; j <= k; j++) {
                A[i] = add(A[i], mul(-q[j], A[i - j]));
            }
        }
        vector<long long> R(2 * k + 1, 0);
        for (long long i = 0; i < q.size(); i++) {
            for (long long j = 0; j < q.size(); j++) {
                R[i + j] = add(R[i + j], mul((long long) q[i], (long long) Q_t(q, j)));
            }
        }
        for (long long i = 0; i < q.size(); i++) {
            q[i] = R[2 * i];
        }
        long long addible = (long long) n % 2;
        for (long long i = 0; i < k; i++) {
            A[i] = A[2 * i + addible];
        }
        n /= 2;
    }
    return A[n];
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

    long long k;
    long long unsigned n;
    cin >> k >> n;
    vector<long long> A(2 * k);
    vector<long long> q(k + 1);

    for (long long i = 0; i < k; i++) {
        cin >> A[i];
    }

    q[0] = 1;
    for (long long i = 0; i < k; i++) {
        cin >> q[i + 1];
        q[i + 1] *= -1;
    }

//    for (long long i = 1; i < 60; i++){
//        cout << i << " = " << ans(i, k, A, q) << "\n";
//    }

    cout << ans(n, k, A, q);

}