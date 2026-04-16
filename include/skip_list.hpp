#pragma once
#include <iostream>
#include <algorithm>
#include <cstdint>
using std::int64_t;

const int64_t maxSkipListLevel = 16; // Increased for better distribution

class Node
{
public:
    int64_t data;
    int64_t level;
    Node *next[1];

    Node(int64_t data, int64_t level) : data(data), level(level) {}

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

    void Insert(int64_t data);
    void Remove(int64_t data);
    bool Search(int64_t data) const;
    void Print() const;

private:
    int64_t GetRandomLevel();
    Node *head;
    int64_t level;
};