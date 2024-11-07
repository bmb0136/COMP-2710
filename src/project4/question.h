#ifndef QUESTION_H
#define QUESTION_H

#include "string_util.h"
#include <iostream>
#include <string>
using namespace std;

enum AnswerResult {
  AR_INVALID,
  AR_CORRECT,
  AR_INCORRECT
};

class Question {
private:
  string prompt;
public:
  Question(string prompt) {
    this->prompt = prompt;
  }
public:
  AnswerResult ask(int questionNumber) {
    cout << "Question " << questionNumber << ": " << prompt << endl << endl;
    cout << prompt << getPromptHint() << ": ";

    bool run = true;
    AnswerResult result;
    while (run) {
      string input;
      cin >> input;
      cout << endl;

      result = checkAnswer(input);

      switch (result) {
        case AR_CORRECT:
          cout << "[Your answer is correct!]" << endl << endl;
          run = false;
          break;
        case AR_INCORRECT:
          cout << "[Your answer is incorrect! The correct answer is " << getAnswer() << "]" << endl << endl;
          run = false;
          break;
        default:
          cout << "[Answer not recognized, please try again!]" << endl << endl;
          break;
      }
    }

    return result;
  }
protected:
  virtual string getPromptHint() = 0;
  virtual string getAnswer() = 0;
  virtual AnswerResult checkAnswer(string answer) = 0;
};

class TFQuestion : public Question {
private:
  bool answer;
public:
  TFQuestion(string prompt, bool answer) : Question(prompt) {
    this->answer = answer;
  }
  AnswerResult checkAnswer(string answer) override {
    bool isTrue = StringUtils::compareIgnoreCase(answer, "t") || StringUtils::compareIgnoreCase(answer, "true");
    bool isFalse = StringUtils::compareIgnoreCase(answer, "f") || StringUtils::compareIgnoreCase(answer, "false");
    if (isTrue) {
      return this->answer ? AR_CORRECT : AR_INCORRECT;
    }
    if (isFalse) {
      return this->answer ? AR_INCORRECT : AR_CORRECT;
    }
    return AR_INVALID;
  }
  string getAnswer() override {
    return this->answer ? "true" : "false";
  }
  string getPromptHint() override {
    return " [true/false]";
  }
};

#endif
