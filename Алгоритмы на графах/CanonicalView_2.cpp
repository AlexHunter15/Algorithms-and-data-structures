#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;
    in >> n;

    vector<vector<int>> mtr(n, vector<int>(n));
    vector<int> p(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> mtr[i][j];
            if (mtr[i][j] == 1) {
                p[j] = i + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        out << p[i] << " ";
    }

    return 0;
}
