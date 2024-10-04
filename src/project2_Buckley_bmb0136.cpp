// project2_Buckley_bmb0136.cpp
// Author: Brandon Buckley (bmb0136)
//
// Build instructions:
// See the README in https://github.com/bmb0136/COMP-2710
//
// Help used:
// 

#include <cassert>
#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

const int NUM_RUNS = 10000;
const int AARON_CHANCE = 100 / 3;
const int BOB_CHANCE = 100 / 2;
// Don't need one for Charlie since he never misses

// Required functions
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);

// My functions
void waitForKey();
bool randomChance(int percent);

struct StrategyResult {
public:
  int aaronWins, bobWins, charlieWins;
  void combine(StrategyResult other) {
    aaronWins += other.aaronWins;
    bobWins += other.bobWins;
    charlieWins += other.charlieWins;
  }
  bool isBetterForAaron(StrategyResult other) {
    return aaronWins > other.aaronWins;
  }
};
typedef void(*shootFunc)(bool&, bool&);
StrategyResult simulateTruel(shootFunc aaronStrategy);
void printResult(StrategyResult result);

// Unit tests
void test_at_least_two_alive();
void test_Aaron_shoots1();
void test_Aaron_shoots2();
void test_Bob_shoots();
void test_Charlie_shoots();

int main() {
  cout << "*** Welcome to Brandon's Truel of the Fates Simulator ***" << endl;
  // Init random
  srand(time(0));

  test_at_least_two_alive();
  waitForKey();
  test_Aaron_shoots1();
  waitForKey();
  test_Bob_shoots();
  waitForKey();
  test_Charlie_shoots();
  waitForKey();

  cout << "Ready to run strategy 1 (run " << NUM_RUNS << " times)" << endl;
  waitForKey();

  StrategyResult strategy1;
  strategy1.aaronWins = strategy1.bobWins = strategy1.charlieWins = 0;

  for (int i = 0; i < NUM_RUNS; i++) {
    strategy1.combine(simulateTruel(&Aaron_shoots1));
  }

  printResult(strategy1);
  cout << endl;

  cout << "Ready to run strategy 2 (run " << NUM_RUNS << " times)" << endl;
  waitForKey();
  StrategyResult strategy2;
  strategy2.aaronWins = strategy2.bobWins = strategy2.charlieWins = 0;

  for (int i = 0; i < NUM_RUNS; i++) {
    strategy2.combine(simulateTruel(&Aaron_shoots2));
  }

  printResult(strategy2);
  cout << endl;

  if (strategy1.aaronWins > strategy2.aaronWins) {
    cout << "Strategy 1 is better than strategy 2." << endl;
  } else {
    cout << "Strategy 2 is better than strategy 1." << endl;
  }

  return 0;
}

void test_at_least_two_alive() {
  cout << "Unit Testing 1: Function 1 at_least_two_alive()" << endl;

  cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive" << endl;
  assert(true == at_least_two_alive(true, true, true));
  cout << "\t\tCase passed" << endl;

  cout << "\tCase 2: Aaron alive, Bob alive, Charlie dead" << endl;
  assert(true == at_least_two_alive(true, true, false));
  cout << "\t\tCase passed" << endl;

  cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive" << endl;
  assert(true == at_least_two_alive(true, false, true));
  cout << "\t\tCase passed" << endl;

  cout << "\tCase 4: Aaron alive, Bob dead, Charlie dead" << endl;
  assert(false == at_least_two_alive(true, false, false));
  cout << "\t\tCase passed" << endl;
  
  cout << "\tCase 5: Aaron dead, Bob alive, Charlie alive" << endl;
  assert(true == at_least_two_alive(false, true, true));
  cout << "\t\tCase passed" << endl;

  cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead" << endl;
  assert(false == at_least_two_alive(false, true, false));
  cout << "\t\tCase passed" << endl;

  cout << "\tCase 7: Aaron dead, Bob dead, Charlie alive" << endl;
  assert(false == at_least_two_alive(false, false, true));
  cout << "\t\tCase passed" << endl;

  cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead" << endl;
  assert(false == at_least_two_alive(false, false, false));
  cout << "\t\tCase passed" << endl;
}

void test_Aaron_shoots1() {
  cout << "Unit Testing 2: Aaron_shoots1(Bob_alive, Charlie_alive)" << endl;

  bool b, c;

  cout << "\tCase 1: Bob alive, Charlie alive\n\t\tAaron is shooting at Charlie" << endl;
  b = true;
  c = true;
  Aaron_shoots1(b, c);
  assert(true == b);

  cout << "\tCase 2: Bob dead, Charlie alive\n\t\tAaron is shooting at Charlie" << endl;
  b = false;
  c = true;
  Aaron_shoots1(b, c);
  assert(false == b);

  cout << "\tCase 2: Bob alive, Charlie dead\n\t\tAaron is shooting at Bob" << endl;
  b = true;
  c = false;
  Aaron_shoots1(b, c);
  assert(false == c);
}

void test_Aaron_shoots2() {
  cout << "Unit Testing 4: Aaron_shoots2(Bob_alive, Charlie_alive)" << endl;

  bool b, c;

  cout << "\tCase 1: Bob alive, Charlie alive\n\t\tAaron intentionally misses his first shot\n\t\tBoth Bob and Charlie are alive." << endl;
  b = true;
  c = true;
  Aaron_shoots2(b, c);
  assert(true == b);
  assert(true == c);

  cout << "\tCase 2: Bob dead, Charlie alive\n\t\tAaron is shooting at Charlie" << endl;
  b = false;
  c = true;
  Aaron_shoots2(b, c);
  assert(false == b);

  cout << "\tCase 3: Bob alive, Charlie dead\n\t\tAaron is shooting at Bob" << endl;
  b = true;
  c = false;
  Aaron_shoots2(b, c);
  assert(false == c);
}

void test_Bob_shoots() {
  cout << "Unit Testing 3: Bob_shoots(Aaron_alive, Charlie_alive)" << endl;

  bool a, c;

  cout << "\tCase 1: Aaron alive, Charlie alive\n\t\tBob is shooting at Charlie" << endl;
  a = true;
  c = true;
  Bob_shoots(a, c);
  assert(true == a);

  cout << "\tCase 2: Aaron dead, Charlie alive\n\t\tBob is shooting at Charlie" << endl;
  a = false;
  c = true;
  Bob_shoots(a, c);
  assert(false == a);

  cout << "\tCase 3: Aaron alive, Charlie dead\n\t\tBob is shooting at Aaron" << endl;
  a = true;
  c = false;
  Bob_shoots(a, c);
  assert(false == c);
}

void test_Charlie_shoots() {
  cout << "Unit Testing 4: Charlie_shoots(Aaron_alive, Bob_alive)" << endl;

  bool a, b;

  cout << "\tCase 1: Aaron alive, Bob alive\n\t\tCharlie is shooting at Bob" << endl;
  a = true;
  b = true;
  Charlie_shoots(a, b);
  assert(true == a);
  assert(false == b);

  cout << "\tCase 2: Aaron dead, Bob alive\n\t\tCharlie is shooting at Bob" << endl;
  a = false;
  b = true;
  Charlie_shoots(a, b);
  assert(false == a);
  assert(false == b);

  cout << "\tCase 3: Aaron alive, Bob dead\n\t\tCharlie is shooting at Aaron" << endl;
  a = true;
  b = false;
  Charlie_shoots(a, b);
  assert(false == a);
  assert(false == b);
}

void waitForKey() {
  cout << "Press any key to continue...";
  cin.ignore().get();
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

void Charlie_shoots(bool& A_alive, bool& B_alive) {
  if (B_alive) {
    B_alive = false; // He never misses, so just kill them
  } else if (A_alive) {
    A_alive = false;
  }
}

void Aaron_shoots2(bool& B_alive, bool& C_alive) {
  // We do not know if we are on the first turn,
  // but if Bob and Charlie are alive then we can assume its the first turn.
  // This is true because after 1 round either Bob or Charlie will be dead,
  // since Bob will try to shoot Charlie and vice versa. And Charlie does not miss,
  // so if either Bob will die or Charlie will die by the end of round 1.
  if (B_alive && C_alive) {
    return;
  }

  if (C_alive) {
    C_alive = !randomChance(AARON_CHANCE);
  } else if (B_alive) {
    B_alive = !randomChance(AARON_CHANCE);
  }
}

StrategyResult simulateTruel(shootFunc aaronStrategy) {
  StrategyResult result;
  result.aaronWins = result.bobWins = result.charlieWins = 0;

  bool a = true, b = true, c = true;
  int i = 0;

  while (at_least_two_alive(a, b, c)) {
    switch (i) {
      case 0:
        if (a) {
          aaronStrategy(b, c);
        }
        break;
      case 1:
        if (b) {
          Bob_shoots(a, c);
        }
        break;
      case 2:
        if (c) {
          Charlie_shoots(a, b);
        }
        break;
    }
    i++;
    i %= 3;
  }

  if (a) {
    result.aaronWins++;
  } else if (b) {
    result.bobWins++;
  } else if (c) {
    result.charlieWins++;
  }

  return result;
}

void printResult(StrategyResult result) {
  float aaronPercent = (float)result.aaronWins / NUM_RUNS * 100.0f;
  float bobPercent = (float)result.bobWins / NUM_RUNS * 100.0f;
  float charliePercent = (float)result.charlieWins / NUM_RUNS * 100.0f;

  cout << "Aaron won " << result.aaronWins << "/" << NUM_RUNS << " truels or " << aaronPercent << "%" << endl; 
  cout << "Bob won " << result.bobWins << "/" << NUM_RUNS << " truels or " << bobPercent << "%" << endl; 
  cout << "Charlie won " << result.charlieWins << "/" << NUM_RUNS << " truels or " << charliePercent << "%" << endl; 
}

bool randomChance(int percent) {
  return (rand() % 100) < percent;
}
