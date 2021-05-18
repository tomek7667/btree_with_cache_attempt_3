//
// Created by Tomek on 18.05.2021.
//

#include "BTree.h"
#include <iostream>

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
        if (this->root->n < (2*this->order-1)) {
            if (this->root->isLeaf) {
                int position = 0;
                while (position < this->root->n && val > this->root->keys[position]) position++;
                for (int i = this->root->n-1; i >= position; i--)
                    this->root->keys[i + 1] = this->root->keys[i];
                this->root->keys[position] = val;
                this->root->n++;
            }
        }
    }
}

void BTree::print() {
    if (this->root != nullptr) this->root->print();
}

