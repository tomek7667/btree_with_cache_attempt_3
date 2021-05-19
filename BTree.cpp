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

void BTree::loadTree() {
    int ob = 0, cb = 0;
    char input[1024][1024]; // depth - position
    char loader = getchar();
    int maximumDepth = 0;
    int iterators[2048] = {};
    do {
        loader = getchar();
        iterators[ob-cb]++;
        if (ob-cb > maximumDepth) maximumDepth = ob-cb;
        int i = iterators[ob-cb];
        input[ob-cb][i] = loader;
        switch (loader) {
            case '(':
                ob++;
                break;
            case ')':
                cb++;
                break;
        }
    } while (loader != '\n' && loader != '\000' && loader != -1);
    //std::cout << "max depth: " << maximumDepth << std::endl;
    for (int i = 1; i < maximumDepth+1; i++) {
        int m = iterators[i];
        for (int j = 1; j < m; j++) {
            char number[128];
            int l = 0;
            while (input[i][j] != ' ' && input[i][j] != '(' && input[i][j] != ')') {
                number[l] = input[i][j];
                l++;
                j++;
            }
            if (l > 0) this->insert(atoi(number));
        }
    }
    /*if (maximumDepth == 1) {
        this->root = new Node(this->order, true);
    } else {
        this->root = new Node(this->order, false);
    }
    for (int i = 1; i < maximumDepth+1; i++) {
        bool leaf = (maximumDepth==i);
        int m = iterators[i];
        if (i == 1) {
            for (int j = 1; j < m; j++) {
                char number[128];
                int l = 0;
                while (input[i][j] != ' ' && input[i][j] != '(' && input[i][j] != ')') {
                    number[l] = input[i][j];
                    l++;
                    j++;
                }
                if (l > 0) {
                    this->root->keys[this->root->n] = atoi(number);
                    this->root->n++;
                }
            }
        } else {
            std::cout << "layer nr" << i << "\n";
            Node * temp = this->root;
            for (int k = 0; k < 2*this->order; k++) { // W ZALEZNOSCI OD TEGO CO OBARA NAPISZE 2*t-1 lub 2*t
                //temp = temp->sons[k];
                temp->sons[k] = new Node(this->order, leaf);
                temp = temp->sons[k];
                for (int j = 1; j < m; j++) {

                }
            }
            for (int j = 1; j < m; j++) {
                std::cout << input[i][j];
            }
            std::cout << std::endl;
        }

    }
    */
}

void BTree::saveTree() {
    if (this->root != nullptr) this->root->save();
}
