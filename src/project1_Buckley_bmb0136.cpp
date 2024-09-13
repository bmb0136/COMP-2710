// project1_Buckley_bmb0136.cpp
// Author: Brandon Buckley (bmb0136)
//
// Build instructions:
// See the README in https://github.com/bmb0136/COMP-2710
//
// Help used:
// Adding commas to numbers: https://stackoverflow.com/questions/7276826/format-number-with-commas-in-c 
// Padding strings: https://stackoverflow.com/questions/667183/padding-stl-strings-in-c
//
// Usage instructions:
// Enter loan amount, interest rate, and monthly payment.
// If the input is invalid the program will ask again until the input is valid.

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

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

  ColumnSizes sizes = calculateColumnWidths(inputs);

  string line = getAsteriskString(sizes.totalWidth());

  // Print table title
  cout << line << endl;
  // 18 = # of chars in "Amortization table"
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
  cout << "Total interest payed is: $" << interestPayed << endl;

  return 0;
}

static void printTableRow(ColumnSizes sizes, string month, string balance, string payment,
                          string rate, string interest, string principal) {
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
  // If it takes more than 10^9 months to pay off the loan youre cooked
  sizes.month = 9;
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
  stringstream ss;
  for (int i = 0; i < length; i++) {
    ss << "*";
  }
  return ss.str();
}

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

    if (inputs.loanAmount <= 0) {
      cout << "Please enter a positive loan amount" << endl;
      continue;
    }
    break;
  }

  while (true) {
    cout << "Interest Rate (% per year): ";
    cin >> inputs.interestRate;
    inputs.interestRate /= 12.0f; // Convert to % per month

    if (inputs.interestRate <= 0) {
      cout << "Please enter a positive interest rate" << endl;
      continue;
    }
    break;
  }

  while (true) {
    cout << "Monthy Payments: ";
    cin >> inputs.monthlyPayments;

    if (inputs.monthlyPayments <= 0) {
      cout << "Please enter a positive monthly payment" << endl;
      continue;
    }

    float interest = inputs.loanAmount * inputs.interestRate / 100.0f;
    float principal = inputs.monthlyPayments - interest;
    if (principal <= 0) {
      cout << "Please enter a highly monthy payment" << endl;
      continue;
    }
    break;
  }

  return inputs;
}
