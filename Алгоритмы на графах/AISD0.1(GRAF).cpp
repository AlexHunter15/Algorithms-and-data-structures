#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m;
    in >> n >> m;

    vector<vector<int>> mtr(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int u, v;
        in >> u >> v;
        u--;
        v--;  
        mtr[u][v] = 1;
        mtr[v][u] = 1; 
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            out << mtr[i][j] << " ";
        }
        out << endl;
    }

    in.close();
    out.close();

    return 0;
}
