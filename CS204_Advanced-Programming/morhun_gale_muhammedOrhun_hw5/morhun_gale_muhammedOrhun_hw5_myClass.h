//Muhammed Orhun Gale - 26754 

//Function descriptions are in the CPP file

#ifndef _WALLET_H
#define _WALLET_H

#include <string>
#include <iostream>

using namespace std;

struct Money
{
	string currency;
	double amount;


	Money::Money(const string &curr = "", const double &val = 0) //Default constructor which can take parameters
	{
		currency = curr;
		amount = val;
	}
};


class Wallet
{
public:
	Wallet();  //Constructor
	Wallet(const int); //Constructor w/ size parameter that constructs a wallet with given amount of money objects 
	~Wallet(); //Destructor
	Wallet(const Wallet &); //Copy Constructor

	const Wallet& operator= (const Wallet&); // Overloaded assignment operator for Wallet class
	const Wallet& operator+= (const Wallet&); // Overloaded assigning summation operator for Wallet class - Merges two wallets
	Wallet operator+ (const Wallet&) const; // Overloaded summation operator (Wallet + Wallet) for Wallet class - Merge two wallets & returns new Wallet
	Wallet operator+ (Money&) const; // Overloaded summation operator (Wallet + Money) for Wallet class - Adds new currency/increase amount & returns new Wallet
	Wallet operator- (Money&) const; //Overloaded extraction operator (Wallet - Money) for Wallet class - Decrease amount of a currency/delete it & returns new Wallet


	string curr(int) const; // Returns the currency of a Money
	double value(int) const; // Returns the amount of a Money
	int getSize() const; // Returns the size of a wallet object
	int currExist(string) const; // Checks if a currency is exist in a given wallet
	bool scan(string, double) const; // Checks the whether the given currency is exist or not
	bool greater(const Money&) const; // Checks a wallet to find if the amount of a currency is greater or equal to the given money's amount
	bool equal(const Wallet&) const; //Compare two wallet to find whether they have the same currencies and amounts or not


private:
	Money* moneyHead;
	int size;
};

ostream& operator<< (ostream&, const Wallet &); // Ostream for the Wallet object
bool operator== (const Wallet&, const Wallet&); // Returns whether two wallet is equal or not
bool operator>= (const Wallet&, const Money&); // Compares the amount of given Money and the currency's amount in the Wallet
bool operator<= (const Money&, const Wallet&); // Compares the amount of given Money and the currency's amount in the Wallet

#endif