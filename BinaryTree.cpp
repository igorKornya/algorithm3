#include <iostream>
#include <vector>

using namespace std;

struct TNode {
    int data;
    TNode* left;
    TNode* right;
    TNode* parent;

    TNode(int _data) {
        data = _data;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class BinaryThree {
public:
    TNode* root;

    BinaryThree() { root = nullptr; }
    BinaryThree(int k) { root = new TNode(k); }

    TNode* addLeft(TNode* curr, int new_k) {
        if (curr->left == nullptr) {
            TNode* new_l_node = new TNode(new_k);
            curr->left = new_l_node;
            new_l_node->parent = curr;
            return new_l_node;
        }
        return curr->left;
    }

    TNode* addRight(TNode* curr, int new_k) {
        if (curr->right == nullptr) {
            TNode* new_r_node = new TNode(new_k);
            curr->right = new_r_node;
            new_r_node->parent = curr;
            return new_r_node;
        }
        return curr->right;
    }

    void recursionInOrder(TNode* curr, vector<int>& res) {
        if (curr == nullptr) return;
        recursionInOrder(curr->left, res);
        res.push_back(curr->data);
        recursionInOrder(curr->right, res);
    }

    void recursionPreOrder(TNode* curr, vector<int>& res) {
        if (curr == nullptr) return;
        res.push_back(curr->data);
        recursionPreOrder(curr->left, res);
        recursionPreOrder(curr->right, res);
    }

    void recursionPostOrder(TNode* curr, vector<int>& res) {
        if (curr == nullptr) return;
        recursionPostOrder(curr->left, res);
        recursionPostOrder(curr->right, res);
        res.push_back(curr->data);
    }

    void printInOrder() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }
        vector<int> res;
        recursionInOrder(root, res);
        for (int i : res) {
            cout << i;
        }
        cout << endl;
    }

    void printPreOrder() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }
        vector<int> res;
        recursionPreOrder(root, res);
        for (int i : res) {
            cout << i << " ";
        }
        cout << endl;
    }

    void printPostOrder() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }
        vector<int> res;
        recursionPostOrder(root, res);
        for (int i : res) {
            cout << i << " ";
        }
        cout << endl;
    }

    TNode* get_root() {
        return root;
    }

    TNode* getParent(TNode* node) {
        return node != nullptr ? node->parent : nullptr;
    }
};
