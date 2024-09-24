// TODO: header

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <string_view>

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
};
typedef void(*shootFunc)(bool&, bool&);
StrategyResult simulateTruel(shootFunc aaronStrategy);

int main() {
  // Init random
  srand(time(0));

  cout << "*** Welcome to Brandon's Truel of the Fates Simulator ***" << endl;

  cout << "Ready to run strategy 1 (run " << NUM_RUNS << " times)" << endl;
  waitForKey();

  StrategyResult strategy1;
  memset(&strategy1, 0, sizeof(StrategyResult));

  for (int i = 0; i < NUM_RUNS; i++) {
    strategy1.combine(simulateTruel(&Aaron_shoots1));
  }


  cout << "Ready to run strategy 2 (run " << NUM_RUNS << " times)" << endl;
  waitForKey();
  StrategyResult strategy2;
  memset(&strategy2, 0, sizeof(StrategyResult));

  for (int i = 0; i < NUM_RUNS; i++) {
    strategy2.combine(simulateTruel(&Aaron_shoots2));
  }


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
  memset(&result, 0, sizeof(StrategyResult));

  bool a = true, b = true, c = true;
  int i = 0;

  while (at_least_two_alive(a, b, c)) {
    switch (i) {
      case 0:
        aaronStrategy(b, c);
        break;
      case 1:
        Bob_shoots(a, c);
        break;
      case 2:
        Charlie_shoots(a, b);
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
