// TODO: header
// Build instructions:see the README in https://github.com/bmb0136/COMP-2710
// Help used:
// Adding commas to numbers: https://stackoverflow.com/questions/7276826/format-number-with-commas-in-c 
// Padding strings: https://stackoverflow.com/questions/667183/padding-stl-strings-in-c

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

static string formatNum(float f, string prefix);
static void getUserInput(float* loanAmount, float* interestRate, float* monthlyPayments);
static string getAsteriskString(int length);

int main() {
  float loanAmount, interestRate, monthlyPayments;
  getUserInput(&loanAmount, &interestRate, &monthlyPayments);

  // If it takes more than 10^9 months to pay off the loan youre cooked
  int monthWidth = 9;
  // The balance never increases
  int balanceWidth = max((int)formatNum(loanAmount, "$").length(), 7) + 2;
  // The payment only decreases for the last payment
  int paymentWidth = max((int)formatNum(monthlyPayments, "$").length(), 7) + 2;
  // Rate does not change
  int rateWidth = max((int)formatNum(interestRate, "").length(), 4) + 2;
  // Interest never increases (since balance never increases)
  int interestWidth = max((int)formatNum(loanAmount * interestRate, "$").length(), 8) + 2;
  // Principal never decreases (it will be at most equal to the monthly payments)
  int principalWidth = max((int)formatNum(monthlyPayments, "$").length(), 9);

  int totalWidth = monthWidth + balanceWidth + paymentWidth + rateWidth + interestWidth + principalWidth;
  
  string line = getAsteriskString(totalWidth);
  cout << line << endl;
  cout << right << setw((totalWidth + 18) / 2) << "Amortization Table" << endl;
  cout << line << endl;
  cout << left << setw(monthWidth) << "Month";
  cout << left << setw(balanceWidth) << "Balance";
  cout << left << setw(paymentWidth) << "Payment";
  cout << left << setw(rateWidth) << "Rate";
  cout << left << setw(interestWidth) << "Interest";
  cout << left << "Principal";
  cout << endl;

  cout << left << setw(monthWidth) << 0;
  cout << left << setw(balanceWidth) << formatNum(loanAmount, "$");
  cout << left << setw(paymentWidth) << "N/A";
  cout << left << setw(rateWidth) << "N/A";
  cout << left << setw(interestWidth) << "N/A";
  cout << left << "N/A";
  cout << endl;

  int numMonths = 0;
  float interestPayed = 0;
  while (loanAmount > 0) {
    float interest = loanAmount * interestRate / 100.0f;
    interestPayed += interest;

    // Accounts for last payment
    float payment = min(monthlyPayments, loanAmount + interest);

    float principal = payment - interest;
    loanAmount -= principal;

    numMonths++;

    cout << left << setw(monthWidth) << numMonths;
    cout << left << setw(balanceWidth) << formatNum(loanAmount, "$");
    cout << left << setw(paymentWidth) << formatNum(payment, "$");
    cout << left << setw(rateWidth) << formatNum(interestRate, "");
    cout << left << setw(interestWidth) << formatNum(interest, "$");
    cout << left << formatNum(principal, "$");
    cout << endl;
  }

  cout << line << endl;
  cout << endl;

  cout << "It will take " << numMonths << " months to pay off your loan" << endl;
  cout << "Total interest payed is: $" << interestPayed << endl;

  return 0;
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

static void getUserInput(float* loanAmount, float* interestRate, float* monthlyPayments) {
  while (true) {
    cout << "Loan amount: ";
    cin >> *loanAmount;

    if (*loanAmount <= 0) {
      cout << "Please enter a positive loan amount" << endl;
      continue;
    }
    break;
  }

  while (true) {
    cout << "Interest Rate (% per year): ";
    cin >> *interestRate;
    *interestRate /= 12.0f; // Convert to % per month

    if (*interestRate <= 0) {
      cout << "Please enter a positive interest rate" << endl;
      continue;
    }
    break;
  }

  while (true) {
    cout << "Monthy Payments: ";
    cin >> *monthlyPayments;

    if (*monthlyPayments <= 0) {
      cout << "Please enter a positive monthly payment" << endl;
      continue;
    }

    float interest = *loanAmount * *interestRate / 100.0f;
    if ((*monthlyPayments - interest) <= 0) {
      cout << "Please enter a highly monthy payment" << endl;
      continue;
    }
    break;
  }
}
