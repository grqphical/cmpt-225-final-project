#pragma once
#include <iostream>
#include <algorithm>

const int maxSkipListLevel = 16; // Increased for better distribution

class Node {
public:
    int data;
    int level;
    Node* next[1]; 

    Node(int data, int level) : data(data), level(level) {}
    
    static Node* Create(int data, int level) {
        size_t size = sizeof(Node) + (level * sizeof(Node*));
        
        void* storage = ::operator new(size);
        Node* newNode = new (storage) Node(data, level);
        
        // Initialize all pointers to nullptr
        for (int i = 0; i <= level; i++) {
            newNode->next[i] = nullptr;
        }
        
        return newNode;
    }

    static void Destroy(Node* node) {
        if (!node) return;
        node->~Node();            
        ::operator delete(node);
    }
};

class SkipList {
public:
    SkipList();
    ~SkipList();

    void Insert(int data);
    void Remove(int data);
    bool Search(int data) const;
    void Print() const;

private:
    int GetRandomLevel();
    Node* head;
    int level;
};