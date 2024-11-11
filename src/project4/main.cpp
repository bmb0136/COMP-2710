#include "editor.h"
#include <iostream>

using namespace std;

struct QuizResults { public:
  int correct;
  float points;
};

QuizResults takeQuiz(Quiz quiz);

int main() {
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
    QuizResults results = takeQuiz(quiz);

    cout << "/!\\ Assessment Complete." << endl << endl;

    cout << "=== SESSION LOG ===" << endl;
    cout << "Correct answers: " << results.correct << "/" << quiz.size() << endl;
    cout.precision(2);
    cout << "Final score: " << results.points << "/" << quiz.totalPoints() << endl << endl;
  }

  cout << "*** Thank you for using the testing service. Goodbye! ***" << endl;
  return 0;
}

QuizResults takeQuiz(Quiz quiz) {
  QuizResults result = { 0 };

  for (int i = 0; i < quiz.size(); i++) {
    Question* q = quiz.get(i);
    if (q->ask(i + 1) == AR_CORRECT) {
      result.correct++;
      result.points += q->getPoints();
    }
  }

  return result;
}
