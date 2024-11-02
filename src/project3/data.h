#ifndef DATA_H
#define DATA_H

#include <string>
using std::string;

struct DataPoint {
public:
  float value;
  int hour, minute, second;
  string toString() {
    return "TODO";
  }
  static bool fromString(string str, DataPoint& dp) {
    return false;
  }
  bool operator<(DataPoint other) {
    return false;
  }
};

#endif
