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
            //tree.insert(val); TODO:
        } else if (choice == '?') {
            cin >> val;
            cout << val;
            //tree.search(val) ? cout << " +\n" : cout << " -\n"; TODO:
        } else if (choice == 'P') {
            //tree.traverse(); TODO:
            cout << endl;
        } else if (choice == 'L') {
            cin >> order;
            tree = BTree(order);
        } else if (choice == 'S') {
            // TODO:
        } else if (choice == 'R') {
            cin >> val;
            //tree.remove(val);TODO:
        } else if (choice == '#') {
            ;;
        } else if (choice == 'X') {
            //while (tree.root != nullptr) tree.remove(tree.root->keys[tree.root->currentKeys - 1]);
            // TODO:
            return 1;
        } else if (choice == 'C') {
            // TODO:
        } else {
            cout << "Nie znam komendy : " << choice << endl;
        }
    }
    return 0;
}
