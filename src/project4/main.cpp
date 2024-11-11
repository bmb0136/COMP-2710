#include "editor.h"
#include "question.h"
#include "quiz.h"
#include "taker.h"
#include <iostream>

using namespace std;

#define UNIT_TESTING

#ifdef UNIT_TESTING
#include <cassert>

// Tests Quiz manipulation methods to not crash
void testQuiz() {
  Quiz q;
  
  cout << "Case 1: Quiz.get invalid index returns null" << endl; 
  assert(q.get(-1) == nullptr);
  assert(q.get(0) == nullptr);
  assert(q.get(1) == nullptr);

  cout << "Case 2: Quiz.add once can be .get and updates .size" << endl;
  q.add(new WRQuestion("prompt", "answer", 1.0f));
  assert(q.size() == 1);
  assert(q.get(0)->getAnswer() == "answer");

  cout << "Case 3: Quiz.replaceAt replaces" << endl;
  q.replaceAt(0, new TFQuestion("prompt", false, 6.9f));
  assert(q.size() == 1);
  assert(q.get(0)->getAnswer() == "false");

  cout << "Case 4: Quiz.totalPoints" << endl;
  assert(q.totalPoints() == 6.9f);

  cout << "Case 5: Quiz.delete updates size and removes item" << endl;
  q.deleteAt(0);
  assert(q.size() == 0);
  assert(q.get(0) == nullptr);
}

// Tests Question subclasses .checkAnswer()
void testQuestion() {
  cout << "Case 1: WR Question answer validation" << endl;
  WRQuestion wr("prompt", "answer", 6.9f);
  assert(AR_CORRECT == wr.checkAnswer("answer"));
  assert(AR_INCORRECT == wr.checkAnswer("wrong"));

  cout << "Case 2: TF Question answer validation" << endl;
  TFQuestion tf("prompt", true, 13.37f);
  assert(AR_CORRECT == tf.checkAnswer("t"));
  assert(AR_CORRECT == tf.checkAnswer("true"));
  assert(AR_INCORRECT == tf.checkAnswer("f"));
  assert(AR_INCORRECT == tf.checkAnswer("false"));
  assert(AR_INVALID == tf.checkAnswer("ur mom"));

  cout << "Case 3: MCQ Question answer validation" << endl;
  MCQQuestion mcq("prompt", 6.9f, 0, 2, "deez", "nuts", "", "", "");
  assert(AR_CORRECT == mcq.checkAnswer("A"));
  assert(AR_INCORRECT == mcq.checkAnswer("b"));
  assert(AR_INVALID == mcq.checkAnswer("C"));
}

int main() {
  cout << "*** This is the debug version ***" << endl << endl;
  
  testQuiz();
  cout << endl;
  
  testQuestion();
  cout << endl;

  cout << "*** End of the debug version ***" << endl << endl;
  return 0;
}
#else

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
#endif
