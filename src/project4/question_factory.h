#ifndef QUESTION_FACTORY_H
#define QUESTION_FACTORY_H
#include <cmath>
#include <iostream>
#include "question.h"
#include "string_util.h"
using namespace std;

class QuestionFactory {
private:
  enum QuestionType {
    MULTIPLE_CHOICE,
    TRUE_FALSE,
    WRITTEN
  };
  static bool tryGetQuestionType(QuestionType& out) {
    string response;
    int type;
    while (true) {
      response.clear();
      cout << "Type of question [mcq/tf/wr]: ";
      cin >> response;
      if (StringUtils::compareIgnoreCase(response, "quit")) {
        break;
      }
      if (StringUtils::compareIgnoreCase(response, "mcq")) {
        out = MULTIPLE_CHOICE;
        return true;
      }
      if (StringUtils::compareIgnoreCase(response, "tf")) {
        out = TRUE_FALSE;
        return true;
      }
      if (StringUtils::compareIgnoreCase(response, "wr")) {
        out = WRITTEN;
        return true;
      }
      cout << "[Command not recognized, please try again!]" << endl << endl;
    }
    return false;
  }
  static bool tryGetMCQAnswers(int& mcq_numChoices, int& mcq_answer, string& mcq_a, string& mcq_b, string& mcq_c, string& mcq_d, string& mcq_e) {
    cout << "[At any time, type 'quit()' to exit]" << endl << endl;
    while (mcq_numChoices < 5) {
      char letter = (char)(mcq_numChoices + 'A');
      cout << "Enter choice " << letter << ": ";

      string mcq_input;
      cin >> mcq_input;

      if (StringUtils::compareIgnoreCase("quit()", mcq_input)) {
        if (mcq_numChoices < 1) {
          return false;
        } else {
          break;
        }
      }

      switch (mcq_numChoices) {
        case 0:
          mcq_a = mcq_input;
          break;
        case 1:
          mcq_b = mcq_input;
          break;
        case 2:
          mcq_c = mcq_input;
          break;
        case 3:
          mcq_d = mcq_input;
          break;
        case 4:
          mcq_e = mcq_input;
          break;
      }
      mcq_numChoices++;
    }
    cout << endl;

    string ans;
    while (true) {
      cout << "Select correct answer: ";
      cin >> ans;
      int index = ans.length() > 0 ? ans[0] : 0;
      index &= ~0b00100000;
      index -= 'A';
      if (ans.length() == 1 && index >= 0 && index < mcq_numChoices) {
        mcq_answer = index;
        break;
      }
      cout << "[Answer not recognized, please try again!]" << endl << endl;
    }
    cout << endl;

    return true;
  }
public:
  static Question* create() {
    QuestionType type;
    if (!tryGetQuestionType(type)) {
      return nullptr;
    }
    cout << endl;

    string prompt;
    cout << "Enter a question: ";
    cin >> prompt;
    cout << endl;

    bool tf_answer;
    string wr_answer;
    int mcq_answer;
    string mcq_a, mcq_b, mcq_c, mcq_d, mcq_e;
    int mcq_numChoices;


    switch (type) {
      case MULTIPLE_CHOICE:
        if (!tryGetMCQAnswers(mcq_numChoices, mcq_answer, mcq_a, mcq_b, mcq_c, mcq_d, mcq_e)) {
          return nullptr;
        }
        break;
      case TRUE_FALSE:
        while (true) {
          cout << "Select correct answer: ";
          string tf_input;
          cin >> tf_input;
          if (StringUtils::tryParseBool(tf_input, tf_answer)) {
            cout << endl;
            break;
          }
          cout << "[Answer not recognized, please try again!]" << endl << endl;
        }
        break;
      case WRITTEN:
        cout << "Type correct answer: ";
        cin >> wr_answer;
        cout << endl;
        break;
    }

    float points;
    while (true) {
      string pts_input;
      cout << "Enter point value: ";
      cin >> pts_input;
      if (StringUtils::tryParseFloat(pts_input, points, 0, INFINITY) && points != 0) {
        cout << endl;
        break;
      }
      cout << "[Not a point value, please try again!]" << endl << endl;
    }

    switch (type) {
      case MULTIPLE_CHOICE:
        return new MCQQuestion(prompt, points, mcq_answer, mcq_numChoices, mcq_a, mcq_b, mcq_c, mcq_d, mcq_e);
      case TRUE_FALSE:
        return new TFQuestion(prompt, points, tf_answer);
      case WRITTEN:
        return new WRQuestion(prompt, wr_answer, points);
    }
    return nullptr;
  }
};


#endif
