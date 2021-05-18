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
    BTree();
    BTree(int order);
    // constants
    int maximumSize() const;
    int minimumSize() const;
    // insertion functions
};


#endif //BTREE_WITH_CACHE_ATTEMPT_3_BTREE_H
