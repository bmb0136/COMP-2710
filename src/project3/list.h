#ifndef LIST_H
#define LIST_H

#include "data.h"
#include <vector>

using namespace std;

typedef bool(*dp_comparator)(DataPoint x, DataPoint y);

class DataList {
private:
  vector<DataPoint> byValue, byTime;
  static void add(DataPoint value, vector<DataPoint>& data, dp_comparator lessThan) {
    int left = 0, right = data.size() - 1;

    while (left <= right) {
      int mid = (left + right) / 2;
      DataPoint midVal = data[mid];

      if (lessThan(midVal, value)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    data.insert(data.begin() + left, value);
  }
public:
  int size() { return byValue.size(); }
  void add(DataPoint value) {
    add(value, byValue, DataPoint::isValueLessThan);
    add(value, byTime, DataPoint::isTimeLessThan);
  }
  DataPoint getByTime(int i) {
    return byTime[i];
  }
  DataPoint getByValue(int i) {
    return byValue[i];
  }
};

#endif
