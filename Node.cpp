//
// Created by Tomek on 18.05.2021.
//

#include "Node.h"
#include <iostream>
#include <string>
using namespace std;

Node::Node(int order, bool leaf) {
    this->isLeaf = leaf;
    this->t = order;
    this->keys = new int[2 * this->t - 1];
    this->sons = new Node*[2 * this->t];
}

void Node::split(Node *left, int i) {
    Node * right = new Node(left->t, left->isLeaf);
    right->n = left->t - 1;
    left->n = left->t - 1;
    for (int k = 0; k < left->t - 1; k++) {
        right->keys[k] = left->keys[k+this->t];
    }
    if (!left->isLeaf)
        for (int k = 0; k < this->t; k++)
            right->sons[k] = left->sons[k+this->t];

    for (int k = this->n; k >= i+1; k--) // shift all pointers to the right to create space
        this->sons[k+1] = this->sons[k];
    this->sons[i+1] = right;
    for (int k = this->n - 1; k >= i; k--)
        this->keys[k + 1] = this->keys[k];
    this->keys[i] = left->keys[this->t-1];
    this->n++;
}

void Node::print() {
    int i;
    for (i = 0; i < this->n; i++) {
        if (!this->isLeaf) this->sons[i]->print();
        cout << this->keys[i] << " ";
    }
    if (!this->isLeaf) this->sons[i]->print();
}

void Node::save() {
    int i;
    cout << "( ";
    for (i = 0; i < this->n; i++) {
        if (!this->isLeaf) this->sons[i]->save();
        cout << this->keys[i] << " ";
    }
    //cout << ") ";
    if (!this->isLeaf) this->sons[i]->save();
    cout << ") ";
}

void Node::add_non_full(int val) {
    if (this->isLeaf) {
        int position = 0;
        while (position < this->n && val > this->keys[position]) position++;
        for (int i = this->n-1; i >= position; i--)
            this->keys[i + 1] = this->keys[i];
        this->keys[position] = val;
        this->n++;
    } else {
        int i;
        for (i = this->n-1; i >= 0 && this->keys[i] > val; i--);
        if (this->sons[i+1]->n == 2*this->t-1) {
            this->split(this->sons[i+1], i+1);
            if (this->keys[i+1] < val) i++;
        }
        this->sons[i+1]->add_non_full(val);
    }
}

bool isNumber(string s) {
    return (!s.empty() && s.find_first_not_of("0123456789") == string::npos);
}

void Node::loadNodes() {
    int l = 0;
    string s;
    //cin.ignore();
    while (cin >> s) {
        if (s == "(") {
            this->isLeaf = false;
            this->sons[l] = new Node(this->t, true);
            this->sons[l]->loadNodes();
            l++;
        } else if (s == ")") {
            return;
        } else if (isNumber(s)){
            this->keys[this->n] = stoi(s);
            this->n++;
        }
    }
}

void Node::remove(int val) {
    int index = this->get_index_of_key(val);
    if (index < this->n && this->keys[index] == val) { // when value is in the node
        if (this->isLeaf) this->remove_from_leaf(index);
        else this->remove_from_non_leaf(index);
    } else {
        if (this->isLeaf) return;
        bool last_child = (index == this->n);
        if (this->sons[index]->n < this->t) this->fill(index);
        if (last_child && index > this->n) this->sons[index-1]->remove(val);
        else this->sons[index]->remove(val);
    }
}

int Node::get_index_of_key(int val) {
    int k = 0;
    while (k < this->n && this->keys[k] < val) k++;
    return k;
}

void Node::remove_from_leaf(int index) {
    for (int i = index + 1; i < this->n; i++) this->keys[i - 1] = this->keys[i];
    this->n--;
}

void Node::remove_from_non_leaf(int index) {
    int key = this->keys[index];
    if (this->sons[index]->n >= this->t) {
        int predecessor = get_left(index);
        this->keys[index] = predecessor;
        this->sons[index]->remove(predecessor);
    } else if (this->sons[index+1]->n >= this->t) {
        int successor = get_right(index);
        this->keys[index] = successor;
        this->sons[index+1]->remove(successor);
    } else {
        this->merge(index);
        this->sons[index]->remove(key);
    }
}

int Node::get_left(int index) {
    Node * temp = this->sons[index];
    while (!temp->isLeaf) temp = temp->sons[temp->n];
    int last = temp->n-1;
    return temp->keys[last];
}

int Node::get_right(int index) {
    Node * temp = this->sons[index+1];
    while (!temp->isLeaf) temp = temp->sons[0];
    return temp->keys[0];
}

void Node::merge(int index) {
    Node * son = this->sons[index];
    Node * to_delete = this->sons[index+1];
    son->keys[son->n] = this->keys[index];
    for (int i = 0; i < to_delete->n; i++)
        son->keys[i+son->n+1] = to_delete->keys[i];
    if (!son->isLeaf) {
        for (int i = 0; i <= to_delete->n; i++)
            son->sons[i+this->t] = to_delete->sons[i];
    }
    for (int i = index + 1; i < this->n; i++)
        this->keys[i-1] = this->keys[i];
    for (int i = index+2; i <= this->n; i++)
        this->sons[i-1] = this->sons[i];
    son->n += to_delete->n + 1;
    this->n--;
    delete to_delete;
}

void Node::fill(int index) {
    Node *son = this->sons[index], *neighbour;

    if (index != 0 && this->sons[index - 1]->n >= this->t) {
        neighbour = this->sons[index - 1];
        for (int i = son->n - 1; i >= 0; i--)
            son->keys[i + 1] = son->keys[i];
        if (!son->isLeaf) {
            for (int i = son->n; i >= 0; i--)
                son->sons[i + 1] = son->sons[i];
        }
        son->keys[0] = this->keys[index - 1];
        if (!son->isLeaf)
            son->sons[0] = neighbour->sons[neighbour->n];
        this->keys[index - 1] = neighbour->keys[neighbour->n - 1];
        son->n++;
        neighbour->n--;
    } else if (index != this->n && this->sons[index + 1]->n >= this->t){
        neighbour = this->sons[index + 1];
        son->keys[son->n] = this->keys[index];
        if (!son->isLeaf)
            son->sons[son->n+1] = neighbour->sons[0];
        this->keys[index] = neighbour->keys[0];
        for (int i = 1; i < neighbour->n; i++)
            neighbour->keys[i-1] = neighbour->keys[i];

        if (!neighbour->isLeaf) {
            for (int i = 1; i <= neighbour->n; i++)
                neighbour->sons[i-1] = neighbour->sons[i];
        }
        son->n++;
        neighbour->n--;
    } else {
        if (index != this->n) this->merge(index);
        else this->merge(index - 1);
    }
}
