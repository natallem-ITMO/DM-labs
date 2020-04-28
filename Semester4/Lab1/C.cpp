#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

#ifdef MY_DEBUG
    string filename = "a";
    std::ifstream cin(filename + ".in");
    std::ofstream cout(filename + ".out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int k;
    cin >> k;

    vector<int> A(k);
    vector<int> C(k + 1);
    vector<int> P(k);
    C[0] = 1;

    for (int i = 0; i < k; i++) {
        cin >> A[i];
    }

    for (int i = 1; i <= k; i++) {
        int a;
        cin >> a;
        C[i] = -a;
    }


    for (int i = 0; i < k; i++) {
        long long int sum = 0;
        for (int j = 0; j <= i; j++) {
            sum += A[j] * C[i - j];
        }
        P[i] = sum;
    }

    int Psize = P.size();
    for (int i = P.size() - 1; i >= 0; i--) {
        if (P[i] == 0) Psize--;
        else break;
    }
    int Csize = C.size();
    for (int i = C.size() - 1; i >= 0; i--) {
        if (C[i] == 0) Csize--;
        else break;
    }

    cout << Psize - 1 << "\n";
    for (int i = 0; i < Psize; i++) {
        cout << P[i] << " ";
    }
    cout << "\n" << Csize - 1 << "\n";
    for (int i = 0; i < Csize; i++) {
        cout << C[i] << " ";
    }
}