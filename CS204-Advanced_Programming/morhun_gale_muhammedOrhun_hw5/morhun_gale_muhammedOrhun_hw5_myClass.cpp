//Muhammed Orhun Gale - 26754 

#include "morhun_gale_muhammedOrhun_hw5_myClass.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

//TODO: Construct a Wallet object
Wallet::Wallet()
{
	moneyHead = nullptr;
	size = 0;
}
//END:  A Wallet object is constructed with size zero

//TODO: Construct a Wallet object with size "s"
Wallet::Wallet(int s)
{
	size = s;
	moneyHead = new Money[s];
}
//END:  A Wallet object is constructed with size "s"



//TODO: Deep copy constructor
Wallet::Wallet(const Wallet & copy)
{
	size = copy.size;
	moneyHead = new Money[size];

	for(int i = 0; i < size; i++)
	{
		moneyHead[i] = *(copy.moneyHead + i);
	}
}
//END:  Deep copied Wallet is constructed



//TODO: Destructor for Wallet object
Wallet::~Wallet()
{
	size = 0;
	delete [] moneyHead;
}
//END:  Object is destructed and the dynamicaly allocated Money is deleted



//TODO: Return the currency of the given Wallet's "i"th Money
string Wallet::curr(int pos) const
{
	Money* ptr = this->moneyHead;
	ptr = (ptr+pos);
	return ptr->currency;
}
//END:  Currency of "i"th Money is returned



//TODO: Return the amount of the given Wallet's "i"th Money
double Wallet::value(int pos) const
{
	Money* ptr = this->moneyHead;
	return (ptr + pos)->amount;
}
//END:  Amount of "i"th Money is returned




//TODO: Return the size of the Wallet object
int Wallet::getSize() const
{
	return this->size;
}
//END:  Size returned


//TODO: Checks if a currency is exist in a given wallet - if it does, returns the position 
int Wallet::currExist(string currency) const
{
	for(int i = 0; i < this->size; i++)
	{
		if(this->curr(i) == currency)
		{
			return i;
		}
	}
	return -1;
}
//END:  If the currency is exist, the position of it in the wallet is returned
//      Else, -1 is returned




//TODO: Checks the whether the given currency is exist or not - if it does, checks the amount of it is equal or not
bool Wallet::scan(string curr, double val) const
{
	for(int i = 0; i < this->size; i++)
	{
		if(this->curr(i) == curr)
		{
			if(this->value(i) == val)
			{
				return true;
			}

			else{
				return false;
			}
		}
	}
	return false;
}
//END: Given conditions are checked and the boolean value is returned



//TODO: Compare two wallet to find whether they have the same currencies and amounts or not
bool Wallet::equal(const Wallet& rhs) const
{
	if(this->size == rhs.size)
	{
		int counter = 0;
		for(int i = 0; i < this->size; i++)
		{
			bool isEqual = rhs.scan(this->curr(i), this->value(i));
			
			if(isEqual == true)
			{
				counter++;
			}
		}
		if(counter == this->size)
		{
			return true;
		}

		else{
			return false;
		}
	}

	else{
		return false;
	}
}
//END: Given conditions are checked and the boolean value is returned




// Checks a wallet to find if the amount of a currency is greater or equal to the given money's amount
bool Wallet::greater(const Money& rhs) const
{
	string rhsCurr = rhs.currency;
	double rhsVal = rhs.amount;

	int pos = -1;

	for(int i = 0; (i < this->size) && (pos == -1); i++)
	{
		if(this->curr(i) == rhsCurr)
		{
			pos = i;
		}
	}

	if(pos == -1)
	{
		return false;
	}

	else{
		if(this->value(pos) < rhsVal)
		{
			return false;
		}

		else{
			return true;
		}
	}
}
//END: Given conditions are checked and the boolean value is returned




//TODO: Assigns given wallet to the declared wallet as a deep copy 
const Wallet& Wallet::operator= (const Wallet& rhs)
{
	if(this != &rhs)
	{
		delete [] this->moneyHead;
		this->moneyHead = nullptr;
		
		this->size = rhs.size;
		this->moneyHead = new Money[size];

		for(int i = 0; i < size; i++)
		{
			this->moneyHead[i] = rhs.moneyHead[i];
		}
	}
	return *this;
}
//END: Wallet at the RHS is assigned to the LHS wallet



//TODO: Merge a given wallet with the declared wallet and assigns do the assignment
const Wallet& Wallet::operator+= (const Wallet& rhs)
{
	Wallet result(*this);

	for(int i = 0; i < rhs.size; i++)
	{
		int pos = result.currExist(rhs.curr(i));
		
		if(pos != -1)
		{
			result.moneyHead[pos].amount += rhs.value(i);
		}

		else{
			Wallet newWallet(result.size +1);

			Money newMoney(rhs.moneyHead[i].currency, rhs.moneyHead[i].amount);

			(newWallet.moneyHead)[result.size] = newMoney;
			for(int i = 0; i < newWallet.size -1; i++)
			{
				(newWallet.moneyHead)[i] = result.moneyHead[i];
			}

			result = newWallet;
		}
	}
	*this = result;
	return *this;
}
//END:  LHS wallet is merged with RHS and assigned


//TODO: Add a currency to the wallet or increase the money amount of an existing currency and return a new Wallet
Wallet Wallet::operator+ (Money& rhs) const
{
	int pos = this->currExist(rhs.currency);

	if(pos != -1)
	{
		Wallet newWallet(*this);
		newWallet.moneyHead[pos].amount += rhs.amount;
		return newWallet;
	}

	else{
		Wallet newWallet(size +1);
		Money newMoney(rhs.currency, rhs.amount);
		(newWallet.moneyHead)[size] = newMoney;

		for(int i = 0; i < newWallet.size -1; i++)
		{
			(newWallet.moneyHead)[i] = this->moneyHead[i];
		}
		return newWallet;
	}
}
//END:  Currency added if it is not exist in the wallet
//      Amount of the currency is increased if it is exist
//      New Wallet object is returned




//TODO: Merge two wallets and return a new Wallet
Wallet Wallet::operator+ (const Wallet& rhs) const
{
	Wallet result(*this);

	for(int i = 0; i < rhs.size; i++)
	{
		int pos = result.currExist(rhs.curr(i));
		
		if(pos != -1)
		{
			result.moneyHead[pos].amount += rhs.value(i);
		}

		else{
			Wallet newWallet(result.size +1);

			Money newMoney(rhs.moneyHead[i].currency, rhs.moneyHead[i].amount);

			(newWallet.moneyHead)[result.size] = newMoney;
			for(int i = 0; i < newWallet.size -1; i++)
			{
				(newWallet.moneyHead)[i] = result.moneyHead[i];
			}

			result = newWallet;
		}
	}

	return result;
}
//END:  Two wallets are merged and new Wallet is returned






//TODO: Decrease the amount of money of an existing currency. 
//      Available to decrease as much as it includes - Delete if amount is equal to zero
//      Return a new Wallet
Wallet Wallet::operator- (Money& money) const
{
	Wallet result(*this);
	int pos = result.currExist(money.currency);
	
	for(int i = 0; i < result.size; i++)
	{
		if(pos != -1)
		{
			if(result.value(pos) >= money.amount)
			{
				
				if(result.value(pos) == money.amount)
				{
					result.moneyHead[pos].amount -= money.amount;
					Wallet newWallet((result.size) - 1);
					int counter = 0;
					for(int j = 0; j < result.size; j++)
					{
						if(result.value(j) != 0)
						{
							newWallet.moneyHead[counter] = result.moneyHead[j];
							counter++;
						}
					}
					result = newWallet;
					return result;
				}
				else{
					result.moneyHead[pos].amount -= money.amount;
					return result;
				}
			}
			else{
				return result;
			}
		}
		else{
			return result;
		}
	}
	return result;
}
//END:  According to the given Money, if there are enough amount:
//                                     (i)  Amount is decreased
//                                     (ii) If after the extraction amount becomes zero, currency is deleted




//TODO: Ostream operator for the Walelt object
ostream& operator<< (ostream& os, const Wallet & wallet)
{
	ostringstream stream;
	int size = wallet.getSize();
	
	for(int i = 0; i < size; i++)
	{
		if(i != size-1)
		{
			stream << wallet.curr(i) << " " << wallet.value(i) << " - ";
		}

		else{
			stream << wallet.curr(i) << " " << wallet.value(i);
		}
	}

	os << stream.str();
	return os;
}
//END:  Ostream object returned with the Wallet information that is turned into the string


//TODO: Checks two Wallet objects are same or not
bool operator== (const Wallet& wallet1, const Wallet& wallet2)
{
	return wallet1.equal(wallet2);
}
//END:  Conditions checked via the "equal" function and boolean value is returned


//TODO: Compare the amount of a specific currency in a Wallet(LHS) with the given Money(RHS) 
bool operator>= (const Wallet& lhs, const Money& rhs)
{
	return lhs.greater(rhs);
}
//END:  Boolean value of the statement "LHS is greater than the RHS" is returned


//TODO: Compare the amount of a specific currency in a Money(LHS) with the given Wallet(RHS) 
bool operator<= (const Money& lhs, const Wallet& rhs)
{
	return rhs.greater(lhs);
}
//END:  Boolean value of the statement "LHS is smaller than the RHS" is returned

