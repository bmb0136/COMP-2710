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

const int NUM_RUNS = 10000;
const int AARON_CHANCE = 100 / 3;
const int BOB_CHANCE = 100 / 2;
// Don't need one for Charlie since he never misses

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

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
  int a = A_alive ? 1 : 0;
  int b = B_alive ? 1 : 0;
  int c = C_alive ? 1 : 0;
  return a + b + c >= 2;
}

void Aaron_shoots1(bool& B_alive, bool& C_alive) {
  if (C_alive) {
    C_alive = !randomChance(AARON_CHANCE);
  } else if (B_alive) {
    B_alive = !randomChance(AARON_CHANCE);
  }
}

void Bob_shoots(bool& A_alive, bool& C_alive) {
  if (C_alive) {
    C_alive = !randomChance(BOB_CHANCE);
  } else if (A_alive) {
    A_alive = !randomChance(BOB_CHANCE);
  }
}
