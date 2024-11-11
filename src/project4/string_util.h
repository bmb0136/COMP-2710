#ifndef STRING_UTIL_H
#define STRING_UTIL_H
#include <sstream>
#include <string>
using std::string;
using std::stringstream;

class StringUtils {
public:
  static bool compareIgnoreCase(string x, string y) {
    if (x.length() != y.length()) {
      return false;
    }
    for (size_t i = 0; i < x.length(); i++) {
      if (tolower(x[i]) != tolower(y[i])) {
        return false;
      }
    }
    return true;
  }
  static bool tryParseFloat(string input, float& out, float min, float max) {
    stringstream stream(input);
    stream >> out;
    if (stream.fail()) {
      return false;
    }
    return out >= min && out <= max;
  }
  static bool tryParseInt(string input, int& out, int min, int max) {
    stringstream stream(input);
    stream >> out;
    if (stream.fail()) {
      return false;
    }
    return out >= min && out <= max;
  }
  static bool tryParseBool(string input, bool& out) {
    bool isTrue = StringUtils::compareIgnoreCase(input, "t") || StringUtils::compareIgnoreCase(input, "true");
    bool isFalse = StringUtils::compareIgnoreCase(input, "f") || StringUtils::compareIgnoreCase(input, "false");
    if (isTrue) {
      out = true;
      return true;
    }
    if (isFalse) {
      out = false;
      return true;
    }
    return false;
  }
};

#endif
