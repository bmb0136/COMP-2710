#include <iostream>
#include "list.h"

using namespace std;

template class SortedList<float>;

int main() {
  cout << "*** Welcome to Brandon's Data Analyzer ***" << endl;

  int files;
  while (true) {
    cout << "Enter the number of files to read: ";
    cin >> files;
    if (cin.fail()) {
      cin.clear();
      string quit;
      cin >> quit;
      if (quit == "quit") {
        files = 0;
        break;
      }
      cin.ignore(99999, '\n');
      cout << "Please enter a non-zero integer" << endl;
    } else {
      break;
    }
  }

  cout << "*** Goodbye ***" << endl;
  return 0;
}
