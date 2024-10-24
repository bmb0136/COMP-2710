#include <fstream>
#include <iostream>
#include <sstream>
#include "list.h"

using namespace std;

template class SortedList<float>;

int getFileCount();
bool tryParseFile(vector<float>& data, ifstream& file);
float getMean(SortedList<float> data);
float getMedian(SortedList<float> data);
float getMode(SortedList<float> data);
void saveStatistics(SortedList<float> data);
bool readFile(string path, SortedList<float>& data);

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

bool readFile(string path, SortedList<float>& data) {

  ifstream file(path);
  if (!file.is_open()) {
    cout << "File not found. Please try again" << endl;
    return false;
  }

  vector<float> dataFromFile;
  if (!tryParseFile(dataFromFile, file) || dataFromFile.size() == 0) {
    cout << "Not an input file. Illegal content/structure detected. Please try again" << endl << endl;
    file.close();
    return false;
  }

  file.close();

  cout << "The list of " << dataFromFile.size() << " values in file " << path << " is:" << endl;
  for (int j = 0; j < dataFromFile.size(); j++) {
    float x = dataFromFile[j];
    cout << x << endl;
    data.add(x);
  }

  cout << endl; // Examples have this extra newline
  return true;
}

void saveStatistics(SortedList<float> data) {
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
    output << data.get(i);
    cout << data.get(i);
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

float getMean(SortedList<float> data) {
  float sum = 0;
  for (int i = 0; i < data.size(); i++) {
    sum += data.get(i);
  }
  return sum / data.size();
}

float getMedian(SortedList<float> data) {
  int len = data.size();
  // Two median values
  if (len % 2 == 0) {
    return (data.get(len / 2) + data.get((len / 2) - 1)) / 2.0f;
  }
  // One median value
  return data.get(len / 2);
}

float getMode(SortedList<float> data) {
  float sum = 0;
  int count = 0;
  int frequency = 0;

  int i = 0;
  while (i < data.size()) {
    int j = 0;
    while ((i + j) < data.size() && data.get(i) == data.get(i + j)) {
      j++;
    }
    if (j > frequency) {
      frequency = j;
      count = 1;
      sum = data.get(i);
    } else if (j == frequency) {
      count++;
      sum += data.get(i);
    }
    i += j;
  }

  return sum / count;
}

bool tryParseFile(vector<float>& data, ifstream& file) {
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
