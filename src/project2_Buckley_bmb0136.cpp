// TODO: header

#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

const int NUM_RUNS = 10000;
const int AARON_CHANCE = 3;
const int BOB_CHANCE = 2;
// Don't need one for Charlie since he never misses

// Required functions
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);

// My functions
void waitForKey();

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

int main() {
  // Init random
  srand(time(0));

  cout << "*** Welcome to Brandon's Truel of the Fates Simulator ***" << endl;

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
    if ((rand() % AARON_CHANCE) == 0) {
      C_alive = false;
    }
  } else if (B_alive) {
    if ((rand() % AARON_CHANCE) == 0) {
      B_alive = false;
    }
  }
}

void Bob_shoots(bool& A_alive, bool& C_alive) {
  if (C_alive) {
    if ((rand() % BOB_CHANCE) == 0) {
      C_alive = false;
    }
  } else if (A_alive) {
    if ((rand() % BOB_CHANCE) == 0) {
      A_alive = false;
    }
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
    if ((rand() % AARON_CHANCE) == 0) {
      C_alive = false;
    }
  } else if (B_alive) {
    if ((rand() % AARON_CHANCE) == 0) {
      B_alive = false;
    }
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
