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
        if (this->root->n == 2*this->order-1) {
            Node * new_node = new Node(this->order, false);
            new_node->sons[0] = this->root;
            new_node->split(this->root, 0);
            int i = 0;
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

