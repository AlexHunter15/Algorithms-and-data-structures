#include <iostream>
#include <fstream>
#include <stack>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <functional>

class SearchTree {
public:
    struct TreeNode {
        int value;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
    };

    TreeNode* root = nullptr;

    SearchTree() : root(nullptr) {}

    ~SearchTree() {
        clear(root);
    }

    void clear(TreeNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    bool New(int value) {
        if (isEmpty()) {
            root = new TreeNode(value);
            return true;
        }

        TreeNode* curr = root;
        while (true) {
            if (curr->value > value) {
                if (curr->left == nullptr) {
                    curr->left = new TreeNode(value);
                    return true;
                }
                else {
                    curr = curr->left;
                }
            }
            else if (curr->value < value) {
                if (curr->right == nullptr) {
                    curr->right = new TreeNode(value);
                    return true;
                }
                else {
                    curr = curr->right;
                }
            }
            else {
                return false;
            }
        }
    }

    bool Delete(int value) {
        return Remove(nullptr, root, value);
    }

    bool Remove(TreeNode* parent, TreeNode* curr, int value) {
        while (curr != nullptr && curr->value != value) {
            parent = curr;
            if (curr->value > value) {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }

        if (curr == nullptr) {
            return false;
        }

        if (curr->left == nullptr || curr->right == nullptr) {
            TreeNode* temp = (curr->right != nullptr) ? curr->right : curr->left;
            if (parent != nullptr) {
                if (parent->right == curr) {
                    parent->right = temp;
                }
                else {
                    parent->left = temp;
                }
            }
            else {
                root = temp;
            }
            delete curr;
            return true;
        }
        else {
            TreeNode* temp = curr->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            curr->value = temp->value;
            return Remove(curr, curr->right, temp->value);
        }
    }

    void leftBP(std::ostream& os) const {
        if (isEmpty()) {
            return;
        }
        std::stack<TreeNode*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            TreeNode* node = nodes.top();
            nodes.pop();
            os << node->value << std::endl;
            if (node->right != nullptr) {
                nodes.push(node->right);
            }
            if (node->left != nullptr) {
                nodes.push(node->left);
            }
        }
    }

    void postBP(std::function<void(TreeNode*)> func) const {
        if (isEmpty()) {
            return;
        }

        std::stack<TreeNode*> s1;
        std::stack<TreeNode*> s2;

        s1.push(root);
        while (!s1.empty()) {
            TreeNode* tempr = s1.top();
            s1.pop();
            if (tempr->left != nullptr) {
                s1.push(tempr->left);
            }
            if (tempr->right != nullptr) {
                s1.push(tempr->right);
            }
            s2.push(tempr);
        }

        while (!s2.empty()) {
            func(s2.top());
            s2.pop();
        }
    }
};

void build(SearchTree& tree) {
    if (tree.isEmpty()) {
        return;
    }

    std::unordered_map<SearchTree::TreeNode*, int> h1;
    std::unordered_map<SearchTree::TreeNode*, int> msl;

    tree.postBP([&h1, &msl](SearchTree::TreeNode* node) {
        SearchTree::TreeNode* right = node->right;
        SearchTree::TreeNode* left = node->left;
        int value = 0;
        if (right != nullptr) {
            value += h1[right] + 1;
        }
        if (left != nullptr) {
            value += h1[left] + 1;
        }
        msl[node] = value;
        int h = 0;
        if (right != nullptr && left != nullptr) {
            h = std::max(h1[right], h1[left]) + 1;
        }
        else if (right != nullptr) {
            h = h1[right] + 1;
        }
        else if (left != nullptr) {
            h = h1[left] + 1;
        }
        h1[node] = h;
        });

    int maxMSL = std::max_element(msl.begin(), msl.end(),
        [](const std::pair<SearchTree::TreeNode*, int>& a, const std::pair<SearchTree::TreeNode*, int>& b) {
            return a.second < b.second;
        })->second;

    std::set<SearchTree::TreeNode*> roots;
    int mxh = 0;
    SearchTree::TreeNode* node = nullptr;

    for (const auto& ent : msl) {
        if (ent.second == maxMSL) {
            roots.insert(ent.first);
            if (mxh < h1[ent.first]) {
                mxh = h1[ent.first];
                node = ent.first;
            }
        }
    }

    SearchTree::TreeNode* p = nullptr;

    if (node->left != nullptr) {
        while (node->left != nullptr) {
            if (node->right != nullptr) {
                if (h1[node->right] > h1[node->left]) {
                    if (!roots.count(node)) {
                        break;
                    }
                }
            }
            p = node;
            node = node->left;
        }
        if (node->right == nullptr) {
            node = p;
        }
        else {
            node = node->right;
            while (node->left != nullptr) {
                if (node->right != nullptr) {
                    if (h1[node->right] > h1[node->left]) {
                        if (!roots.count(node)) {
                            break;
                        }
                    }
                }
                node = node->left;
            }
        }
    }
    else {
        node = node->right;
        while (node->left != nullptr) {
            if (node->right != nullptr) {
                if (h1[node->right] > h1[node->left]) {
                    if (!roots.count(node)) {
                        break;
                    }
                }
            }
            node = node->left;
        }
    }

    tree.Delete(node->value);
}

int main() {
    SearchTree Tree;
    std::ifstream in("in.txt");
    if (in.is_open()) {
        int value;
        while (in >> value) {
            Tree.New(value);
        }
        in.close();
    }
    else {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    build(Tree);

    std::ofstream out("out.txt");
    if (out.is_open()) {
        Tree.leftBP(out);
        out.close();
    }
    else {
        std::cerr << "Failed to open output file." << std::endl;
        return 1;
    }

    return 0;
}
