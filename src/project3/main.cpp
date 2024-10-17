#include <fstream>
#include <iostream>
#include <sstream>
#include "list.h"

using namespace std;

template class SortedList<float>;

int getFileCount();
bool tryParseFile(SortedList<float>& data, ifstream& file);
float getMean(SortedList<float> data);
float getMedian(SortedList<float> data);
float getMode(SortedList<float> data);

int main() {
  cout << "*** Welcome to Brandon's Data Analyzer ***" << endl;

  int files = getFileCount();
  cout << endl; // Examples have this extra newline

  SortedList<float> data;
  for (int i = 0; i < files; i++) {
    string path;

    cout << "Enter the file name for file " << (i + 1) << ": ";
    cin >> path;
    if (path == "quit") {
      cout << "Input cancelled. Proceeding to calculation..." << endl << endl;
      break;
    }

    ifstream file(path);
    if (!file.is_open()) {
      cout << "File not found. Please try again" << endl;
      i--;
      continue;
    }

    SortedList<float> dataFromFile;
    if (!tryParseFile(dataFromFile, file) || dataFromFile.size() == 0) {
      cout << "Not an input file. Illegal content/structure detected. Please try again" << endl << endl;
      i--;
      continue;
    }

    cout << "The list of " << dataFromFile.size() << " values in file " << path << " is:" << endl;
    for (int j = 0; j < dataFromFile.size(); j++) {
      float x = dataFromFile.get(j);
      cout << x << endl;
      data.add(x);
    }

    cout << endl; // Examples have this extra newline
  }

  cout << "*** Summarized Statistics ***" << endl << endl;

  cout << "The orderly sorted list of " << data.size() << " values is:" << endl;
  for (int i = 0; i < data.size(); i++) {
    cout << data.get(i);
    if (i != data.size() - 1) {
      cout << ", ";
    } else {
      cout << endl;
    }
  }
  cout << endl;

  cout << "The mean is " << getMean(data) << endl;
  cout << "The median is " << getMedian(data) << endl;
  cout << "The mode is " << getMode(data) << endl;
  cout << endl; // Examples have this extra newline

  cout << "*** Goodbye ***" << endl;
  return 0;
}

float getMean(SortedList<float> data) {
  float sum = 0;
  for (int i = 0; i < data.size(); i++) {
    sum += data.get(i);
  }
  return sum / data.size();
}

float getMedian(SortedList<float> data) {
  return -1;
}

float getMode(SortedList<float> data) {
  return -1;
}

bool tryParseFile(SortedList<float>& data, ifstream& file) {
  while (!file.eof()) {
    string line;
    getline(file, line);
    if (line == "") {
      break;
    }
    stringstream lineStream(line);

    float value;
    lineStream >> value;
    if (lineStream.fail()) {
      return false;
    }

    data.add(value);
  }
  return true;
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
