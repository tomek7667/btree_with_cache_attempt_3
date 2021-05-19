//
// Created by Tomek on 18.05.2021.
//

#include "BTree.h"
#include <iostream>
#include <string>
using namespace std;

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
    Node * temp = this->root;
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
    int nodes = 0;
    string input;
    string depths[1024];
    cin.ignore();
    getline(cin, input);
    Node ** nds = new Node*[nodes];
    int deepest = 0, ob = 0, cb = 0;
    for (char c : input) {
        ((ob - cb) > deepest) && (deepest = ob - cb);
        depths[ob-cb] += c;
        (c == '(') && ob++;
        (c == ')') && cb++;
    }
    for (char c : input) (c == '(') && nodes++;
    int i = 0;
    int j = 0;
    while (i < nodes) {
        cout << "node numer:" << i;
        nds[i] = new Node(this->order);
        string num;
        bool found = false;
        while (input[j] != ')' || input[j] != '(') {
            if (input[j] == ' ' || input[j] == '(' || input[j] == ')') {
                found = true;
            } else {
                num += input[j];
                found = false;
            }
            if (found && num.length() > 0) {
                cout <<"CO TY DAJESZ:" << num << endl;
                nds[i]->keys[nds[i]->n] = stoi(num);
                nds[i]->n++;
            }
            if (found) num = "";
            j++;
        }
        cout << "ADSADSADSADS\n";
        j++;
        if (nds[i]->n != 0) {
            nds[i]->print();
            cout << endl;
            i++;
        }
    }
    /*for (int i = 0; i < nodes; i++) {
        for (int s = 0; s < nds[i]->n; s++) {
            cout << nds[i]->keys[s] << " ";
        }
        cout << endl;
    }*/

    /*
    cout << "num of nodes: "<< nodes << std::endl;
    int ob = 0, cb = 0;
    int deepest = 0;
    for (char c : input) {
        ((ob - cb) > deepest) && (deepest = ob - cb);
        depths[ob-cb] += c;
        (c == '(') && ob++;
        (c == ')') && cb++;
    }
    if (deepest == 1) {
        this->root = new Node(this->order, true);
    } else {
        this->root = new Node(this->order, false);
    }
    bool leaf;
    for (int i = 1; i < deepest+1; i++) {
        int test = 0;
        leaf = (deepest == i);
        for (int c = 0; c < depths[i].length(); c++) {
            string num;
            int val;
            if (depths[i][c] == '(' || depths[i][c] == ')') test++;
            while (depths[i][c] != ' ' && depths[i][c] != '(' && depths[i][c] != ')') {
                num += depths[i][c];
                c++;
            }
            if (num.length() > 0) {
                val = stoi(num);
                // val  - one of the keys
                // test - which node is that value
                cout << val << " [" << test << " " << open << " " << close << "] ";
            }
        }
        cout << endl;
    }
    */

    //cout << "deepest: " << deepest << endl;
    cout << "end of load\n\n";
}

void BTree::saveTree() const {
    if (this->root != nullptr) this->root->save();
}

bool isInArray(const int * array, int val, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == val) return true;
    }
    return false;
}

void appendFIFO(int * array, int val, int * size, int max_size) {
    if ((*size) != max_size) {
        array[(*size)] = val;
        (*size)++;
    } else {
        for (int i = 0; i < *size; i++) array[i] = array[i+1];
        array[(*size)-1] = val;
    }
}

void printFIFO(int * array, int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

bool BTree::measure_cache(int val, int * gos) {
    Node * temp = root;
    (*gos)++;
    while (!temp->isLeaf) {
        int position = 0;
        while (position < temp->n && val > temp->keys[position]) position++;
        if (val == temp->keys[position]) return true;
        (*gos)++;
        temp = temp->sons[position];
    }
    for (int i = 0; i < temp->n; i++)
        if (temp->keys[i] == val) return true;
    return false;
}

void BTree::fifo_cache(int c_size) {
    string input;
    cin.ignore();
    getline(cin, input);
    int * cache = new int[c_size];
    int nm = 0;
    int no_cache_operations = 0;
    int cache_operations = 0;
    for (int i = 0; i < input.length(); i++) {
        string num;
        int val;
        while (input[i] != ' ' && i < input.length()) {
            num += input[i];
            i++;
        }
        if (num.length() > 0) {
            val = stoi(num);
            if (!isInArray(cache, val, nm)) {
                appendFIFO(cache, val, &nm, c_size);
                measure_cache(val, &cache_operations);
                measure_cache(val, &no_cache_operations);
            } else {
                measure_cache(val, &no_cache_operations);
            }
        }
    }
    cout << "NO CACHE: " << no_cache_operations << " CACHE: " << cache_operations << endl;
}

int positionOfVal(int ** array, int size, int val) {
    for (int i = 0; i < size; i++) {
        if (array[i][0] == val) return i;
    }
}

int positionOfLeastUsed(int ** array, int size) {
    int smallest = array[0][1];
    int position = 0;
    for (int i = 0; i < size; i++) {
        if (smallest > array[i][1]) {
            position = i;
            smallest = array[i][1];
        }
    }
    return position;
}

void appendTLUO(int ** array, int val, int * size, int max_size) {
    if ((*size) != max_size) {
        array[(*size)][0] = val;
        array[(*size)][1] = 1;
        (*size)++;
    } else {
        int leastUsed = positionOfLeastUsed(array, (*size));
        array[leastUsed][1] = 1;
        array[leastUsed][0] = val;
    }
}

bool isInArrayTLUO(int ** array, int val, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i][0] == val) return true;
    }
    return false;
}

void BTree::tluo_cache(int c_size) {
    string input;
    cin.ignore();
    getline(cin, input);
    int ** cache = new int*[c_size];
    for (int i = 0; i < c_size; i++) cache[i] = new int[2]{};
    int nm = 0;
    int no_cache_operations = 0;
    int cache_operations = 0;
    for (int i = 0; i < input.length(); i++) {
        string num;
        int val;
        while (input[i] != ' ' && i < input.length()) {
            num += input[i];
            i++;
        }
        if (num.length() > 0) {
            val = stoi(num);
            if (!isInArrayTLUO(cache, val, nm)) {
                appendTLUO(cache, val, &nm, c_size);
                measure_cache(val, &cache_operations);
                measure_cache(val, &no_cache_operations);
            } else {
                int pos = positionOfVal(cache, nm, val);
                cache[pos][1]++;
                measure_cache(val, &no_cache_operations);
            }
        }
    }
    cout << "NO CACHE: " << no_cache_operations << " CACHE: " << cache_operations << endl;
}
