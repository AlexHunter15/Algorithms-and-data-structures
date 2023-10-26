#include <iostream>
using namespace std;

const int MOD = 1000000007;

int main() {
    int n, k;
    cin >> n >> k;

    if (k > n) {
        cout << 0;
        return 0;
    }

    int res = 1;
    int m = min(k, n - k);

    for (int i = 0; i < m; ++i) {
        res = (1LL * res * (n - i)) % MOD;

        int inv = 1;
        int b = i + 1;
        int exp = MOD - 2;

        while (exp > 0) {
            if (exp % 2 == 1) {
                inv = (1LL * inv * b) % MOD;
            }
            b = (1LL * b * b) % MOD;
            exp = exp / 2;
        }
        res = (1LL * res * inv) % MOD;
    }

    cout << res;

    return 0;
}