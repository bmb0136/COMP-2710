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
    int left = 0, right = data.size() - 1;

    while (left <= right) {
      int mid = (left + right) / 2;
      T midVal = data[mid];

      if (midVal < value) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    data.insert(data.begin() + left, value);
  }
  T get(int i) {
    return data[i];
  }
};

#endif
