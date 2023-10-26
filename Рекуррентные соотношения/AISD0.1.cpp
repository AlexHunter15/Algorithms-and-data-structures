#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_N = 105;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    if (!in.is_open()) {
        cout << "Unable to open input file." << endl;
        return 1;
    }

    if (!out.is_open()) {
        cout << "Unable to open output file." << endl;
        return 1;
    }
    int s;
    in >> s;

    vector<int> rows(s + 1);
    vector<int> cols(s + 1);

    for (int i = 0; i < s; ++i) {
        in >> rows[i] >> cols[i];
    }
    rows[s] = cols[s - 1];

    vector<vector<long long>> mtrx(s, vector<long long>(s, LLONG_MAX));
    for (int i = 0; i < s; ++i) {
        mtrx[i][i] = 0;
    }
    for (int len = 2; len <= s; ++len) {
        for (int i = 0; i <= s - len; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                long long cost = mtrx[i][k] + mtrx[k + 1][j] + static_cast<long long>(rows[i]) * cols[k] * cols[j];
                mtrx[i][j] = min(mtrx[i][j], cost);
            }
        }
    }

    out << mtrx[0][s - 1] << endl;

    in.close();
    out.close();
    return 0;
}