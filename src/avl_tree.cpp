#include "avl_tree.hpp"
#include <queue>
#include <iostream>
#include <cmath>
#include <cassert>
using std::queue;
using std::cout;
using std::abs;

// Public Methods

void AVLTree::insert(int key) {
    this->root = insertHelper(this->root, key);
    updateHeight(this->root);
}

int AVLTree::getHeight(AVLNode* node) const {
    if (!node) return 0;
    return node->height;
}

void AVLTree::levelOrder() const {
    if (!this->root) return;

    queue<AVLNode*> q;
    q.push(this->root);
    
    while (!q.empty()) {
        AVLNode* node = q.front();
        q.pop();

        cout << "Key: " << node->key;

        if (q.empty()) cout << '\n';

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

bool AVLTree::isSorted() const {
    return isSortedHelper(this->root);
}

bool AVLTree::isBalanced() const {
    return isBalancedHelper(this->root);
}

// Private Methods

void AVLTree::updateHeight(AVLNode* updateNode) {
    if (!updateNode) return;
    updateNode->height = 1 + std::max(getHeight(updateNode->left), getHeight(updateNode->right));
}

AVLNode* AVLTree::rotateLeft(AVLNode* node) {
    if (!node || !node->right) return nullptr;
    AVLNode* z = node;
    AVLNode* y = node->right;
    z->right = y->left; // z takes over y's left child
    y->left = z; // y becomes the new root
    updateHeight(z);
    updateHeight(y);
    return y;
}

AVLNode* AVLTree::rotateRight(AVLNode* node) {
    if (!node || !node->left) return nullptr;
    AVLNode* z = node;
    AVLNode* y = node->left;
    z->left = y->right; // z takes over y's right child
    y->right = z; // y becomes the new root
    updateHeight(z);
    updateHeight(y);
    return y;
}

bool AVLTree::isBalancedFactored(AVLNode* node) const {
    return std::abs(getHeight(node->left) - getHeight(node->right)) <= 1;
}

AVLNode* AVLTree::insertHelper(AVLNode* insertAtNode, int key) {
    // Base case
    if (!insertAtNode) {
        return new AVLNode(key);
    }

    // Recursively inserting based on the BST's sorted property
    if (insertAtNode->key > key) insertAtNode->left = insertHelper(insertAtNode->left, key);
    else if (insertAtNode->key < key) insertAtNode->right = insertHelper(insertAtNode->right, key);
    else return insertAtNode; // Duplicate key case

    updateHeight(insertAtNode);

    // Ensuring balance factor is kept
    if (!isBalancedFactored(insertAtNode)) {
        insertAtNode = restructure(insertAtNode);
    }

    return insertAtNode;
}

AVLNode* AVLTree::restructure(AVLNode* restructureAtNode) {
    // An unbalanced node must have at least a child of relative height 2
    
    assert(restructureAtNode && "Unbalanced node must have at least a child of relative height 2");

    AVLNode* z = restructureAtNode; // First unbalanced ancestor
    AVLNode* y; // Heightest child of z
    AVLNode* x; // Heightest child of y

    // Getting y and z
    if (getHeight(z->left) > getHeight(z->right)) y = z->left;
    else y = z->right;

    assert(y && "Unbalanced node must have at least a child of relative height 2");

    if (getHeight(y->left) > getHeight(y->right)) x = y->left;
    else x = y->right;

    assert(x && "Unbalanced node must have at least a child of relative height 2");

    if (z->right == y && y->right == x) return rotateLeft(z); // RR, so rotate left
    else if (z->left == y && y->left == x) return rotateRight(z); // LL, so rotate right
    else if (z->right == y && y->left == x) { // RL
        z->right = rotateRight(y); // first make it into a rightward chain
        return rotateLeft(z); // now it's RR, so rotate left
    }
    else if (z->left == y && y->right == x) { // LR
        z->left = rotateLeft(y); // first make it into a leftward chain
        return rotateRight(z); // then it's LL, so rotate right
    }

    return z;
}

bool AVLTree::isSortedHelper(AVLNode* node) const {
    if (!node) return true;

    if (node->left && node->left->key >= node->key) return false;
    if (node->right && node->right->key <= node->key) return false;

    bool leftCheck = isSortedHelper(node->left);
    bool rightCheck = isSortedHelper(node->right);

    return leftCheck && rightCheck;
}

bool AVLTree::isBalancedHelper(AVLNode* node) const {
    if (!node) return true;

    if (!isBalancedFactored(node)) return false;

    bool leftCheck = isBalancedHelper(node->left);
    bool rightCheck = isBalancedHelper(node->right);

    return leftCheck && rightCheck;
}
