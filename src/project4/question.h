#ifndef QUESTION_H
#define QUESTION_H

#include "string_util.h"
#include <cstdio>
#include <iostream>
#include <ostream>
#include <sstream>
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
  float points;
public:
  Question(string prompt, float points) {
    this->prompt = prompt;
    this->points = points;
  }
public:
  virtual ~Question() {}
  float getPoints() {
    return points;
  }
  AnswerResult ask(int questionNumber) {
    cout << "Question " << questionNumber << ": " << prompt << endl;
    string subPrompt = getSubprompt();
    if (subPrompt.length() > 0) {
      cout << subPrompt << endl;
    }

    bool run = true;
    AnswerResult result;
    while (run) {
      cout << "Your answer" << getPromptHint() << ": ";
      string input;
      getline(cin, input);

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
          cout << "[Answer not recognized, please try again!]" << endl;
          break;
      }
    }

    return result;
  }
  virtual string getType() = 0;
  string getPrompt() {
    return prompt;
  }
  virtual string getSubprompt() {
    return "";
  }
  Question* edit(int number, Question* (*factory)()) {
    cout << "=== QUESTION " << number << " SAVED VALUES ===" << endl;
    cout << "  1. Type*: " << getType() << endl;
    cout << "  2. Question: " << prompt << endl;
    cout << "  3. Answer: " << getAnswer() << endl;
    bool hasExtra = printExtraEditOption();
    cout << "* Editing question type will replace question" << endl;

    while (true) {
      string input;
      int action;
      while (true) {
        cout << "Select a value to edit, or type quit(): ";
        getline(cin, input);

        if (StringUtils::compareIgnoreCase(input, "quit()")) {
          return this;
        }

        if (StringUtils::tryParseInt(input, action, 1, hasExtra ? 4 : 3)) {
          break;
        }

        cout << "[Option not recognized, please try again!]" << endl;
      }

      Question* replacement;
      switch (action) {
        case 1:
          replacement = factory();
          if (replacement) {
            return replacement->edit(number, factory);
          }
          cout << "Question replacement aborted." << endl;
          break;
        case 2:
          while (true) {
            cout << "Enter new question: ";
            getline(cin, input);
            if (StringUtils::compareIgnoreCase(input, "quit()")) {
              break;
            }
            if (input.length() > 0) {
              prompt = input;
              cout << "Question saved." << endl;
              break;
            }
            cout << "[Please enter a question!]" << endl;
          }
          break;
        case 3:
          if (editAnswer()) {
            cout << "Question saved." << endl;
          }
          break;
        case 4:
          if (hasExtra && editExtraAnswer()) {
            cout << "Question saved." << endl;
          }
          break;
      }
    }
  }
protected:
  virtual bool editAnswer() = 0;
  virtual bool editExtraAnswer() {
    return false;
  }
  virtual bool printExtraEditOption() {
    return false;
  }
  virtual string getPromptHint() {
    return "";
  }
  virtual string getAnswer() = 0;
  virtual AnswerResult checkAnswer(string answer) = 0;
};

class TFQuestion : public Question {
private:
  bool answer;
public:
  TFQuestion(string prompt, bool answer, float points) : Question(prompt, points) {
    this->answer = answer;
  }
  AnswerResult checkAnswer(string answer) override {
    bool parsed;
    if (!StringUtils::tryParseBool(answer, parsed)) {
      return AR_INVALID;
    }
    return parsed == this->answer ? AR_CORRECT : AR_INCORRECT;
  }
  string getAnswer() override {
    return this->answer ? "true" : "false";
  }
  string getPromptHint() override {
    return " [true/false]";
  }
  string getType() override {
    return "tf";
  }
  bool editAnswer() override {
    string input;
    while (true) {
      cout << "Enter new answer [true/false]: ";
      getline(cin, input);
      if (StringUtils::compareIgnoreCase(input, "quit()")) {
        return false;
      }
      bool newAns;
      if (StringUtils::tryParseBool(input, newAns)) {
        answer = newAns;
        return true;
      }
      cout << "[Answer not recognized, please try again!]" << endl;
    }
  } 
};

class WRQuestion : public Question {
private:
  string answer;
public:
  WRQuestion(string prompt, string answer, float points) : Question(prompt, points) {
    this->answer = answer;
  }
  string getAnswer() override {
    return this->answer;
  }
  AnswerResult checkAnswer(string answer) override {
    return StringUtils::compareIgnoreCase(answer, this->answer) ? AR_CORRECT : AR_INCORRECT;
  }
  string getType() override {
    return "wr";
  }
  bool editAnswer() override {
    string input;
    while (true) {
      cout << "Enter new answer: ";
      getline(cin, input);
      if (StringUtils::compareIgnoreCase(input, "quit()")) {
        return false;
      }
      if (input.length() > 0) {
        answer = input;
        return true;
      }
      cout << "[Answer must not be empty!]" << endl;
    }
  }
};

class MCQQuestion : public Question {
private:
  string a, b, c, d, e;
  int answerIndex, numChoices;
public:
  MCQQuestion(string prompt, float points, int answerIndex, int numChoices,
              string a, string b, string c, string d, string e) : Question(prompt, points) {
    this->a = a;
    if (numChoices >= 2) {
      this->b = b;
    }
    if (numChoices >= 3) {
      this->c = c;
    }
    if (numChoices >= 4) {
      this->d = d;
    }
    if (numChoices >= 5) {
      this->e = e;
    }
    this->answerIndex = answerIndex;
    this->numChoices = numChoices;
  }
  string getAnswer() override {
    switch (answerIndex) {
      case 0:
        return "A";
      case 1:
        return "B";
      case 2:
        return "C";
      case 3:
        return "D";
      case 4:
        return "E";
      default:
        return "?";
    }
  }
  AnswerResult checkAnswer(string answer) override {
    if (answer.length() != 1) {
      return AR_INVALID;
    }
    // 4X = uppercase
    // 6X = lowercase
    // Mask out 2 bit to make 6X -> 4X
    int index = (answer[0] & ~0b00100000) - 'A';
    if (index < 0 || index >= numChoices) {
      return AR_INVALID;
    }
    return index == answerIndex ? AR_CORRECT : AR_INCORRECT;
  }
  string getSubprompt() override {
    stringstream ss;
    ss << "  A. " << a << endl;
    if (numChoices >= 2) {
      ss << "  B. " << b << endl;
    }
    if (numChoices >= 3) {
      ss << "  C. " << c << endl;
    }
    if (numChoices >= 4) {
      ss << "  D. " << d << endl;
    }
    if (numChoices >= 5) {
      ss << "  E. " << e << endl;
    }
    return ss.str();
  }
  string getType() override {
    return "mcq";
  }
  bool editAnswer() override {
    cout << "TODO" << endl;
    return false;
  }
  bool printExtraEditOption() override {
    cout << "  4. Answer choices";
    cout << getSubprompt();
    return true;
  }
};

#endif
