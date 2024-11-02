// main.cpp
// Author: Brandon Buckley (bmb0136)
//
// Build Instructions: See the README in https://github.com/bmb0136/COMP-2710
//
// NOTE: Tests are within the src/project3 folder, not the root of the repo
//
// Help Used:
// I used https://en.cppreference.com/w/cpp/container/vector for the vector<T> docs

#include <fstream>
#include <iostream>
#include <sstream>
#include "data.h"
#include "list.h"

using namespace std;

template class SortedList<DataPoint>;

typedef SortedList<DataPoint> Data;

int getFileCount();
bool tryParseFile(vector<DataPoint>& data, ifstream& file);
float getMean(Data data);
float getMedian(Data data);
float getMode(Data data);
void saveStatistics(Data data);
bool readFile(string path, Data& data);

int main() {
  cout << "*** Welcome to Brandon's Data Analyzer ***" << endl;

  int files = getFileCount();
  cout << endl; // Examples have this extra newline

  Data data;
  for (int i = 0; i < files; i++) {
    string path;

    cout << "Enter the file name for file " << (i + 1) << ": ";
    cin >> path;
    if (path == "quit") {
      cout << "Input cancelled. Proceeding to calculation..." << endl << endl;
      break;
    }

    if(!readFile(path, data)) {
      i--;
    }
  }

  if (data.size() > 0) {
    saveStatistics(data);
  }
  cout << endl;

  cout << "*** Goodbye ***" << endl;
  return 0;
}

bool readFile(string path, Data& data) {

  ifstream file(path);
  if (!file.is_open()) {
    cout << "File not found. Please try again" << endl;
    return false;
  }

  vector<DataPoint> dataFromFile;
  if (!tryParseFile(dataFromFile, file) || dataFromFile.size() == 0) {
    cout << "Not an input file. Illegal content/structure detected. Please try again" << endl << endl;
    file.close();
    return false;
  }

  file.close();

  cout << "The list of " << dataFromFile.size() << " values in file " << path << " is:" << endl;
  for (size_t j = 0; j < dataFromFile.size(); j++) {
    DataPoint x = dataFromFile[j];
    cout << x.toString() << endl;
    data.add(x);
  }

  cout << endl; // Examples have this extra newline
  return true;
}

void saveStatistics(Data data) {
  ofstream output("output.txt");
  if (!output.is_open()) {
    cout << "Failed to save results" << endl;
    return;
  }

  output << "*** Summarized Statistics ***" << endl << endl;
  cout << "*** Summarized Statistics ***" << endl << endl;

  output << "The orderly sorted list of " << data.size() << " values is:" << endl;
  cout << "The orderly sorted list of " << data.size() << " values is:" << endl;
  for (int i = 0; i < data.size(); i++) {
    output << data.get(i).value;
    cout << data.get(i).value;
    if (i != data.size() - 1) {
      output << ", ";
      cout << ", ";
    } else {
      output << endl;
      cout << endl;
    }
  }
  output << endl;
  cout << endl;

  output << "The mean is " << getMean(data) << endl;
  cout << "The mean is " << getMean(data) << endl;
  output << "The median is " << getMedian(data) << endl;
  cout << "The median is " << getMedian(data) << endl;
  output << "The mode is " << getMode(data) << endl;
  cout << "The mode is " << getMode(data) << endl;

  output.close();
}

float getMean(Data data) {
  float sum = 0;
  for (int i = 0; i < data.size(); i++) {
    sum += data.get(i).value;
  }
  return sum / data.size();
}

float getMedian(Data data) {
  int len = data.size();
  // Two median values
  if (len % 2 == 0) {
    return (data.get(len / 2).value + data.get((len / 2) - 1).value) / 2.0f;
  }
  // One median value
  return data.get(len / 2).value;
}

// Since the data is sorted, we can just count the
// number of duplicate elements in a row and maximize
// for the frequency, with the edge case that if
// the frequency is the same we average them together
// instead of replacing the current max
float getMode(Data data) {
  float sum = 0;
  int count = 0;
  int maxFrequency = 0;

  int i = 0;
  while (i < data.size()) {
    // We can start at n=1 since data[i + n] == data[i] will always be true for n=0
    int n = 1;
    while ((i + n) < data.size() && data.get(i).value == data.get(i + n).value) {
      n++;
    }
    if (n > maxFrequency) {
      maxFrequency = n;
      count = 1;
      sum = data.get(i).value;
    } else if (n == maxFrequency) {
      count++;
      sum += data.get(i).value;
    }
    i += n;
  }

  return sum / count;
}

bool tryParseFile(vector<DataPoint>& data, ifstream& file) {
  while (!file.eof()) {
    string line;
    getline(file, line);
    if (line == "") {
      break;
    }
    stringstream lineStream(line);

    string raw;
    lineStream >> raw;
    if (lineStream.fail()) {
      return false;
    }

    DataPoint value;
    if (!DataPoint::fromString(raw, value)) {
      return false;
    }

    data.push_back(value);
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
