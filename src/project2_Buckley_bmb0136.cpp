// TODO: header

#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

// Required functions
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);

// My functions
void waitForKey();
bool randomChance(int percent);

// 3 required constants
const int NUM_RUNS = 10000;

int main() {
  // Init random
  srand(time(0));

  cout << "*** Welcome to Brandon's Truel of the Fates Simulator ***" << endl;

  return 0;
}

void waitForKey() {
  cout << "Press any key to continue...";
  cin.ignore().get();
}

bool randomChance(int percent) {
  return (rand() % 100) < percent;
}
