#include <iostream>
#include <fstream>
#include <vector>

const int empty = -1;

int hash(int x, int m, int c, int i) {
    return ((x % m) + c * i) % m;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int m, c, n;
    in >> m >> c >> n;

    std::vector<int> a(m, empty);

    for (int j = 0; j < n; j++) {
        int x;
        in >> x;
        int i = 0;
        int ind;
        do {
            ind = hash(x, m, c, i);
            if (a[ind] == x || a[ind] == empty) {
                break;
            }
            i++;
        } while (true);
        a[ind] = x;
    }

    in.close();

    for (int i = 0; i < m; ++i) {
        out << a[i] << " ";
    }

    out.close();

    return 0;
}