#pragma once

class AVLNode {
public:
    AVLNode* left;
    AVLNode* right;
    int key;
    int height;

    AVLNode(int key) : key(key), left(nullptr), right(nullptr), height(0) {}
};

class AVLTree {
public:
    AVLTree() = default;
    ~AVLTree() = default;

    // Inserts a node to the tree (does not insert if the key is a duplicate)
    void insert(int key);

    // Returns the height of the node (0 if node is null)
    int getHeight(AVLNode* node) const;

    // Prints the level order traversal of the tree
    void levelOrder() const;

    // Testing function to ensure the tree has the BST sorted property
    bool isSorted() const;

    // Testing function to ensure the tree has the AVL balanced property
    bool isBalanced() const;

private:
    AVLNode* root = nullptr;

    // Updates height of the given node
    void updateHeight(AVLNode* updateNode);

    // Rotates a rightward chain to the left and returns the new root (null if node or node->right are null)
    AVLNode* rotateLeft(AVLNode* node);

    // Rotates a leftward chain to the right and returns the new root (null if node or node->left are null)
    AVLNode* rotateRight(AVLNode* node);

    // Returns true if the node satisfies the balance factor: |h(left) - h(right)| <= 1
    bool isBalancedFactored(AVLNode* node) const;

    AVLNode* insertHelper(AVLNode* insertAtNode, int key);

    // Rotates the tree where given a node with an unblanced factor
    AVLNode* restructure(AVLNode* restructureAtNode);
    
    bool isSortedHelper(AVLNode* node) const;

    bool isBalancedHelper(AVLNode* node) const;
};
