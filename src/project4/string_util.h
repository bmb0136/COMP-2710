#ifndef STRING_UTIL_H
#define STRING_UTIL_H
#include <string>
using std::string;

class StringUtils {
public:
  static bool compareIgnoreCase(string x, string y) {
    if (x.length() != y.length()) {
      return false;
    }
    for (int i = 0; i < x.length(); i++) {
      if (tolower(x[i]) != tolower(y[i])) {
        return false;
      }
    }
    return true;
  }
};

#endif
