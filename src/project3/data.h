#ifndef DATA_H
#define DATA_H

#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

static bool read2DigitPaddedNum(stringstream& ss, int& value, int min, int max) {
  char tens, ones;

  ss >> tens;
  if (ss.fail() || tens < '0' || tens > '9') {
    return false;
  }

  ss >> ones;
  if (ss.fail() || ones < '0' || ones > '9') {
    return false;
  }

  value = (10 * (tens - '0')) + (ones - '0');

  return value >= min && value <= max;
}

struct DataPoint {
public:
  float value;
  int hour, minute, second;
  string toString() {
    stringstream ss;

    ss << value << '\t';
    ss << setw(2) << setfill('0');
    ss << hour << '.' << minute << '.' << second;

    return ss.str();
  }
  static bool fromString(string str, DataPoint& dp) {
    stringstream ss(str);

    // Read value
    ss >> dp.value;
    if (ss.fail()) {
      return false;
    }

    // Read \t
    if (ss.get() != '\t') {
      return false;
    }

    // Read hour
    if (!read2DigitPaddedNum(ss, dp.hour, 0, 24)) {
      return false;
    }
   
    // Read .
    if (ss.get() != '.') {
      return false;
    }

    // Read minute
    if (!read2DigitPaddedNum(ss, dp.minute, 0, 60)) {
      return false;
    }
   
    // Read .
    if (ss.get() != '.') {
      return false;
    }
    
    // Read second
    if (!read2DigitPaddedNum(ss, dp.second, 0, 60)) {
      return false;
    }

    // Check for \n or eof
    if (ss.get() != '\n' && !ss.eof()) {
      return false;
    }

    return true;
  }
  static bool isTimeLessThan(DataPoint x, DataPoint other) {
    if (x.hour < other.hour) {
      return true;
    }
    if (x.minute < other.minute) {
      return true;
    }
    return x.second < other.second;
  }
  static bool isValueLessThan(DataPoint x, DataPoint other) {
    return x.value < other.value;
  }
};

#endif
