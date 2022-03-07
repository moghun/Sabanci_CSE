/*
Account class that handles bank account operations.
*/

#include <iostream>
#include "account_modified.h"
#include <string>
#include <vector>
using namespace std;

Account::Account() {
    owner = "";
	balance = 0;
	iban = "";
}

Account::Account(string ibanCode, string paramOwner) {
    
	owner = paramOwner;
	iban = ibanCode;
}

Account::Account(string ibanCode, string paramOwner, double amount) {
    owner = paramOwner;
	balance = amount;
	iban = ibanCode;
}

Account::Account(const Account &ac) {
    owner = ac.owner;
    iban = ac.iban;
    balance = ac.balance;
}

bool Account::deposit(double amount){
    if (amount <= 0) {
		cout << "Deposit amount could not be less than or equal to zero" << endl;
        return false;
    }
    else {
		balance += amount;
        return true;
    }
}

bool Account::withdraw(double amount){
    if (amount <= 0) {
		cout << "Withdraw amount could not be less than or equal to zero" << endl;
        return false;
    }
	else{
        if (amount <= balance) {
			balance -= amount;
            return true;
        }
        else {
			cout << "There is not enough money to be withdrawn" << endl;
            return false;
        }
	}
}

void Account::displayBalance(){	
	cout << "Account " << iban << " has " << balance << " amount of money" << endl;
}

void Account::displayOwner(){	
	cout << "Account " << iban << " belongs to " << owner << endl;
}

void Account::transfer(Account& a, double amount){
	if (amount <= 0)
		cout << "Transfer amount could not be less than or equal to zero" << endl;
	else{
		if (balance < amount){
			cout << "WARNING: Not enough money in account " << iban << endl;
		}
		else{
			cout << "MESSAGE: Transfer completed" << endl;
			withdraw(amount);
			a.deposit(amount);
		}
	}
}


string Account::getIBAN() const
{
	return iban;
}


double Account::getBalance() const
{
	return balance;
}

void Account::displayAll()
{
	cout << "Account " << iban << " belongs to " << owner << " and has a balance of " << balance << endl;
}