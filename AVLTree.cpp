#include <iostream>
using namespace std;

struct AVLTNode {
    int data;
    AVLTNode* left;
    AVLTNode* right;
    int height;
    AVLTNode(int _data) { data = _data; left = nullptr; right = nullptr; height = 1; }
};

class AVLTree {
public:
    AVLTNode* root;
    AVLTree() { root = nullptr; }
    AVLTree(int k) { root = new AVLTNode(k); }

    int height(AVLTNode* tree) {
        return tree ? tree->height : 0;
    }

    int balanceF(AVLTNode* tree) {
        return height(tree->right) - height(tree->left);
    }

    void fix(AVLTNode* tree) {
        int hl = height(tree->left);
        int hr = height(tree->right);
        tree->height = (hl > hr ? hl : hr) + 1;
    }

    AVLTNode* leftTurn(AVLTNode* tree) {
        AVLTNode* curr = tree->right;
        tree->right = curr->left;
        curr->left = tree;
        fix(tree);
        fix(curr);
        return curr;
    }

    AVLTNode* rightTurn(AVLTNode* tree) {
        AVLTNode* curr = tree->left;
        tree->left = curr->right;
        curr->right = tree;
        fix(curr);
        fix(tree);
        return curr;
    }

    AVLTNode* balance(AVLTNode* tree) {
        fix(tree);
        if (balanceF(tree) == -2) {
            if (balanceF(tree->left) > 0) {
                tree->left = leftTurn(tree->left);
            }
            return rightTurn(tree);
        }

        if (balanceF(tree) == 2) {
            if (balanceF(tree->right) < 0) {
                tree->right = leftTurn(tree->right);
            }
            return leftTurn(tree);
        }

        return tree;
    }

    AVLTNode* insert(AVLTNode* tree, int _k) {
        if (tree == nullptr) {
            return new AVLTNode(_k);
        }
        if (_k < tree->data) {
            tree->left = insert(tree->left, _k);
        }
        else if (_k > tree->data) {
            tree->right = insert(tree->right, _k);
        }
        else {
            return tree;
        }
        return balance(tree);
    }

    AVLTNode* min(AVLTNode* tree) {
        return tree->left ? min(tree->left) : tree;
    }

    AVLTNode* removeMin(AVLTNode* tree) {
        if (tree->left == nullptr) {
            return tree->right;
        }
        tree->left = removeMin(tree->left);
        return balance(tree);
    }

    AVLTNode* del(AVLTNode* tree, int _k) {
        if (tree == nullptr) {
            return nullptr;
        }
        if (_k < tree->data) {
            tree->left = del(tree->left, _k);
        }
        else if (_k > tree->data) {
            tree->right = del(tree->right, _k);
        }
        else {
            AVLTNode* curr_l = tree->left;
            AVLTNode* curr_r = tree->right;
            delete tree;
            if (curr_r == nullptr) {
                return curr_l;
            }
            AVLTNode* mn = min(curr_r);
            mn->right = removeMin(curr_r);
            mn->left = curr_l;
            return balance(mn);
        }
        return balance(tree);
    }

    void printInOrder(AVLTNode* tree) {
        if (tree != nullptr) {
            printInOrder(tree->left);
            cout << tree->data << " ";
            printInOrder(tree->right);
        }
    }

    void printTree() {
        cout << "In-order traversal of the AVL Tree: ";
        printInOrder(root);
        cout << endl;
    }
};

int main() {
    AVLTree tree;

    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 30);
    tree.printTree();

    tree.root = tree.del(tree.root, 10);
    tree.printTree();

    return 0;
}
