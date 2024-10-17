#ifndef LIST_H
#define LIST_H

#include <vector>
using namespace std;
template <typename T> class SortedList {
private:
  vector<T> data;
public:
  int size() { return data.size(); }
  void add(T value) {
    for (int i = 0; i < data.size(); i++) {
      if (value < data[i]) {
        data.insert(data.begin() + i, value);
        return;
      }
    }
    data.push_back(value);
  }
  T get(int i) {
    return data[i];
  }
};

#endif
