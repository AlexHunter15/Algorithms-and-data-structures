#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;

    vector<int> arr(n, 0); 

    for (int i = 1; i < n; i++) {
        int u, v;
        in >> u >> v;
        arr[v - 1] = u;
    }

    for (int i = 0; i < n; i++) {
        out << arr[i] << " ";
    }
    out << endl;

    in.close();
    out.close();

    return 0;
}
