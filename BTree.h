//
// Created by Tomek on 18.05.2021.
//

#ifndef BTREE_WITH_CACHE_ATTEMPT_3_BTREE_H
#define BTREE_WITH_CACHE_ATTEMPT_3_BTREE_H

#include "Node.h"

class BTree {
public:
    // Initializers
    int order = 0;
    Node * root = nullptr;
    BTree();
    BTree(int order);
    // insertion functions
    void insert(int val);
    void print();
};


#endif //BTREE_WITH_CACHE_ATTEMPT_3_BTREE_H
