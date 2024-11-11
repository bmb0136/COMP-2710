#include "editor.h"
#include "taker.h"
#include <iostream>

using namespace std;

#define UNIT_TESTING

int main() {
#ifdef UNIT_TESTING
  cout << "*** This is the debug version ***" << endl << endl;
  return 0;
#endif
  cout << "*** Welcome to Brandon's Testing Service ***" << endl << endl;

  Quiz quiz = QuizEditor::createQuiz();

  cout << "=== SESSION LOG ===" << endl;
  cout << "Total questions: " << quiz.size() << endl;
  cout << "Total point values: " << quiz.totalPoints() << endl;
  cout << endl;

  bool take;
  string yn;
  while (true) {
    cout << "/!\\ Begin assessment? [y/n]: ";
    getline(cin, yn);

    char c = yn.length() == 1 ? yn[0] : 0;
    c &= ~0b00100000;
    if (c == 'N') {
      take = false;
      break;
    }
    if (c == 'Y') {
      take = true;
      break;
    }
    cout << "[Command not recognized, please try again!]" << endl << endl;
  }
  cout << endl;

  if (take) {
    QuizResult score = QuizTaker::take(quiz);
    cout << endl;

    cout << "/!\\ Assessment Complete." << endl << endl;

    cout << "=== SESSION LOG ===" << endl;
    score.print();
    cout << endl;
  }

  cout << "*** Thank you for using the testing service. Goodbye! ***" << endl;
  return 0;
}
