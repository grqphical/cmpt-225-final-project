#include "skip_list.hpp"
#include <cstdlib>
#include <iostream>

SkipList::SkipList() {
  head = new Node(0, maxSkipListLevel);
  level = 0;
}

void SkipList::Insert(int data) {
  int newLevel = 0;

  while (newLevel < maxSkipListLevel and (rand() % 2) == 1) {
    newLevel++;
  }

  if (level < newLevel) {
    head->next.resize(newLevel + 1, nullptr);
    level = newLevel;
  }

  Node *current = head;

  std::vector<Node *> Update(level + 1, nullptr);

  for (int i = level; i >= 0; i--) {

    while (current->next[i] and current->next[i]->data < data) {
      current = current->next[i];
    }

    Update[i] = current;
  }

  current = current->next[0];
  // only need to insert if the element doesn't already exist
  if (current == nullptr or current->data != data) {
    Node *newNode = new Node(data, level);

    for (int i = 0; i <= newLevel; i++) {
      newNode->next[i] = Update[i]->next[i];

      Update[i]->next[i] = newNode;
    }
  }
}

void SkipList::Print() const {
  std::cout << "Skip List:" << std::endl;
  for (int i = level; i >= 0; i--) {
    Node *current = head->next[i];

    std::cout << "Level " << i << ": ";

    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next[i];
    }
    std::cout << std::endl;
  }
}