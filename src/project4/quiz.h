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
      head = new Node(q);
      return;
    }
    Node* current = head;
    Node* prev = nullptr;
    while (current) {
      prev = current;
      current = current->next;
    }
    prev->next = new Node(q);
    count++;
  }
  int size() {
    return count;
  }
  Question* get(int i) {
    if (i < 0 || i >= count) {
      return nullptr;
    }
    Node* current = head;
    while (i > 0) {
      if (!current) {
        return nullptr;
      }
      current = current->next;
      i--;
    }
    return current ? current->question : nullptr;
  }
  float totalPoints() {
    Node* current = head;
    float sum = 0.0f;
    while (current) {
      sum += current->question->getPoints();
      current = current->next;
    }
    return sum;
  }
};

#endif