#ifndef LIST_H
#define LIST_H

template <typename T> struct Node {
public:
  T value;
  Node<T>* next;
  Node(T value) {
    this->value = value;
    this->next = nullptr;
  }
  void dispose() {
    if (next) {
      next->dispose();
      delete next;
    }
  }
};

template <typename T> class SortedList {
private:
  Node<T>* head;
  int size = 0;
public:
  void add(T value) {
    if (!head) {
      head = new Node<T>(value);
      size = 1;
      return;
    }

    Node<T>* prev = nullptr;
    Node<T>* current = head;

    while (current && value > current->value) {
      prev = current;
      current = current->next;
    }

    if (!current) {
      prev->next = new Node<T>(value);
    } else {
      current->next = new Node<T>(value);
    }

    size++;
  }
  void clear() {
    size = 0;
    if (head) {
      head->dispose();
      delete head;
    }
  }
  T* get(int i) {
    Node<T>* current = head;

    while (i-- > 0) {
      if (!current) {
        return nullptr;
      }
      current = current->next;
    }

    return &current->value;
  }
};

#endif
