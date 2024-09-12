// project1_Buckley_bmb0136.cpp
// Author: Brandon Buckley (bmb0136)
//
// Build instructions: see the README in https://github.com/bmb0136/COMP-2710
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

using namespace std;

struct UserInput {
public:
  float loanAmount, interestRate, monthlyPayments;
};

static string formatNum(float f, string prefix);
static UserInput getUserInput();
static string getAsteriskString(int length);
static int calculateColumnWidths(float loanAmount, float interestRate, float monthlyPayments,
                                 int* monthWidth, int* balanceWidth, int* paymentWidth, int* rateWidth,
                                 int* interestWidth);

int main() {
  UserInput inputs = getUserInput();

  int monthWidth, balanceWidth, paymentWidth, rateWidth, interestWidth;
  int totalWidth = calculateColumnWidths(inputs.loanAmount, inputs.interestRate, inputs.monthlyPayments,
                                         &monthWidth, &balanceWidth, &paymentWidth,
                                         &rateWidth, &interestWidth);

  // Print table title
  string line = getAsteriskString(totalWidth);
  cout << line << endl;
  cout << right << setw((totalWidth + 18) / 2) << "Amortization Table" << endl;
  cout << line << endl;

  // Print header names
  cout << left << setw(monthWidth) << "Month";
  cout << left << setw(balanceWidth) << "Balance";
  cout << left << setw(paymentWidth) << "Payment";
  cout << left << setw(rateWidth) << "Rate";
  cout << left << setw(interestWidth) << "Interest";
  cout << left << "Principal";
  cout << endl;

  float balance = inputs.loanAmount;

  // Print first row
  cout << left << setw(monthWidth) << 0;
  cout << left << setw(balanceWidth) << formatNum(balance, "$");
  cout << left << setw(paymentWidth) << "N/A";
  cout << left << setw(rateWidth) << "N/A";
  cout << left << setw(interestWidth) << "N/A";
  cout << left << "N/A";
  cout << endl;

  int numMonths = 0;
  float interestPayed = 0;
  while (balance > 0) {
    float interest = balance * inputs.interestRate / 100.0f;
    interestPayed += interest;

    // Accounts for last payment
    float payment = min(inputs.monthlyPayments, balance + interest);

    float principal = payment - interest;
    balance -= principal;

    // Increment before so that the output is correct.
    // This is because we already printed the first row.
    numMonths++;

    cout << left << setw(monthWidth) << numMonths;
    cout << left << setw(balanceWidth) << formatNum(balance, "$");
    cout << left << setw(paymentWidth) << formatNum(payment, "$");
    cout << left << setw(rateWidth) << formatNum(inputs.interestRate, "");
    cout << left << setw(interestWidth) << formatNum(interest, "$");
    cout << left << formatNum(principal, "$");
    cout << endl;
  }

  // Print end line
  cout << line << endl;
  cout << endl;

  // Final output
  cout << "It will take " << numMonths << " months to pay off your loan" << endl;
  cout << "Total interest payed is: $" << interestPayed << endl;

  return 0;
}


static int calculateColumnWidths(float loanAmount, float interestRate, float monthlyPayments,
                                 int* monthWidth, int* balanceWidth, int* paymentWidth, int* rateWidth,
                                 int* interestWidth) {
  // If it takes more than 10^9 months to pay off the loan youre cooked
  *monthWidth = 9;
  // The balance never increases
  *balanceWidth = max((int)formatNum(loanAmount, "$").length(), 7) + 2;
  // The payment only decreases for the last payment
  *paymentWidth = max((int)formatNum(monthlyPayments, "$").length(), 7) + 2;
  // Rate does not change
  *rateWidth = max((int)formatNum(interestRate, "").length(), 4) + 2;
  // Interest never increases (since balance never increases)
  *interestWidth = max((int)formatNum(loanAmount * interestRate, "$").length(), 8) + 2;
  // Principal never decreases (it will be at most equal to the monthly payments)
  int principalWidth = max((int)formatNum(monthlyPayments, "$").length(), 9);

  return *monthWidth + *balanceWidth + *paymentWidth + *rateWidth + *interestWidth + principalWidth;
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
    if ((inputs.monthlyPayments - interest) <= 0) {
      cout << "Please enter a highly monthy payment" << endl;
      continue;
    }
    break;
  }
  
  return inputs;
}
