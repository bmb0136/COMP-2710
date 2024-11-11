#ifndef EDITOR_H
#define EDITOR_H

#include "question_factory.h"
#include "quiz.h"

class QuizEditor {
private:
  enum Action {
    CREATE,
    EDIT,
    DELETE,
    FINISH
  };
  static Action getAction() {
    cout << "Do you want to:" << endl;
    cout << "  1. Create a new question" << endl;
    cout << "  2. Edit a question" << endl;
    cout << "  3. Delete a question" << endl;
    cout << "  4. Finish" << endl;

    string input;
    while (true) {
      cout << "Select an action: ";
      getline(cin, input);
      int num = input.length() >= 1 ? (input[0] - '0') : -1;
      switch (num) {
        case 1:
          return CREATE;
        case 2:
          return EDIT;
        case 3:
          return DELETE;
        case 4:
          return FINISH;
        default:
          cout << "[Action not recognized, please try again!]" << endl;
          break;
      }
    }
  }
public:
  static Quiz createQuiz() {
    Quiz quiz;

    Question* newQuestion;

    while (true) {
      Action action = getAction();
      cout << endl;

      switch (action) {
        case CREATE:
          cout << "=== QUESTION " << (quiz.size() + 1) << " ===" << endl;
          newQuestion = QuestionFactory::create();

          if (newQuestion) {
            quiz.add(newQuestion);
            cout << "Question saved." << endl;
          } else {
            cout << "Question not saved." << endl;
          }

          cout << endl;
          break;
        case EDIT:
          break;
        case DELETE:
          break;
        case FINISH:
          return quiz;
      }
    }
  }
};

#endif
