#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }

    vector<vector<int>> mtr(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1]) {
                mtr[i][j] = mtr[i - 1][j - 1] + 1;
            }
            else {
                mtr[i][j] = max(mtr[i - 1][j], mtr[i][j - 1]);
            }
        }
    }

    int k = mtr[n][n];
    cout << k << endl;

    vector<int> indA, indB;
    int i = n, j = n;
    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1]) {
            indA.push_back(i - 1);
            indB.push_back(j - 1);
            i--;
            j--;
        }
        else if (mtr[i - 1][j] > mtr[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    for (int t = k - 1; t >= 0; t--) {
        cout << indA[t] << " ";
    }
    cout << endl;
    for (int t = k - 1; t >= 0; t--) {
        cout << indB[t] << " ";
    }
    cout << endl;

    return 0;
}
