#include "morhun_gale_muhammedOrhun_hw5_myClass.h"
#include <iostream>
#include <string>

using namespace std;

//This program does not perform something meaningful. It just uses the operators and class that you will implement.
//Do not change anything other than adding include(s) above.


void display(const Wallet& w)
{
	cout << w << "\n\n";
}

Wallet readWallet()
{
	Wallet res;
	Money t;
	cout << "Please enter the name of the currency and amount to put it to myWallet3 (to stop enter ctrl+z on an empty line):\n";
	while (cin >> t.currency >> t.amount)
	{
		res = res + t;
		cout << "Please enter the name of the currency and amount to put it to myWallet3 (to stop enter ctrl+z on an empty line):\n";
	}
	cout << "\n";
	cin.clear();

	return res;
}

void foo(const Wallet & w)//if you receive no operator matches ... errors in this function, read the life-saving advice in the homework document
{
	Money t;
	t.currency = "USD"; t.amount = 33.2;
	Wallet localWallet = w + w;
	localWallet = w + t;
	localWallet = w - t;
}

int main()
{
	Wallet myWallet;
	Money t;
	cout << "Please enter the name of the currency and amount to put it to myWallet (to stop enter ctrl+z on an empty line):\n";
	while (cin >> t.currency >> t.amount)
	{
		myWallet = myWallet + t;
		cout << "Please enter the name of the currency and amount to put it to myWallet (to stop enter ctrl+z on an empty line):\n";
	}

	cin.clear();
	myWallet = myWallet;
	cout << "\nCurrent myWallet after input and self assignment:\n";
	display(myWallet);
	foo(myWallet);

	Wallet myWallet2(myWallet);
	cout << "Current myWallet2 after copy constructor:\n";
	display(myWallet2);
	

	cout << "What do you want to spend from myWallet?: "; 
	cin >> t.currency >> t.amount;
	myWallet = myWallet - t; 

	cout << "\nCurrent myWallet after spending:\n";
	cout << myWallet << "\n\n";;
	cout << "Current myWallet2 after spending:\n";
	cout << myWallet2 << "\n\n";;

	if (myWallet == myWallet2)
		cout << "myWallet and myWallet2 are exactly the same\n";
	else
		cout << "myWallet and myWallet2 are not the same\n";

	Wallet myWallet3;
	cout << "\nEmpty myWallet3:\n";
	cout << myWallet3 << "\n";;

	myWallet3 = readWallet();

	cout << "Current myWallet3 after reading:\n";
	cout << myWallet3 << "\n\n";;

	if (myWallet == myWallet3)
		cout << "myWallet and myWallet3 are exactly the same\n";
	else
		cout << "myWallet and myWallet3 are not the same\n";
	cout << "\n";

	t.currency = "HBAR";
	t.amount = 251;

	if (myWallet >= t) 
		cout << "myWallet has more than 250 HBAR\n";
	else
		cout << "myWallet does not have more than 250 HBAR\n";
	
	if (t <= myWallet3)
		cout << "myWallet3 has more than 250 HBAR\n";
	else
		cout << "myWallet3 does not have more than 250 HBAR\n";

	myWallet3 = myWallet3 + myWallet;

	cout << "\nCurrent myWallet3 after myWallet3 = myWallet3 + myWallet:\n";
	cout << myWallet3 << "\n\n";;

	Wallet myWallet4;
	myWallet4 = myWallet4 + myWallet4;
	myWallet4 += myWallet4;
	myWallet4 = myWallet + myWallet2 + myWallet3;

	cout << "Current myWallet4 after myWallet4 = myWallet + myWallet2 + myWallet3:\n";
	cout << myWallet4 << "\n\n";;

	myWallet = myWallet2 = myWallet3 += myWallet2;
	cout << "After myWallet = myWallet2 = myWallet3 += myWallet2";
	cout << "\nCurrent myWallet:\n";
	cout << myWallet << "\n\n";;
	cout << "Current myWallet2:\n";
	cout << myWallet2 << "\n\n";;
	cout << "Current myWallet3:\n";
	cout << myWallet3 << "\n";;

	return 0;
}
