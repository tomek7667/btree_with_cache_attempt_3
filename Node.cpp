//
// Created by Tomek on 18.05.2021.
//

#include "Node.h"
#include <iostream>

Node::Node(int order, bool leaf) {
    this->isLeaf = leaf;
    this->t = order;
    this->keys = new int[2 * this->t - 1];
    this->sons = new Node*[2 * this->t];
}

int Node::position_of_key(int val) const {
    for (int i = 0; i < this->n; i++) {
        if (this->keys[i] == val) return i;
    }
    return -1;
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
    this->keys[i] = left->keys[this->t-1];
    this->n++;
}

void Node::print() {
    int i;
    for (i = 0; i < this->n; i++) {
        if (!this->isLeaf) this->sons[i]->print();
        std::cout << this->keys[i] << " ";
    }
    if (!this->isLeaf) this->sons[i]->print();
}

void Node::save() {
    int i;
    std::cout << "( ";
    for (i = 0; i < this->n; i++) {
        if (!this->isLeaf) this->sons[i]->save();
        std::cout << this->keys[i] << " ";
    }
    std::cout << ") ";
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



