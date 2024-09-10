// TODO: header
// Build instructions:see the README in https://github.com/bmb0136/COMP-2710
// Help used:
// Adding commas to numbers: https://stackoverflow.com/questions/7276826/format-number-with-commas-in-c 
// Padding strings: https://stackoverflow.com/questions/667183/padding-stl-strings-in-c

#include <iostream>
#include <iomanip>

using namespace std;

static string formatNum(float f, string prefix) {
  stringstream ss;
  ss.imbue(locale(""));
  ss << prefix;
  ss << fixed << setprecision(2) << f;
  return ss.str();
}

int main() {
  float loanAmount;
  while (true) {
    cout << "Loan amount: ";
    cin >> loanAmount;

    if (loanAmount <= 0) {
      cout << "Please enter a positive loan amount" << endl;
      continue;
    }
    break;
  }

  float interestRate;
  while (true) {
    cout << "Interest Rate (% per year): ";
    cin >> interestRate;
    interestRate /= 12.0f; // Convert to % per month

    if (interestRate <= 0) {
      cout << "Please enter a positive interest rate" << endl;
      continue;
    }
    break;
  }

  float monthlyPayments;
  while (true) {
    cout << "Monthy Payments: ";
    cin >> monthlyPayments;

    if (monthlyPayments <= 0) {
      cout << "Please enter a positive monthly payment" << endl;
      continue;
    }

    float interest = loanAmount * interestRate / 100.0f;
    if ((monthlyPayments - interest) <= 0) {
      cout << "Please enter a highly monthy payment" << endl;
      continue;
    }
    break;
  }

  cout << "************************************************************" << endl;
  cout << "        Amortization Table" << endl;
  cout << "************************************************************" << endl;
  cout << "Month   Balance    Payment      Rate    Interest   Principal" << endl;
  cout << left << setw(8) << 0;
  cout << left << setw(11) << formatNum(loanAmount, "$");
  cout << left << setw(13) << "N/A";
  cout << left << setw(8) << "N/A";
  cout << left << setw(11) << "N/A";
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

    cout << left << setw(8) << numMonths;
    cout << left << setw(11) << formatNum(loanAmount, "$");
    cout << left << setw(13) << formatNum(payment, "$");
    cout << left << setw(8) << formatNum(interestRate, "");
    cout << left << setw(11) << formatNum(interest, "$");
    cout << left << formatNum(principal, "$");
    cout << endl;
  }

  cout << "************************************************************" << endl;
  cout << endl;

  cout << "It will take " << numMonths << " months to pay off your loan" << endl;
  cout << "Total interest payed is: $" << interestPayed << endl;

  return 0;
}
