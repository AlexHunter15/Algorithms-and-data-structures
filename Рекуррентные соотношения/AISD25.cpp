#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main() {
    ifstream in("in.txt");
    ofstream out("out.txt");

    int x, y, z;
    in >> x >> y >> z;

    string A, B;
    in >> A >> B;

    int n = A.size();
    int m = B.size();

    vector<vector<int>> mtr(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; ++i) {
        mtr[i][0] = i * x;
    }
    for (int j = 0; j <= m; ++j) {
        mtr[0][j] = j * y;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (A[i - 1] == B[j - 1]) {
                mtr[i][j] = mtr[i - 1][j - 1];
            }
            else {
                mtr[i][j] = min(mtr[i - 1][j] + x, min(mtr[i][j - 1] + y, mtr[i - 1][j - 1] + z));
            }
        }
    }

    out << mtr[n][m] << endl;

    in.close();
    out.close();

    return 0;
}
