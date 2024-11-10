#include "question.h"
#include "question_factory.h"
#include "quiz.h"
#include <iostream>

using namespace std;

Quiz createQuiz(); 

struct QuizResults {
public:
  int correct;
  float points;
};

QuizResults takeQuiz(Quiz quiz);

int main() {
  cout << "*** Welcome to Brandon's Testing Service ***" << endl << endl;

  Quiz quiz = createQuiz();

  bool take;
  string yn;
  while (true) {
    cout << "/!\\ Begin assessment? [y/n]: ";
    cin >> yn;

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
    cout << "Final score: " << fixed << results.points << "/" << quiz.totalPoints() << endl << endl;
  }

  cout << endl << "*** Thank you for using the testing service. Goodbye! ***" << endl;
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

Quiz createQuiz() {
  Quiz quiz;
  int questionNum = 1;
  bool repeat = true;
  while (repeat) {
    Question* q = QuestionFactory::create();

    if (q) {
      quiz.add(q);
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
        cout << endl;
        break;
      }
      cout << "[Command not recognized, please try again!]" << endl << endl;
    }
  }
  return quiz;
}
