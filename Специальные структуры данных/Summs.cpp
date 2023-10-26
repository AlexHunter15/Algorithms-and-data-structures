#include <iostream>
#include <vector>

using namespace std;

struct SegmentTreeNode {
    long long sum;
    long long lazy;

    SegmentTreeNode() : sum(0), lazy(0) {}
};

class SegmentTree {
public:
    SegmentTree(vector<long long>& arr) : n(arr.size()) {
        tree.resize(4 * n);
        build(arr);
    }

    void update(int index, long long value) {
        index += n;
        tree[index].sum += value;
        for (index >>= 1; index > 0; index >>= 1) {
            tree[index].sum = tree[index << 1].sum + tree[(index << 1) + 1].sum;
        }
    }

    long long query(int l, int r) {
        l += n; 
        r += n;
        long long result = 0;
        while (l < r) {
            if (l & 1) {
                result += tree[l].sum;
                l++;
            }
            if (r & 1) {
                r--;
                result += tree[r].sum;
            }
            l >>= 1;
            r >>= 1;
        }
        return result;
    }

private:
    int n;
    vector<SegmentTreeNode> tree;

    void build(vector<long long>& arr) {
        for (int i = 0; i < n; i++) {
            tree[i + n].sum = arr[i];
        }
        for (int i = n - 1; i > 0; i--) {
            tree[i].sum = tree[i << 1].sum + tree[(i << 1) + 1].sum;
        }
    }
};

int main() {
    int n;
    cin >> n;

    vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    SegmentTree segmentTree(arr);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        string query_type;
        cin >> query_type;
        if (query_type == "Add") {
            int ind;
            long long val;
            cin >> ind >> val;
            segmentTree.update(ind, val);
        }
        else if (query_type == "FindSum") {
            int l, r;
            cin >> l >> r;
            cout << segmentTree.query(l, r) << endl;
        }
    }

    return 0;
}
