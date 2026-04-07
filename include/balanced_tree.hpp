#pragma once
#include <cmath>
#include <iostream>
#include <queue>

using std::cout;
using std::queue;

template <typename T>
struct AVLNode {
    AVLNode<T>* left;
    AVLNode<T>* right;
    int key;
    T data;
    int height;

    AVLNode(int key, const T& data)
        : key(key),
          data(data),
          left(nullptr),
          right(nullptr),
          height(0)
    {}
};

template <typename T>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    // Inserts a node to the tree (does not insert if the key is a duplicate)
    void insert(int key, const T& data) {
        this->root = insertHelper(this->root, key, data);
        updateHeight(this->root);
        return;
    }

    // Returns the height of the node (0 if node is null)
    int getHeight(AVLNode<T>* node) const {
        if (!node) return 0;
        return node->height;
    }

    // Prints the level order traversal of the tree
    void levelOrder() {
        if (!this->root) return;

        queue<AVLNode<T>*> q;
        q.push(this->root);
        
        while (!q.empty()) {
            AVLNode<T>* node = q.front();
            q.pop();

            cout << "Key: " << node->key << "Data: " << node->data << " ";

            if (q.empty()) cout << '\n';

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }

    // Testing function to ensure the tree has the BST sorted property
    bool isSorted() {
        isSortedHelper(this->root);
    }

    // Testing function to ensure the tree has the AVL balanced property
    bool isBalanced() {
        isBalancedHelper(this->root);
    }

private:
    AVLNode<T>* root = nullptr;

    // Updates height of the given node
    void updateHeight(AVLNode<T>* updateNode) {
        if (!updateNode) return;
        updateNode->height = 1 + std::max(getHeight(updateNode->left), getHeight(updateNode->right));
    }

    // Rotates a rightward chain, to the left and returns the new root (null if node or node->right are null)
    AVLNode<T>* rotateLeft(AVLNode<T>* node) {
        if (!node || !node->right) return nullptr;
        AVLNode<T>* z = node;
        AVLNode<T>* y = node->right;
        z->right = y->left; // z takes over y's left child
        y->left = z; // y becomes the new root
        updateHeight(z);
        updateHeight(y);
        return y;
    }

    // Rotates a leftward chain, to the right and returns the new root (null if node or node->left are null)
    AVLNode<T>* rotateRight(AVLNode<T>* node) {
        if (!node || !node->left) return nullptr;
        AVLNode<T>* z = node;
        AVLNode<T>* y = node->left;
        z->left = y->right; // z takes over y's right child
        y->right = z; // y becomes the new root
        updateHeight(z);
        updateHeight(y);
        return y;
    }

    // Returns true if the node satisfies the balance factor: |h(left) - h(right)| <= 1
    bool isBalancedFactored(AVLNode<T>* node) {
        return std::abs(getHeight(node->left) - getHeight(node->right)) <= 1;
    }

    AVLNode<T>* insertHelper(AVLNode<T>* insertAtNode, int key, const T& data) {
        // Base case
        if (!insertAtNode) {
            return new AVLNode<T>(key, data);
        }

        // Recursively inserting based on the BST's sorted property
        if (insertAtNode->key > key) insertAtNode->left = insertHelper(insertAtNode->left, key, data);
        else if (insertAtNode->key < key) insertAtNode->right = insertHelper(insertAtNode->right, key, data);
        else return insertAtNode; // Duplicate key case

        updateHeight(insertAtNode);

        // Ensuring balance factor is kept
        if (!isBalancedFactored(insertAtNode)) {
            insertAtNode = restructure(insertAtNode);
        }

        return insertAtNode;
    }

    // Rotates the tree where given a node with an unblanced factor
    AVLNode<T>* restructure(AVLNode<T>* restructureAtNode) {
        // An unbalanced node must have at least a child of relative height 2
        
        static_assert(restructureAtNode, "Unbalanced node must have at least a child of relative height 2");

        AVLNode<T>* z = restructureAtNode; // First unbalanced ancestor
        AVLNode<T>* y; // Heightest child of z
        AVLNode<T>* x; // Heightest child of y

        // Getting y and z
        if (getHeight(z->left) > getHeight(z->right)) y = z->left;
        else y = z->right;

        static_assert(y, "Unbalanced node must have at least a child of relative height 2");

        if (getHeight(y->left) > getHeight(y->right)) x = y->left;
        else x = y->right;

        static_assert(x, "Unbalanced node must have at least a child of relative height 2");

        if (z->right == y && y->right == x) return rotateLeft(z); // RR
        else if (z->left == y && y->left == x) return rotateRight(z); // LL
        else if (z->right == y && y->left == x) { // RL
            z->right = rotateRight(y); // first make it into a rightward chain
            return rotateLeft(z);
        }
        else if (z->left == y && y->right == x) { // LR
            z->left = rotateLeft(y); // first make it into a leftward chain
            return rotateRight(z);
        }

        return z;
    }

    bool isSortedHelper(AVLNode<T>* node) {
        if (!node) return true;

        if (node->left && node->left->key >= node->key) return false;
        if (node->right && node->right->key <= node->key) return false;

        bool leftCheck = isSortedHelper(node->left);
        bool rightCheck = isSortedHelper(node->right);

        return leftCheck && rightCheck;
    }

    bool isBalancedHelper(AVLNode<T>* node) {
        if (!node) return true;

        if (!isBalancedFactored(node)) return false;

        bool leftCheck = isBalancedHelper(node->left);
        bool rightCheck = isBalancedHelper(node->right);

        return leftCheck && rightCheck;
    }
};
