#include <iostream>
#include <fstream>

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

TreeNode* Min(TreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

TreeNode* remove(TreeNode* root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->key) {
        root->left = remove(root->left, key);
    }
    else if (key > root->key) {
        root->right = remove(root->right, key);
    }
    else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        TreeNode* temp = Min(root->right);
        root->key = temp->key;
        root->right = remove(root->right, temp->key);
    }

    return root;
}

void inorderBP(TreeNode* root, ofstream& outFile) {
    if (root == nullptr) {
        return;
    }

    outFile << root->key << endl;
    inorderBP(root->left, outFile);
    inorderBP(root->right, outFile);
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int del;
    in >> del;

    TreeNode* root = nullptr;
    int key;

    while (in >> key) {
        root = insert(root, key);
    }

    root = remove(root, del);
    inorderBP(root, out);

    in.close();
    out.close();

    return 0;
}
