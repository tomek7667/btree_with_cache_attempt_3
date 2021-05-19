//
// Created by Tomek on 18.05.2021.
//

#include "BTree.h"
#include <iostream>
#include <string>
using namespace std;

BTree::BTree(int order) {
    this->order = order;
}

BTree::BTree() {
    this->order = 0;
}

void BTree::insert(int val) {
    if (this->root == nullptr) {
        this->root = new Node(this->order, true);
        this->root->keys[0] = val;
        this->root->n++;
    } else {
        if (this->root->n == 2*this->order-1) {
            Node * new_node = new Node(this->order, false);
            new_node->sons[0] = this->root;
            new_node->split(this->root, 0);
            if (new_node->keys[0] < val)
                new_node->sons[1]->add_non_full(val);
            else
                new_node->sons[0]->add_non_full(val);
            this->root = new_node;
        } else root->add_non_full(val);
    }
}

void BTree::print() {
    if (this->root != nullptr) this->root->print();
}

bool BTree::search(int val) {
    Node * temp = root;
    while (!temp->isLeaf) {
        int position = 0;
        while (position < temp->n && val > temp->keys[position]) position++;
        if (val == temp->keys[position]) return true;
        temp = temp->sons[position];
    }
    for (int i = 0; i < temp->n; i++)
        if (temp->keys[i] == val) return true;
    return false;
}

void BTree::loadTree() {
    int nodes = 0;
    string input;
    string depths[1024];
    cin.ignore();
    getline(cin, input);
    Node ** nds = new Node*[nodes];
    int deepest = 0, ob = 0, cb = 0;
    for (char c : input) {
        ((ob - cb) > deepest) && (deepest = ob - cb);
        depths[ob-cb] += c;
        (c == '(') && ob++;
        (c == ')') && cb++;
    }
    for (char c : input) (c == '(') && nodes++;
    int i = 0;
    int j = 0;
    while (i < nodes) {
        cout << "node numer:" << i;
        nds[i] = new Node(this->order);
        string num;
        bool found = false;
        while (input[j] != ')' || input[j] != '(') {
            if (input[j] == ' ' || input[j] == '(' || input[j] == ')') {
                found = true;
            } else {
                num += input[j];
                found = false;
            }
            if (found && num.length() > 0) {
                cout <<"CO TY DAJESZ:" << num << endl;
                nds[i]->keys[nds[i]->n] = stoi(num);
                nds[i]->n++;
            }
            if (found) num = "";
            j++;
        }
        cout << "ADSADSADSADS\n";
        j++;
        if (nds[i]->n != 0) {
            nds[i]->print();
            cout << endl;
            i++;
        }
    }
    /*for (int i = 0; i < nodes; i++) {
        for (int s = 0; s < nds[i]->n; s++) {
            cout << nds[i]->keys[s] << " ";
        }
        cout << endl;
    }*/

    /*
    cout << "num of nodes: "<< nodes << std::endl;
    int ob = 0, cb = 0;
    int deepest = 0;
    for (char c : input) {
        ((ob - cb) > deepest) && (deepest = ob - cb);
        depths[ob-cb] += c;
        (c == '(') && ob++;
        (c == ')') && cb++;
    }
    if (deepest == 1) {
        this->root = new Node(this->order, true);
    } else {
        this->root = new Node(this->order, false);
    }
    bool leaf;
    for (int i = 1; i < deepest+1; i++) {
        int test = 0;
        leaf = (deepest == i);
        for (int c = 0; c < depths[i].length(); c++) {
            string num;
            int val;
            if (depths[i][c] == '(' || depths[i][c] == ')') test++;
            while (depths[i][c] != ' ' && depths[i][c] != '(' && depths[i][c] != ')') {
                num += depths[i][c];
                c++;
            }
            if (num.length() > 0) {
                val = stoi(num);
                // val  - one of the keys
                // test - which node is that value
                cout << val << " [" << test << " " << open << " " << close << "] ";
            }
        }
        cout << endl;
    }
    */

    //cout << "deepest: " << deepest << endl;
    cout << "end of load\n\n";
}

void BTree::saveTree() {
    if (this->root != nullptr) this->root->save();
}
