#include <iostream>
const int MOD = 1000000007;
int C[1001][1001];
int main() {
    int n, k;
    scanf_s("%d %d", &n, &k);
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        C[i][i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
    printf("%d\n", C[n][k]);
    return 0;
}






