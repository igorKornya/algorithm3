#include <iostream>
#include <queue>
#include <vector>
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

    AVLTNode* f_min(AVLTNode* tree) {
        if (tree->left == nullptr)
        {
            return tree;
        }
        return f_min(tree->left);
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
            AVLTNode* mn = f_min(curr_r);
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

    void recursionInOrder(AVLTNode* curr, vector<int>& res) {
        if (curr != nullptr) {
            recursionInOrder(curr->left, res);
            res.push_back(curr->data);
            recursionInOrder(curr->right, res);
        }
    }

    void recursionPreOrder(AVLTNode* curr, vector<int>& res) {
        if (curr != nullptr) {
            res.push_back(curr->data);
            recursionPreOrder(curr->left, res);
            recursionPreOrder(curr->right, res);
        }
    }

    void recursionPostOrder(AVLTNode* curr, vector<int>& res) {
        if (curr != nullptr) {
            recursionPostOrder(curr->left, res);
            recursionPostOrder(curr->right, res);
            res.push_back(curr->data);
        }
    }

    void printTree() {
        printInOrder(root);
        cout << endl;
    }

    AVLTNode* search(AVLTNode* tree, int _k)
    {
        if (tree == nullptr || tree->data == _k)
        {
            return tree;
        }
        if (_k < tree->data)
        {
            return search(tree->left, _k);
        }
        else { return search(tree->right, _k); }
    }

    void bft(AVLTNode* tree)
    {
        if (tree == nullptr)
        {
            return;
        }
        queue<AVLTNode*> qu;
        qu.push(tree);
        while (!qu.empty())
        {
            AVLTNode* temp = qu.front();
            qu.pop();
            cout << temp->data << " ";

            if (temp->left != nullptr)
            {
                qu.push(temp->left);
            }
            if (temp->right != nullptr)
            {
                qu.push(temp->right);
            }
        }
        cout << endl;
    }
};

int main() {
        //AVLTree tree;

    //vector<int> elements = { 20, 10, 30, 5, 15, 25, 35 };
    //for (int el : elements) {
    //    tree.root = tree.insert(tree.root, el);
    //}
    //cout << "AVL-Tree: ";
    //tree.printTree();

    //tree.root = tree.del(tree.root, 10);
    //cout << "after deleting: ";
    //tree.printTree();

    //vector<int> inOrder, preOrder, postOrder;
    //tree.recursionInOrder(tree.root, inOrder);
    //tree.recursionPreOrder(tree.root, preOrder);
    //tree.recursionPostOrder(tree.root, postOrder);

    //cout << "In-order: ";
    //for (int val : inOrder) cout << val << " ";
    //cout << "\nPre-order: ";
    //for (int val : preOrder) cout << val << " ";
    //cout << "\nPost-order: ";
    //for (int val : postOrder) cout << val << " ";
    //cout << "\nBreadth-first traversal: ";
    //tree.bft(tree.root);

    //return 0;
}
