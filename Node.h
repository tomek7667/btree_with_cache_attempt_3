//
// Created by Tomek on 18.05.2021.
//

#ifndef BTREE_WITH_CACHE_ATTEMPT_3_NODE_H
#define BTREE_WITH_CACHE_ATTEMPT_3_NODE_H


class Node {
public:
    Node ** p_to_children;
    int * keys;
    int n = 0;
    bool isLeaf = true;
    Node(int order);
};


#endif //BTREE_WITH_CACHE_ATTEMPT_3_NODE_H
