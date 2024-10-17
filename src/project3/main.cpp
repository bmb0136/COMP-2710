#include <iostream>
#include "list.h"

using namespace std;

template class SortedList<float>;

int getFileCount();

int main() {
  cout << "*** Welcome to Brandon's Data Analyzer ***" << endl;

  int files = getFileCount();

  cout << "*** Goodbye ***" << endl;
  return 0;
}

int getFileCount() {
  int files;
  while (true) {
    cout << "Enter the number of files to read: ";
    cin >> files;
    if (cin.fail()) {
      cin.clear();
      string quit;
      cin >> quit;
      if (quit == "quit") {
        return 0;
      }
      cin.ignore(99999, '\n');
      cout << "Please enter a non-zero integer" << endl;
    } else {
      break;
    }
  }

  return files;
}
