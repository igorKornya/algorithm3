#include "stack.cpp"
#include "BinaryTree.cpp"
#include "AVLTree.cpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>

using namespace std;


vector<int> AVLvec;

int parcer()
{
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
    vector<int> vec;
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
    cout << "\nБинарное дерево: ";
    tree.recursionInOrder(tree.get_root(), vec);
    AVLvec.assign(vec.begin(), vec.end());
    tree.printInOrder();

}

void menu()
{
    cout << "\n1. Считать с файла в бинарное дерево, вывод обходов бинарного дерева" << endl;
    cout << "2. Обход дерева и создание АВЛ-дерева" << endl;
    cout << "3. Вывод всех 4 способов" << endl;
    cout << "4. Выход" << endl;
    cout << "Выберите: " << endl;
}

void AVLtreeFUNC()
{
    AVLTree tree(AVLvec[0]);

    for (int el : AVLvec) {
        tree.root = tree.insert(tree.root, el);
    }
    cout << "AVL-Tree: ";
    tree.printTree();

    vector<int> inOrder, preOrder, postOrder;
    tree.recursionInOrder(tree.root, inOrder);
    tree.recursionPreOrder(tree.root, preOrder);
    tree.recursionPostOrder(tree.root, postOrder);

    cout << "In-order: ";
    for (int val : inOrder) cout << val << " ";
    cout << "\nPre-order: ";
    for (int val : preOrder) cout << val << " ";
    cout << "\nPost-order: ";
    for (int val : postOrder) cout << val << " ";
    cout << "\nBreadth-first traversal: ";
    tree.bft(tree.root);
}

int main() {
    setlocale(LC_ALL, "ru");

    while (true) {
        menu();
        int choice;
        cin >> choice;
        string res;

        switch (choice) {
        case 1:
            parcer();
            break;
        case 2:
            AVLtreeFUNC();
            break;
        case 3:
            cout << "Выход из программы." << endl;
            return 0;
        default:
            cout << "Неверный выбор. Повторите ввод." << endl;
            break;
        }
    }

    return 0;
}

