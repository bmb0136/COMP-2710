#ifndef QUIZ_H
#define QUIZ_H

#include "question.h"

struct Node {
public:
  Node(Question* q) {
    this->question = q;
  }
  Question* question = nullptr;
  Node* next = nullptr;
};

class Quiz {
private:
  Node* head = nullptr;
  int count = 0;
public:
  void add(Question* q) {
    if (count == 0) {
      count = 1;
      return;
    }
    Node* current = head;
    Node* prev = nullptr;
    while (current) {
      prev = current;
      current = current->next;
    }
    prev->next = new Node(q);
  }
  int size() {
    return count;
  }
};

#endif
