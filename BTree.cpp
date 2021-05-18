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

