#include <bits/stdc++.h>

class Node{
public:
    int key;
    Node* leftChild;
    Node* rightChild;

    Node() {}
    Node(int key) {
        this->key = key;
        leftChild = nullptr;
        rightChild = nullptr;
    }
};

/*
        1
       / \
      4   3
         /
        2
*/

class BinaryTree{
public:
    Node* root;

    BinaryTree() {
        root = new Node(1);
        root->leftChild = new Node(4);
        root->rightChild = new Node(3);
        root->rightChild->leftChild = new Node(2);
    }

    void traverse(Node* cur, bool clear = false) {
        if (cur == NULL) return;
        if (!clear) std::cout << cur->key << std::endl;
        traverse(cur->leftChild, clear);
        traverse(cur->rightChild, clear);
        if (clear) free(cur);
    }

    ~BinaryTree() {
        traverse(this->root, true);
    }
};

int main() {
    BinaryTree t;
    t.traverse(t.root);
    return 0;
}
