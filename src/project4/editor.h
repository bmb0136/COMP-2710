#ifndef EDITOR_H
#define EDITOR_H

#include "question_factory.h"
#include "question.h"
#include "quiz.h"
#include "string_util.h"

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
  static void createQuestion(Quiz& quiz) {
    Question* newQuestion;

    cout << "=== QUESTION " << (quiz.size() + 1) << " ===" << endl;
    newQuestion = QuestionFactory::create();

    if (newQuestion) {
      quiz.add(newQuestion);
      cout << "Question saved." << endl;
    } else {
      cout << "Question not saved." << endl;
    }
  }
  static Question* getQuestion(Quiz& quiz, int& number) {
    string input;
    while (true) {
      cout << "Select a question to edit, or type quit() [1-" << quiz.size() << "]: ";
      getline(cin, input);

      if (StringUtils::compareIgnoreCase(input, "quit()")) {
        return nullptr;
      }

      if (!StringUtils::tryParseInt(input, number, 1, quiz.size())) {
        cout << "[That question does not exist!]" << endl;
        continue;
      }

      return quiz.get(number - 1);
    }
  }
  static void editQuestion(Quiz& quiz) {
    if (quiz.size() < 1) {
      cout << "[Please create a question first!]" << endl;
      return;
    }
    int number;
    Question* q = getQuestion(quiz, number);
    if (!q) {
      return;
    }

    Question* replacement = q->edit(number, &QuestionFactory::create);
    if (replacement && q != replacement) {
      quiz.replaceAt(number - 1, replacement);
    }
  }
  static void deleteQuestion(Quiz& quiz) {
    if (quiz.size() < 1) {
      cout << "[Please create a question first!]" << endl;
      return;
    }
    int number;
    if (getQuestion(quiz, number)) {
      quiz.deleteAt(number - 1);
      cout << "Question " << number << " deleted";
    }
  }
public:
  static Quiz createQuiz() {
    Quiz quiz;

    while (true) {
      Action action = getAction();
      cout << endl;

      switch (action) {
        case CREATE:
          createQuestion(quiz);
          cout << endl;
          break;
        case EDIT:
          editQuestion(quiz);
          cout << endl;
          break;
        case DELETE:
          deleteQuestion(quiz);
          cout << endl;
          break;
        case FINISH:
          return quiz;
      }
    }
  }
};

#endif
