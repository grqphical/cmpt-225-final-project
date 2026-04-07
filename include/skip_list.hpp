#pragma once
#include <vector>

const int maxSkipListLevell = 5;

class Node {
public:
    int data;
    std::vector<Node*> next; 
    Node(int data, int level) : data(data), next(level + 1, nullptr) {}
};

template <typename T>
class SkipList {
public:
    SkipList();

    void Insert(int data);
    void Remove(int data);
    bool Search(int data) const;
    void Print() const;
private:
    Node* head;
    int level;
};