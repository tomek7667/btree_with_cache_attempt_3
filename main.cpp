#include <iostream>
#include "BTree.h"
using namespace std;

int main() {
    char choice;
    int val;
    int order;
    BTree tree;
    while (cin >> choice) {
        if (choice == 'I') {
            cin >> order;
            tree = BTree(order);
        } else if (choice == 'A') {
            cin >> val;
            tree.insert(val);
        } else if (choice == '?') {
            cin >> val;
            cout << val;
            //tree.search(val) ? cout << " +\n" : cout << " -\n";
        } else if (choice == 'P') {
            //tree.traverse();
            cout << endl;
        } else if (choice == 'L') {
            cin >> order;
            tree = BTree(order);
        } else if (choice == 'S') {
            // TODO
        } else if (choice == 'R') {
            cin >> val;
            //tree.remove(val);
        } else if (choice == '#') {
            ;;
        } else if (choice == 'X') {
            //while (tree.root != nullptr) tree.remove(tree.root->keys[tree.root->currentKeys - 1]);
            return 1;
        } else if (choice == 'C') {
            // TODO
        } else {
            cout << "Nie znam komendy : " << choice << endl;
        }
    }
    return 0;
}