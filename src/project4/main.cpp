#include <iostream>
#include "string_util.h"

using namespace std;

int main() {
  cout << "*** Welcome to Brandon's Testing Service ***" << endl << endl;

  string response;
  int type;
  while (true) {
    response.clear();
    cout << "Type of question [mcq/tf/wr]: ";
    cin >> response;
    if (StringUtils::compareIgnoreCase(response, "mcq")) {
      type = 1;
      break;
    }
    if (StringUtils::compareIgnoreCase(response, "tf")) {
      type = 2;
      break;
    }
    if (StringUtils::compareIgnoreCase(response, "wr")) {
      type = 3;
      break;
    }
    cout << "[Command not recognized, please try again!]" << endl << endl;
  }

  cout << endl << "*** Thank you for using the testing service. Goodbye! ***" << endl;
  return 0;
}
