// project1_Buckley_bmb0136.cpp
// Author: Brandon Buckley (bmb0136)
//
// Build instructions:
// See the README in https://github.com/bmb0136/COMP-2710
//
// Help used:
// (1) Adding commas to numbers: https://stackoverflow.com/questions/7276826/format-number-with-commas-in-c 
// (2) Padding strings: https://stackoverflow.com/questions/667183/padding-stl-strings-in-c
// (3) std::cin with invalid inputs: https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
//
// Usage instructions:
// Enter loan amount, interest rate, and monthly payment.
// If the input is invalid the program will ask again until the input is valid.

#include <iostream>
#include <iomanip>

using namespace std;

struct UserInput {
public:
  float loanAmount, interestRate, monthlyPayments;
};

struct ColumnSizes {
public:
  int month, balance, payment, rate, interest, principal;
  int totalWidth() {
    return month + balance + payment + rate + interest + principal;
  }
};

static string formatNum(float f, string prefix);
static UserInput getUserInput();
static string getAsteriskString(int length);
static ColumnSizes calculateColumnWidths(UserInput inputs);
static void printTableRow(ColumnSizes sizes, string month, string balance, string payment,
                          string rate, string interest, string principal);

int main() {
  UserInput inputs = getUserInput();
  cout << endl; // Add extra line

  ColumnSizes sizes = calculateColumnWidths(inputs);

  string line = getAsteriskString(sizes.totalWidth());

  // Print table title
  cout << line << endl;
  // 18 = # of chars in "Amortization table"
  // right and setw from Source (2)
  cout << right << setw((sizes.totalWidth() + 18) / 2) << "Amortization Table" << endl;
  cout << line << endl;

  // Print header names
  printTableRow(sizes, "Month", "Balance", "Payment", "Rate", "Interest", "Principal");

  // Make a copy instead of modifying the field in inputs directly
  float balance = inputs.loanAmount;

  // Print hardcoded first row
  printTableRow(sizes, "0", formatNum(balance, "$"), "N/A", "N/A", "N/A", "N/A");

  // Print the rest of thr rows
  int numMonths = 0;
  float interestPayed = 0;
  while (balance > 0) {
    // Interest rate is in %, convert to 0-1 range
    float interest = balance * inputs.interestRate / 100.0f;
    interestPayed += interest;

    // Accounts for last payment
    float payment = min(inputs.monthlyPayments, balance + interest);

    float principal = payment - interest;
    balance -= principal;

    // Increment before so that the output is correct.
    // This is because we already printed the first row.
    numMonths++;

    printTableRow(sizes, to_string(numMonths), formatNum(balance, "$"),
                  formatNum(payment, "$"), formatNum(inputs.interestRate, "$"),
                  formatNum(interest, "$"), formatNum(principal, "$"));
  }

  // Print end line
  cout << line << endl;
  cout << endl;

  // Final output
  cout << "It will take " << numMonths << " months to pay off your loan" << endl;
  cout << "Total interest payed is: " << formatNum(interestPayed, "$") << endl;

  return 0;
}

static void printTableRow(ColumnSizes sizes, string month, string balance, string payment,
                          string rate, string interest, string principal) {
  // left and setw from Source (2)
  cout << left << setw(sizes.month) << month;
  cout << left << setw(sizes.balance) << balance;
  cout << left << setw(sizes.payment) << payment;
  cout << left << setw(sizes.rate) << rate;
  cout << left << setw(sizes.interest) << interest;
  cout << left << setw(sizes.principal) << principal;
  cout << endl;
}

static ColumnSizes calculateColumnWidths(UserInput inputs) {
  ColumnSizes sizes;

  // Calculate number of months it will take
  // The only other way to do this would be solving a recurrence relation, then solving that for 0
  // IDK how to do the former half of that.
  // I could just ask WolframAlpha, but this is way easier.
  int maxMonths = 0;
  float tempBalance = inputs.loanAmount;
  while (tempBalance > 0) {
    tempBalance -= inputs.monthlyPayments - (tempBalance * inputs.interestRate / 100.0);
    maxMonths++;
  }

  sizes.month = max((int)formatNum(maxMonths, "").length(), 5) + 2;
  // The balance never increases
  sizes.balance = max((int)formatNum(inputs.loanAmount, "$").length(), 7) + 2;
  // The payment only decreases for the last payment
  sizes.payment = max((int)formatNum(inputs.monthlyPayments, "$").length(), 7) + 2;
  // Rate does not change
  sizes.rate = max((int)formatNum(inputs.interestRate, "$").length(), 4) + 2;
  // Interest never increases (since balance never increases)
  sizes.interest = max((int)formatNum(inputs.loanAmount * inputs.interestRate / 100.0, "$").length(), 8) + 2;
  // Principal never decreases (it will be at most equal to the monthly payments)
  sizes.principal = max((int)formatNum(inputs.monthlyPayments, "$").length(), 9);

  return sizes;
}

static string getAsteriskString(int length) {
  // The use of stringstream here was inspired by Source (1)
  stringstream ss;
  for (int i = 0; i < length; i++) {
    ss << "*";
  }
  return ss.str();
}

// Modified from Source (1)
static string formatNum(float f, string prefix) {
  stringstream ss;
  ss.imbue(locale(""));
  ss << prefix;
  ss << fixed << setprecision(2) << f;
  return ss.str();
}

static UserInput getUserInput() {
  UserInput inputs;

  while (true) {
    cout << "Loan amount: ";
    cin >> inputs.loanAmount;
    // These two lines are based on Source (3)
    cin.clear();
    cin.ignore(999999, '\n');

    if (inputs.loanAmount <= 0) {
      cout << "\x1b[31mPlease enter a positive loan amount\x1b[0m" << endl;
      continue;
    }
    break;
  }

  while (true) {
    cout << "Interest Rate (% per year): ";
    cin >> inputs.interestRate;
    // These two lines are based on Source (3)
    cin.clear();
    cin.ignore(999999, '\n');

    inputs.interestRate /= 12.0f; // Convert to % per month

    if (inputs.interestRate <= 0) {
      cout << "\x1b[31mPlease enter a positive interest rate\x1b[0m" << endl;
      continue;
    }
    break;
  }

  while (true) {
    cout << "Monthy Payments: ";
    cin >> inputs.monthlyPayments;
    // These two lines are based on Source (3)
    cin.clear();
    cin.ignore(999999, '\n');

    if (inputs.monthlyPayments <= 0) {
      cout << "\x1b[31mPlease enter a positive monthly payment\x1b[0m" << endl;
      continue;
    }

    float interest = inputs.loanAmount * inputs.interestRate / 100.0f;
    float principal = inputs.monthlyPayments - interest;
    if (principal <= 0) {
      cout << "\x1b[31mPlease enter a higher monthy payment\x1b[0m" << endl;
      continue;
    }
    break;
  }

  return inputs;
}
