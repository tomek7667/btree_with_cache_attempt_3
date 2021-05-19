//
// Created by Tomek on 18.05.2021.
//

#include "Node.h"
#include <iostream>
#include <string>
using namespace std;

Node::Node(int order, bool leaf) {
    this->isLeaf = leaf;
    this->t = order;
    this->keys = new int[2 * this->t - 1];
    this->sons = new Node*[2 * this->t];
}

void Node::split(Node *left, int i) {
    Node * right = new Node(left->t, left->isLeaf);
    right->n = left->t - 1;
    left->n = left->t - 1;
    for (int k = 0; k < left->t - 1; k++) {
        right->keys[k] = left->keys[k+this->t];
    }
    if (!left->isLeaf)
        for (int k = 0; k < this->t; k++)
            right->sons[k] = left->sons[k+this->t];

    for (int k = this->n; k >= i+1; k--) // shift all pointers to the right to create space
        this->sons[k+1] = this->sons[k];
    this->sons[i+1] = right;
    for (int k = this->n - 1; k >= i; k--)
        this->keys[k + 1] = this->keys[k];
    this->keys[i] = left->keys[this->t-1];
    this->n++;
}

void Node::print() {
    int i;
    for (i = 0; i < this->n; i++) {
        if (!this->isLeaf) this->sons[i]->print();
        cout << this->keys[i] << " ";
    }
    if (!this->isLeaf) this->sons[i]->print();
}

void Node::save() {
    int i;
    cout << "( ";
    for (i = 0; i < this->n; i++) {
        if (!this->isLeaf) this->sons[i]->save();
        cout << this->keys[i] << " ";
    }
    cout << ") ";
    if (!this->isLeaf) this->sons[i]->save();
}

void Node::add_non_full(int val) {
    if (this->isLeaf) {
        int position = 0;
        while (position < this->n && val > this->keys[position]) position++;
        for (int i = this->n-1; i >= position; i--)
            this->keys[i + 1] = this->keys[i];
        this->keys[position] = val;
        this->n++;
    } else {
        int i;
        for (i = this->n-1; i >= 0 && this->keys[i] > val; i--);
        if (this->sons[i+1]->n == 2*this->t-1) {
            this->split(this->sons[i+1], i+1);
            if (this->keys[i+1] < val) i++;
        }
        this->sons[i+1]->add_non_full(val);
    }
}

bool isNumber(const string& str)
{
    for (char const &c : str) if (std::isdigit(c) == 0) return false;
    return true;
}

void Node::loadNodes() {
    int l = 0;
    string s;
    while (cin >> s && (s == "(" || s == ")" || isNumber(s))) {
        if (s == "(") {
            //cout << this->n << "\n";
            this->n++;
            this->sons[this->n-1] = new Node(this->t, false);
            this->sons[this->n-1]->loadNodes();
            //cout << endl;
        } else if (s == ")") {
            return;
        } else if (isNumber(s)){
            //cout << s << " ";
            this->keys[l] = stoi(s);
            l++;
        }
    }
}

void Node::fix_itself() {
    if (!this->sons[0]) {
        this->sons[0]->fix_itself();
    } else {
        this->isLeaf = true;
    }
}



