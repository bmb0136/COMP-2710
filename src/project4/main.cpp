#include "question_factory.h"
#include <iostream>

using namespace std;

int main() {
  cout << "*** Welcome to Brandon's Testing Service ***" << endl << endl;

  int questionNum = 1;
  bool repeat = true;
  while (repeat) {
    Question* q = QuestionFactory::create();

    if (q) {
      // TODO: quiz.add(q)
      cout << "Question saved. ";
    } else {
      cout << "Question not saved. ";
    }

    string yn;
    while (true) {
      cout << "Continue? [y/n]: ";
      cin >> yn;
      if (yn == "y") {
        questionNum++;
        cout << endl;
        break;
      }
      if (yn == "n") {
        repeat = false;
        break;
      }
      cout << "[Command not recognized, please try again!]" << endl << endl;
    }
  }

  cout << endl << "*** Thank you for using the testing service. Goodbye! ***" << endl;
  return 0;
}
