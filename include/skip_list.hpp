#pragma once
#include <iostream>
#include <algorithm>
#include <cstdint>
using std::int64_t;

const int64_t maxSkipListLevel = 32; // Increased for better distribution

class Node
{
public:
    int64_t data;
    int64_t level;
    Node *next[1];

    Node(int64_t data, int64_t level) : data(data), level(level) {}

    // Creates a new Node
    //
    // We do it this way to manage memory manually, improving performance and reducing the # of memory allocations needed
    static Node *Create(int data, int level)
    {
        size_t size = sizeof(Node) + (level * sizeof(Node *));

        void *storage = ::operator new(size);
        Node *newNode = new (storage) Node(data, level);

        // Initialize all pointers to nullptr
        for (int i = 0; i <= level; i++)
        {
            newNode->next[i] = nullptr;
        }

        return newNode;
    }

    // Deletes a node
    //
    // Because we used manual memory management, we have to explicitly delete the memory once we are done with it
    static void Destroy(Node *node)
    {
        if (!node)
            return;
        node->~Node();
        ::operator delete(node);
    }
};

class SkipList
{
public:
    SkipList();
    ~SkipList();

    // Inserts a node into the SkipList
    void Insert(int64_t data);
    // Removes a node from the SkipList. If the node doesn't exist, the function does nothing
    void Remove(int64_t data);
    // Searches for a given node in the SkipList, returning true if the node is found
    bool Search(int64_t data) const;
    // Prints the SkipList to the console
    void Print() const;

private:
    // Helper function to generate a random level to place the next node on
    int64_t GetRandomLevel();
    Node *head;
    int64_t level;
};