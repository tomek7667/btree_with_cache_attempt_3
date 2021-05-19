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
    bool isLeaf;
    Node(int order, bool leaf=true);
    int position_of_key(int val) const;
    void print();
    void save();
    void split(Node * left, int i);
    void add_non_full(int val);
};


#endif //BTREE_WITH_CACHE_ATTEMPT_3_NODE_H
