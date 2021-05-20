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
    void print();
    void save();
    void split(Node * left, int i);
    void add_non_full(int val);
    void loadNodes();

    void remove(int val);
    int get_index_of_key(int val);

    void remove_from_leaf(int index);

    void remove_from_non_leaf(int index);

    int get_left(int index);

    int get_right(int index);

    void merge(int index);

    void fill(int index);
};


#endif //BTREE_WITH_CACHE_ATTEMPT_3_NODE_H
