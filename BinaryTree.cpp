#include <iostream>
#include <vector>

using namespace std;

struct TNode {
    int data;
    TNode* left;
    TNode* right;
    TNode* parent;
    TNode(int _data) { data = _data; left = nullptr; right = nullptr; parent = nullptr; }
};

class BinaryThree {

public:
    TNode* root;
    BinaryThree() { root = nullptr; }
    BinaryThree(int k) { root = new TNode(k); }

    void addLeft(TNode* curr, int new_k) {
        if (curr->left == nullptr) {
            TNode* new_l_node = new TNode(new_k);
            curr->left = new_l_node;
            new_l_node->parent = curr;
        }
    }

    void addRight(TNode* curr, int new_k) {
        if (curr->right == nullptr) {
            TNode* new_r_node = new TNode(new_k);
            curr->right = new_r_node;
            new_r_node->parent = curr;
        }
    }

    void recursionInOrder(TNode* curr, vector<int>& res) {
        if (curr != nullptr) {
            recursionInOrder(curr->left, res);
            res.push_back(curr->data);
            recursionInOrder(curr->right, res);
        }
    }

    void recursionPreOrder(TNode* curr, vector<int>& res) {
        if (curr != nullptr) {
            res.push_back(curr->data);
            recursionPreOrder(curr->left, res);
            recursionPreOrder(curr->right, res);
        }
    }

    void recursionPostOrder(TNode* curr, vector<int>& res) {
        if (curr != nullptr) {
            recursionPostOrder(curr->left, res);
            recursionPostOrder(curr->right, res);
            res.push_back(curr->data);
        }
    }

    void printInOrder() {
        vector<int> res;
        recursionInOrder(root, res);
        for (int i : res) {
            cout << i << " ";
        }
        cout << endl;
    }

    void printPreOrder() {
        vector<int> res;
        recursionPreOrder(root, res);
        for (int i : res) {
            cout << i << " ";
        }
        cout << endl;
    }

    void printPostOrder() {
        vector<int> res;
        recursionPostOrder(root, res);
        for (int i : res) {
            cout << i << " ";
        }
        cout << endl;
    }
};

int main() {
/*
    BinaryThree tree(6);
    tree.addLeft(tree.root, 2);
    tree.addRight(tree.root, 7);
    tree.addLeft(tree.root->left, 1);
    tree.addRight(tree.root->left, 4);
    tree.addRight(tree.root->right, 9);
    tree.addLeft(tree.root->left->right, 3);
    tree.addRight(tree.root->left->right, 5);
    tree.addLeft(tree.root->right->right, 8);

    cout << "In-order: "; tree.printInOrder();
    cout << "Pre-order: "; tree.printPreOrder();
    cout << "Post-order: "; tree.printPostOrder();*/

    return 0;
}

