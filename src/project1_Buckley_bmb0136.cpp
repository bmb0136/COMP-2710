// TODO: header

#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  // For printing numbers properly
  cout << fixed << setprecision(2);

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

    if (monthlyPayments < 0) {
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

  cout << "***********************************************************" << endl;
  cout << "        Amortization Table" << endl;
  cout << "***********************************************************" << endl;
  cout << "Month   Balance   Payment      Rate    Interest   Principal" << endl;
  cout << left << setw(8) << 0;
  cout << left << "$" << setw(9) << loanAmount;
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
    cout << left << "$" << setw(9) << loanAmount;
    cout << left << "$" << setw(12) << payment;
    cout << left << setw(8) << interestRate;
    cout << left << "$" << setw(10) << interest;
    cout << left << "$" << principal;
    cout << endl;
  }

  cout << "***********************************************************" << endl;
  cout << endl;

  cout << "It will take " << numMonths << " months to pay off your loan" << endl;
  cout << "Total interest payed is: $" << interestPayed << endl;

  return 0;
}
