#ifndef QUIZ_H
#define QUIZ_H

#include "question.h"

struct _QuizNode {
public:
  _QuizNode(Question* q) {
    this->question = q;
  }
  Question* question = nullptr;
  _QuizNode* next = nullptr;
};

class Quiz {
private:
  _QuizNode* head = nullptr;
  int count = 0;
public:
  void add(Question* q) {
    if (count == 0) {
      count = 1;
      head = new _QuizNode(q);
      return;
    }
    _QuizNode* current = head;
    _QuizNode* prev = nullptr;
    while (current) {
      prev = current;
      current = current->next;
    }
    prev->next = new _QuizNode(q);
    count++;
  }
  int size() {
    return count;
  }
  void deleteAt(int i) {
    if (i < 0 || i >= count) {
      return;
    }

    if (i == 0) {
      _QuizNode* oldHead = head;
      head = head->next;
      delete oldHead->question;
      delete oldHead;
      count--;
      return;
    }

    _QuizNode* current = head;
    _QuizNode* prev = nullptr;

    while (i > 0) {
      prev = current;
      current = current->next;
      i--;
    }

    if (!current) {
      return;
    }

    prev->next = current->next;

    delete current->question;
    delete current;
    count--;
  }
  void replaceAt(int i, Question* q) {
    if (i < 0 || i >= count) {
      return;
    }

    _QuizNode* current = head;
    while (i > 0) {
      current = current->next;
      i--;
    }

    delete current->question;
    current->question = q;
  }
  Question* get(int i) {
    if (i < 0 || i >= count) {
      return nullptr;
    }
    _QuizNode* current = head;
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
    _QuizNode* current = head;
    float sum = 0.0f;
    while (current) {
      sum += current->question->getPoints();
      current = current->next;
    }
    return sum;
  }
};

#endif
