#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>

struct TreeNode {
    long long int val;
    long long int min;
    long long int max;
    TreeNode* left;
    TreeNode* right;
};

bool isBST(TreeNode* root, long long int min, long long int max) {
    if (root == nullptr) {
        return true;
    }

    if (root->val < min || root->val >= max) {
        return false;
    }

    return isBST(root->left, min, root->val) && isBST(root->right, root->val, max);
}

int main() {
    std::ifstream in("bst.in");
    std::ofstream out("bst.out");

    int n;
    long long int v;
    in >> n >> v;

    TreeNode* root = new TreeNode{v, LLONG_MIN, LLONG_MAX, nullptr, nullptr};

    bool f = true;

    for (int i = 1; i < n; ++i) {
        long long int key;
        int p;
        std::string s;
        in >> key >> p >> s;
        p--;

        TreeNode* current = root;

        while (p > 0) {
            if (s == "R") {
                current = current->right;
            } else {
                current = current->left;
            }
            p--;
        }

        if (s == "R") {
            if (key < current->max && key >= current->val) {
                current->right = new TreeNode{key, current->val, current->max, nullptr, nullptr};
            } else {
                f = false;
                break;
            }
        } else if (s == "L") {
            if (key >= current->min && key < current->val) {
                current->left = new TreeNode{key, current->min, current->val, nullptr, nullptr};
            } else {
                f = false;
                break;
            }
        }
    }

    if (f && isBST(root, LLONG_MIN, LLONG_MAX)) {
        out << "YES";
    } else {
        out << "NO";
    }

    in.close();
    out.close();
    delete root;

    return 0;
}
