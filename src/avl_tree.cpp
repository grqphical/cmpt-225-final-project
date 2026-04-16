#include "avl_tree.hpp"
#include <queue>
#include <iostream>
#include <cmath>
#include <cassert>
using std::queue;
using std::cout;
using std::abs;

// Public Methods

AVLTree::~AVLTree() {
    freeHelper(this->root);
}

void AVLTree::Insert(int key) {
    this->root = insertHelper(this->root, key);
    updateHeight(this->root);
}

bool AVLTree::Search(int key) const {
    return searchHelper(this->root, key);
}

void AVLTree::Delete(int key) {
    this->root = deleteHelper(this->root, key);
    updateHeight(this->root);
}

void AVLTree::Print() const {
    if (!this->root) return;

    queue<AVLNode*> q;
    q.push(this->root);
    
    int levelSize = 0;
    cout << '\n';
    while (!q.empty()) {
        if (levelSize == 0) levelSize = q.size();
        AVLNode* node = q.front();
        q.pop();
        levelSize--;

        cout << "K-" << node->key << " ";

        if (levelSize == 0) cout << '\n';

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    cout << '\n';
}

AVLNode* AVLTree::searchNode(int key) const {
    return searchHelper(this->root, key);
}

int AVLTree::getHeight(AVLNode* node) const {
    if (!node) return 0;
    return node->height;
}

int AVLTree::getSize() const {
    return getSizeHelper(this->root);
}

bool AVLTree::isSorted() const {
    return isSortedHelper(this->root);
}

bool AVLTree::isBalanced() const {
    return isBalancedHelper(this->root);
}

// Private Methods

void AVLTree::freeHelper(AVLNode* node) {
    if (!node) return;
    freeHelper(node->left);
    freeHelper(node->right);
    delete node;
}

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

AVLNode* AVLTree::deleteHelper(AVLNode* deleteAtNode, int key) {
    // Base case
    if (!deleteAtNode) return nullptr;

    // Deletion
    if (deleteAtNode->key == key) {
        AVLNode* toReturn = nullptr;

        if (deleteAtNode->left && deleteAtNode->right) { // two children case
            // We swap the key so now current node is successor and the other node is deleted

            // Successor is smallest of right subtree
            AVLNode* successor = deleteAtNode->right;
            while (successor->left) successor = successor->left;

            // Swapping and then deleting successor
            deleteAtNode->key = successor->key;
            successor->key = key;
            deleteAtNode->right = deleteHelper(deleteAtNode->right, key);
            
            // Maintain tree properties
            updateHeight(deleteAtNode);
            if (!isBalancedFactored(deleteAtNode)) {
                deleteAtNode = restructure(deleteAtNode);
            }

            // Return current node as we are done
            return deleteAtNode;
        } else if (deleteAtNode->left) {
            toReturn = deleteAtNode->left;
        } else if (deleteAtNode->right) {
            toReturn = deleteAtNode->right;
        }

        // Single child case we just remove current node and return the child
        delete deleteAtNode;
        return toReturn;
    }

    // Recursively deleting based on the BST's sorted property
    if (deleteAtNode->key > key) deleteAtNode->left = deleteHelper(deleteAtNode->left, key);
    else deleteAtNode->right = deleteHelper(deleteAtNode->right, key);

    updateHeight(deleteAtNode);

    // Ensuring balance factor is kept
    if (!isBalancedFactored(deleteAtNode)) {
        deleteAtNode = restructure(deleteAtNode);
    }

    return deleteAtNode;
}

int AVLTree::getSizeHelper(AVLNode* node) const {
    if (!node) return 0;
    
    return 1 + getSizeHelper(node->left) + getSizeHelper(node->right);
}

AVLNode* AVLTree::searchHelper(AVLNode* node, int key) const {
    if (!node) return nullptr;

    if (node->key == key) return node;

    AVLNode* left = searchHelper(node->left, key);
    if (left) return left;
    AVLNode* right = searchHelper(node->right, key);
    if (right) return right;

    return nullptr;
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
