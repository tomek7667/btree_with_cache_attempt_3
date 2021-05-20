#include <iostream>
#include "BTree.h"
#include <string>
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
            tree.search(val) ? cout << " +\n" : cout << " -\n";
        } else if (choice == 'P') {
            tree.print();
            cout << endl;
        } else if (choice == 'L') {
            cin >> order;
            tree = BTree(order);
            tree.loadTree();
        } else if (choice == 'S') {
            cout << tree.order << endl;
            tree.saveTree();
        } else if (choice == 'R') {
            cin >> val;
            tree.remove(val);
        } else if (choice == '#') {
            string temp;
            cin.ignore();
            cin >> temp;
        } else if (choice == 'X') {
            while (tree.root != nullptr) tree.remove(tree.root->keys[tree.root->n-1]);
            //tree.remove(tree.root->keys[tree.root->n-1]);
            return 1;
        } else if (choice == 'C') {
            cin >> val;
            tree.fifo_cache(val);
        } else if (choice == 'K') { // my implementation of cache TLUO - The Least Used Out
            cin >> val;
            tree.tluo_cache(val);
        } else {
            cout << "Nie znam komendy : " << choice << endl;
        }
    }
    return 0;
}
