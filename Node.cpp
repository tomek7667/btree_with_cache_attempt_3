//
// Created by Tomek on 18.05.2021.
//

#include "Node.h"

Node::Node(int order) {
    this->t = order;
    this->keys = new int[2 * this->t];
    this->sons = new Node*[2 * this->t - 1];
}

