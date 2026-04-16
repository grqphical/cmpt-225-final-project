#include "skip_list.hpp"
#include <random>

SkipList::SkipList() {
    level = 0;
    head = Node::Create(-1, maxSkipListLevel); 
}

SkipList::~SkipList() {
    Node* curr = head->next[0];
    while (curr) {
        Node* next = curr->next[0];
        Node::Destroy(curr);
        curr = next;
    }
    Node::Destroy(head);
}

int SkipList::GetRandomLevel() {
    int newLevel = 0;
    static thread_local std::mt19937 generator(std::random_device{}());
    // Using a fast bitwise-style check (simulating 50% probability)
    static thread_local std::uniform_int_distribution<int> distribution(0, 1);

    while (newLevel < maxSkipListLevel && distribution(generator) == 1) {
        newLevel++;
    }
    return newLevel;
}

void SkipList::Insert(int data) {
    // update array must be large enough for maxSkipListLevel
    Node* update[maxSkipListLevel + 1];
    Node* current = head;

    // Start searching from the current highest level of the list
    for (int i = level; i >= 0; i--) {
        while (current->next[i] != nullptr && current->next[i]->data < data) {
            current = current->next[i];
        }
        update[i] = current;
    }

    current = current->next[0];

    if (current == nullptr || current->data != data) {
        int newLevel = GetRandomLevel();

        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++) {
                update[i] = head;
            }
            level = newLevel;
        }

        Node* newNode = Node::Create(data, newLevel); 

        for (int i = 0; i <= newLevel; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }
}

void SkipList::Remove(int data) {
    Node* update[maxSkipListLevel + 1];
    Node* current = head;

    for (int i = level; i >= 0; i--) {
        while (current->next[i] != nullptr && current->next[i]->data < data) {
            current = current->next[i];
        }
        update[i] = current;
    }

    current = current->next[0];

    if (current != nullptr && current->data == data) {
        for (int i = 0; i <= level; i++) {
            if (update[i]->next[i] != current) break;
            update[i]->next[i] = current->next[i];
        }

        Node::Destroy(current);

        // Adjust the list level if the highest level nodes were removed
        while (level > 0 && head->next[level] == nullptr) {
            level--;
        }
    }
}

// ... Search and Print remain largely the same ...

bool SkipList::Search(int data) const {
  Node *current = head;

  for (int i = level; i >= 0; i--) {
    while (current->next[i] and current->next[i]->data < data) {
      current = current->next[i]; // moving forward
    }
  }

  current = current->next[0];

  if (current != nullptr && current->data == data) {
    return true;
  } else {
    return false;
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