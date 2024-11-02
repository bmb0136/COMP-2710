#ifndef LIST_H
#define LIST_H

#include "data.h"
#include <vector>

using namespace std;

typedef bool(*dp_comparator)(DataPoint x, DataPoint y);

class DataList {
private:
  vector<DataPoint> data;
  vector<DataPoint*> byValue, byTime;
  static void add(DataPoint value, vector<DataPoint> main, vector<DataPoint*> ref, dp_comparator lessThan) {
    int left = 0, right = main.size() - 1;

    while (left <= right) {
      int mid = (left + right) / 2;
      DataPoint midVal = main[mid];

      if (lessThan(midVal, value)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    main.push_back(value);
    ref.insert(ref.begin() + left, &main[0]);
  }
public:
  int size() { return data.size(); }
  void add(DataPoint value) {
    add(value, data, byValue, DataPoint::isValueLessThan);
    add(value, data, byTime, DataPoint::isTimeLessThan);
  }
  DataPoint getByTime(int i) {
    return *byTime[i];
  }
  DataPoint getByValue(int i) {
    return *byValue[i];
  }
};

#endif
