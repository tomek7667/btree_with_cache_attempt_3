//
// Created by Tomek on 18.05.2021.
//

#include "BTree.h"

BTree::BTree(int order) {
    this->order = order;
}

BTree::BTree() {
    this->order = 0;
}

int BTree::maximumSize() const {
    return 2 * this->order - 1;
}

int BTree::minimumSize() const {
    return this->order - 1;
}
