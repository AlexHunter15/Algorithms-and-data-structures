#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

struct Node {
    int sum;
    int min;
    int max;
};

void build(vector<Node>& tree, const vector<int>& arr, int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = { arr[tl], arr[tl], arr[tl] }; 
    }
    else {
        int tm = (tl + tr) / 2;
        build(tree, arr, v * 2, tl, tm);
        build(tree, arr, v * 2 + 1, tm + 1, tr);

        tree[v].sum = tree[v * 2].sum + tree[v * 2 + 1].sum;
        tree[v].min = min(tree[v * 2].min, tree[v * 2 + 1].min);
        tree[v].max = max(tree[v * 2].max, tree[v * 2 + 1].max);
    }
}

void update(vector<Node>& tree, vector<int>& arr, int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        arr[tl] = new_val;
        tree[v] = { new_val, new_val, new_val }; 
    }
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            update(tree, arr, v * 2, tl, tm, pos, new_val);
        }
        else {
            update(tree, arr, v * 2 + 1, tm + 1, tr, pos, new_val);
        }

        tree[v].sum = tree[v * 2].sum + tree[v * 2 + 1].sum;
        tree[v].min = min(tree[v * 2].min, tree[v * 2 + 1].min);
        tree[v].max = max(tree[v * 2].max, tree[v * 2 + 1].max);
    }
}

Node query(vector<Node>& tree, int v, int tl, int tr, int l, int r) {
    if (l > r) {
        return { 0, INT_MAX, INT_MIN };
    }
    if (l == tl && r == tr) {
        return tree[v];
    }

    int tm = (tl + tr) / 2;
    Node left = query(tree, v * 2, tl, tm, l, min(r, tm));
    Node right = query(tree, v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);

    Node result;
    result.sum = left.sum + right.sum;
    result.min = min(left.min, right.min);
    result.max = max(left.max, right.max);
    return result;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n;
    input >> n;
    vector<int> arr(n);

    vector<Node> tree(4 * n);
    build(tree, arr, 1, 0, n - 1);

    int type;
    while (input >> type && type != 0) {
        if (type == 1) {
            int i, v;
            input >> i >> v;
            update(tree, arr, 1, 0, n - 1, i, v);
        }
        else if (type == 2) {
            int a, b, v;
            input >> a >> b >> v;
            for (int i = a; i <= b; i++) {
                update(tree, arr, 1, 0, n - 1, i, arr[i] + v);
            }
        }
        else if (type == 3) {
            int a, b;
            input >> a >> b;
            Node result = query(tree, 1, 0, n - 1, a, b);
            output << result.sum << endl;
        }
        else if (type == 4) {
            int a, b;
            input >> a >> b;
            Node result = query(tree, 1, 0, n - 1, a, b);
            output << result.min << endl;
        }
        else if (type == 5) {
            int a, b;
            input >> a >> b;
            Node result = query(tree, 1, 0, n - 1, a, b);
            output << result.max << endl;
        }
    }

    input.close();
    output.close();

    return 0;
}
