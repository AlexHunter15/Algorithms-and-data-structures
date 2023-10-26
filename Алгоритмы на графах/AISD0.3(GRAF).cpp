#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m;
    in >> n >> m;

    vector<vector<int>> arr(n);
    vector<int> num(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        in >> u >> v;
        u--;
        v--;
        arr[u].push_back(v);
        arr[v].push_back(u); 
        num[u]++;
        num[v]++;
    }

    for (int i = 0; i < n; i++) {
        out << num[i] << " "; 
        for (int j : arr[i]) {
            out << j + 1 << " "; 
        }
        out << endl;
    }

    in.close();
    out.close();

    return 0;
}
