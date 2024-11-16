#include "stack.cpp"
#include "BinaryTree.cpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    Stack<char> stack;
    string path = "bb.txt";
    ifstream read(path);

    if (!read.is_open()) {
        cout << "Error" << endl;
        return 1;
    }

    string s;
    getline(read, s);
    read.close();

    if (s.empty()) {
        cout << "Error" << endl;
        return 1;
    }

    if (s[0] != '(') {
        cout << "Error" << endl;
        return 1;
    }

    s.erase(0, 1);
    stack.push_front('(');

    int root = 0;
    for (int i = 0; i < s.find('('); ++i) {
        if (!isdigit(s[i])) {
            cout << "Error" << endl;
            return 2;
        }
        root = root * 10 + (s[i] - '0');
    }
    s.erase(0, s.find('('));

    BinaryThree tree(root);
    TNode* curr_parent = tree.get_root();
    int curr_node_val = 0;
    bool right_child_flag = false;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            stack.push_front('(');

            if (i > 0 && s[i - 1] != '(' && s[i - 1] != ')') {
                if (right_child_flag) {
                    curr_parent = tree.addRight(curr_parent, curr_node_val);
                }
                else {
                    curr_parent = tree.addLeft(curr_parent, curr_node_val);
                }
                right_child_flag = false;
                curr_node_val = 0;
            }
            if (i > 0 && s[i - 1] == ')') {
                right_child_flag = true;
            }
        }
        else if (s[i] == ')') {
            if (stack.is_empty() || stack.get_val() != '(') {
                cout << "Error" << endl;
                return 2;
            }
            else {
                if (i > 0 && s[i - 1] != '(' && s[i - 1] != ')') {
                    if (right_child_flag) {
                        curr_parent = tree.addRight(curr_parent, curr_node_val);
                    }
                    else {
                        curr_parent = tree.addLeft(curr_parent, curr_node_val);
                    }
                    right_child_flag = false;
                    curr_node_val = 0;
                }
                stack.pop_front();
                curr_parent = tree.getParent(curr_parent);
            }

        }
        else if (isdigit(s[i])) {
            curr_node_val = curr_node_val * 10 + (s[i] - '0');
        }
        else {
            cout << "Error" << endl;
            return 2;
        }
    }
    vector<int> vec;
    tree.recursionInOrder(tree.get_root(), vec);
    tree.printInOrder();
    tree.recursionPostOrder(tree.get_root(), vec);
    tree.printPostOrder();
    tree.recursionPreOrder(tree.get_root(), vec);
    tree.printPreOrder();

    return 0;
}
