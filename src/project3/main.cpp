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
      cin.ignore(99999, '\n');
      cout << "Invalid number" << endl;
    } else {
      break;
    }
  }

  return 0;
}
