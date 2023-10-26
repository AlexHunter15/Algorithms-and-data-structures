#include <iostream>
#include <fstream>
#include <set>

using namespace std;

struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : key(val), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int key) {
    if (root == nullptr) {
        return new TreeNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    }
    else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

void leftBP(TreeNode* root, ofstream& outFile) {
    if (root == nullptr) {
        return;
    }

    outFile << root->key << endl;
    leftBP(root->left, outFile);
    leftBP(root->right, outFile);
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    TreeNode* root = nullptr;
    int key;
    set<int> k;

    while (in >> key) {
        if (k.find(key) == k.end()) {
            root = insert(root, key);
            k.insert(key);
        }
    }

    leftBP(root, out);

    in.close();
    out.close();

    return 0;
}
