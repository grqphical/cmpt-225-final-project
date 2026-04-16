#pragma once

class AVLNode
{
public:
    AVLNode *left;
    AVLNode *right;
    int64_t key;
    int64_t height;

    AVLNode(int key) : key(key), left(nullptr), right(nullptr), height(0) {}
};

class AVLTree
{
public:
    AVLTree() = default;
    ~AVLTree();

    /* 4 Main Comparison Functions: Insert, Search, Delete, and Print */

    // Inserts a node to the tree (does not insert if the key is a duplicate)
    void Insert(int64_t key);

    // Searches for a node in the tree and returns true (false if not found)
    bool Search(int64_t key) const;

    // Deletes a node in the tree
    void Delete(int64_t key);

    // Prints the level order traversal of the tree
    void Print() const;

    /* Utility Functions */

    // Searches for a node in the tree and returns the node (nullptr if not found)
    AVLNode *searchNode(int64_t key) const;

    // Returns the height of the node (0 if node is null)
    int64_t getHeight(AVLNode *node) const;

    // Returns the number of nodes in the tree.
    // Does so recursively so other operations' speed won't be impacted when comparing
    int64_t getSize() const;

    // Testing function to ensure the tree has the BST sorted property
    bool isSorted() const;

    // Testing function to ensure the tree has the AVL balanced property
    bool isBalanced() const;

private:
    AVLNode *root = nullptr;

    /* Core Helper Functions*/

    void freeHelper(AVLNode *node);

    // Updates height of the given node
    void updateHeight(AVLNode *updateNode);

    // Rotates a rightward chain to the left and returns the new root (null if node or node->right are null)
    AVLNode *rotateLeft(AVLNode *node);

    // Rotates a leftward chain to the right and returns the new root (null if node or node->left are null)
    AVLNode *rotateRight(AVLNode *node);

    // Returns true if the node satisfies the balance factor: |h(left) - h(right)| <= 1
    bool isBalancedFactored(AVLNode *node) const;

    AVLNode *insertHelper(AVLNode *insertAtNode, int64_t key);

    AVLNode *deleteHelper(AVLNode *deleteAtNode, int64_t key);

    // Rotates the tree where given a node with an unblanced factor
    AVLNode *restructure(AVLNode *restructureAtNode);

    /* Utility Helper Functions */

    int64_t getSizeHelper(AVLNode *node) const;

    AVLNode *searchHelper(AVLNode *node, int64_t key) const;

    bool isSortedHelper(AVLNode *node) const;

    bool isBalancedHelper(AVLNode *node) const;
};
