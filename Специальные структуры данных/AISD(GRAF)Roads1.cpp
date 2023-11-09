#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

vector<long long> p, s;

tuple<long long, vector<long long>> FindSet(long long x) {
    vector<long long> anc;
    while (x != p[x]) {
        anc.push_back(x);
        x = p[x];
    }

    for (long long anc : anc) {
        p[anc] = x;
    }

    return make_tuple(x, anc);
}

void Union(long long x, long long y) {
    tie(x, ignore) = FindSet(x);
    tie(y, ignore) = FindSet(y);
    if (x != y) {
        p[y] = x;
        s[x] += s[y];
    }
}

int main() {
    ios::sync_with_stdio(false);
    ifstream in("input.txt");
    ofstream out("output.txt");
    long long n, q;
    in >> n >> q;
    p.resize(n + 1);
    s.resize(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }
    long long cmp = n;

    for (int i = 0; i < q; i++) {
        long long u, v;
        in >> u >> v;
        long long r1, r2;
        tie(r1, ignore) = FindSet(u);
        tie(r2, ignore) = FindSet(v);

        if (r1 != r2) {
            Union(u, v);
            cmp--;
        }

        out << cmp << endl;
    }

    in.close();
    out.close();
    return 0;
}
