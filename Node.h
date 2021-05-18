//
// Created by Tomek on 18.05.2021.
//

#ifndef BTREE_WITH_CACHE_ATTEMPT_3_NODE_H
#define BTREE_WITH_CACHE_ATTEMPT_3_NODE_H


class Node {
public:
    Node ** sons;
    int * keys;
    int n = 0, t = 0;
    bool isLeaf = true;
    Node(int order);
    // constants
};


#endif //BTREE_WITH_CACHE_ATTEMPT_3_NODE_H
