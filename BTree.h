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
    explicit BTree(int order);
    // insertion functions
    void insert(int val);
    void print() const;
    bool search(int val) const;

    void loadTree();
    void saveTree() const;

    void fifo_cache(int c_size) const;
    void tluo_cache(int c_size) const;
    bool measure_cache(int val, int *gos) const;

    void remove(int val);
};


#endif //BTREE_WITH_CACHE_ATTEMPT_3_BTREE_H
