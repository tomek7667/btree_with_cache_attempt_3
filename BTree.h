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
    bool search(int val);

    void loadTree();
    void saveTree() const;

    void fifo_cache(int c_size);
    bool measure_fifo_cache(int val, int *gos);
};


#endif //BTREE_WITH_CACHE_ATTEMPT_3_BTREE_H
