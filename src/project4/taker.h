#ifndef TAKER_H
#define TAKER_H

#include "question.h"
#include "quiz.h"
#include "string_util.h"
#include <iostream>

struct _TakerNode {
public:
  Question* question = nullptr;
  Answer* answer = nullptr;
  _TakerNode* next = nullptr;
public:
  void print(int number) {
    cout << "  Question " << number << ": " << question->getAnswer() << endl;
    cout << "  Your answer: " << answer->input << endl;
  }
};

class QuizResult {
private:
  _TakerNode* head = nullptr;
  int count;
public:
  QuizResult(Quiz& q) {
    count = q.size();
    if (count < 1) {
      return;
    }
    _TakerNode* current = new _TakerNode();
    for (int i = 0; i < count; i++) {
      if (!head) {
        head = current;
      }
      current->question = q.get(i);
      if (i < (count - 1)) {
        current->next = new _TakerNode();
        current = current->next;
      }
    }
  }
  _TakerNode* get(int i) {
    if (i < 0 || i >= count) {
      return nullptr;
    }

    _TakerNode* current = head;
    while (i > 0) {
      current = current->next;
      i--;
    }

    return current;
  }
  bool isDone() {
    _TakerNode* n = head;
    while (n) {
      if (!n->answer) {
        return false;
      }
      n = n->next;
    }
    return true;
  }
  void print() {
    float points, total;
    int correct;

    points = total = 0;
    correct = 0;

    _TakerNode* n = head;
    while (n) {
      correct += n->answer->correct ? 1 : 0;
      points += n->answer->pointsGained;
      total += n->question->getPoints();
      n = n->next;
    }

    cout << "Correct answers: " << correct << "/" << count << endl;
    int i = 1;
    n = head;
    while (n) {
      n->print(i++);
      cout << endl;
      n = n->next;
    }
    cout.precision(2);
    cout << "Final score: " << points << "/" << total << endl;
  }
};

class QuizTaker {
public:
  static QuizResult take(Quiz quiz) {
    QuizResult result(quiz);

    int i = 0;
    while (true) {
      _TakerNode* node = result.get(i);

      cout << "On Question " << (i + 1) << ": " << node->question->getPrompt() << endl;
      string sub = node->question->getSubprompt();
      if (sub.length() > 0) {
        cout << sub;
      }
      if (node->answer) {
        cout << "Your answer: " << node->answer->input << endl;
      }
      if (result.isDone()) {
        cout << "All questions answered. ";
      }
      cout << "Do you want to:" << endl;
      cout << "  1. Submit" << endl;
      cout << "  2. Go to next question" << endl;
      cout << "  3. Jump to question" << endl;
      if (node->answer) {
        cout << "  4. Edit this answer" << endl;
      } else {
        cout << "  4. Answer the question" << endl;
      }

      string input;
      int choice;
      while (true) {
        cout << "Select an action: ";
        getline(cin, input);
        if (StringUtils::tryParseInt(input, choice, 1, 4)) {
          break;
        }
        cout << "[Action not recognized, please try again!]" << endl;
      }

      switch (choice) {
        case 1:
          if (!result.isDone()) {
            cout << "[You have not answered all questions!]" << endl;
            break;
          }
          return result;
        case 2:
          if ((i + 1) < quiz.size()) {
            i++;
          } else {
            cout << "[No next question available]" << endl;
          }
          break;
        case 3:
          int newQ;
          while (true) {
            cout << "Jump to question [1-" << quiz.size() << "]: ";
            getline(cin, input);
            if (StringUtils::tryParseInt(input, newQ, 1, quiz.size())) {
              i = newQ - 1;
              break;
            }
            cout << "[Question not recognized, please try again!]" << endl;
          }
          break;
        case 4:
          if (node->answer) {
            Answer* newAns = node->question->ask();
            delete node->answer;
            node->answer = newAns;
          } else {
            node->answer = node->question->ask();
          }
          break;
      }
      cout << endl;
    }
  }
};

#endif
