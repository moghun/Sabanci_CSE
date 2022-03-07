#include <iostream>
#include <string>
#include <fstream>
#include "account_modified.h"
#include <vector>
#include <sstream>
#include "strutils.h"

using namespace std;

struct MoneyTransfer{
	int transID;
	string ibanReciver;
	string ibanSender;
	double amount;
	double tax;
};

void readAccounts( vector<Account> &list)
{
	string filename = "accounts.txt";
	ifstream inFile;
	inFile.open(filename.c_str());
	string line;
	while(getline(inFile,line))
	{
		istringstream input(line);
		string name, lastname, iban, balance;
		input >> name >> lastname >> iban >> balance;
		string owner = name + " " + lastname;
		double dbalance = atof(balance);
		Account user(iban, owner, dbalance);
		list.push_back(user);
	}
	inFile.close();
}


void readTrans( vector<MoneyTransfer> &list)
{
	string filename = "transactions.txt";
	ifstream inFile;
	inFile.open(filename.c_str());
	string line;
	while(getline(inFile,line))
	{
		istringstream input(line);
		string ID, iban1, iban2, sent, cut;
		input >> ID >> iban1 >> iban2 >> sent >> cut;
		MoneyTransfer operation;

		operation.transID = atoi(ID);
		operation.ibanSender = iban1;
		operation.ibanReciver = iban2;
		operation.amount = atof(sent) + atof(cut);
		operation.tax = atof(cut);
		list.push_back(operation);
	}
	inFile.close();
}


void displayAll_accounts(const vector<Account> &list)
{
	int size = list.size();
	for(int i = 0; i < size; i++)
	{
		Account info = list[i];
		info.displayAll();
	}
}


void displayAll_trans(const vector<MoneyTransfer> &list)
{
	int size = list.size();
	for(int i = 0; i < size; i++)
	{
		MoneyTransfer operation;
		operation = list[i];
		cout << "Transaction #" << operation.transID << ": " << operation.ibanSender << " ==> " << operation.amount << " ==> " << operation.ibanReciver << ", tax deducted: " << operation.tax << endl;
	}

}


void sortAccounts(vector<Account> &list)
{
	for(unsigned int k = 0; k < list.size() -1; k++)
	{
		int maxIndex = k;
		double maxAmount = list[k].getBalance(); 
		for(unsigned int j = k+1; j < list.size(); j++)
		{
			double currentAmount = list[j].getBalance();
			if(maxAmount < currentAmount)
			{
				maxIndex = j;
				maxAmount = currentAmount;
			}
		}
		Account temp;
		temp = list[k];
		list[k] = list[maxIndex];
		list[maxIndex] = temp;
	}
}


void sortTrans(vector<MoneyTransfer> &list)
{
	for(unsigned int k = 0; k < list.size() -1; k++)
	{
		int maxIndex = k;
		double maxAmount = list[k].amount; 
		for(unsigned int j = k+1; j < list.size(); j++)
		{
			double currentAmount = list[j].amount;
			if(maxAmount < currentAmount)
			{
				maxIndex = j;
				maxAmount = currentAmount;
			}
		}
		MoneyTransfer temp;
		temp = list[k];
		list[k] = list[maxIndex];
		list[maxIndex] = temp;
	}
}


int searchAccount(vector<Account> &list, string iban)
{
	for(unsigned int i = 0; i < list.size(); i++)
	{
		if(list[i].getIBAN() == iban)
		{
			return i;
		}
	}
	return -1;
}

void removeAccount(vector<Account> &list, int idx)
{
	for(unsigned int k = idx; k < list.size()-1; k++)
	{
		list[k] = list[k+1];
	}
	list.pop_back();
}

int removeTrans(vector<MoneyTransfer> &list, int ID)
{

	for(unsigned int i = 0; i < list.size()-1; i++)
	{

		if(list[i].transID	== ID)
		{
			for(unsigned int k = i; k < list.size()-1; k++)
			{
				list[k] = list[k+1];
			}
			list.pop_back();
			return 1;
		}
	}
	return -1;
}

int searchTrans(vector<MoneyTransfer> &list, int ID)
{

	for(unsigned int i = 0; i < list.size(); i++)
	{
		if(list[i].transID == ID)
		{
			return i;
		}
	}
	return -1;
}

void handleTrans(vector<Account> &list, vector<MoneyTransfer> &list2, int ID)
{
	int transIdx = searchTrans(list2, ID);

	if(transIdx == -1)
	{
		cout << "Transaction #"<< ID << " NOT FOUND" << endl << endl;
	}

	else
	{
		
		string iban1;
		string iban2;
		iban1 = list2[transIdx].ibanSender;
		iban2 = list2[transIdx].ibanReciver;

		int ibanCheck1;
		ibanCheck1 = searchAccount(list, iban1);
		int ibanCheck2;
		ibanCheck2 = searchAccount(list, iban2);

		if(ibanCheck1 == -1)
		{
			cout << "ERROR: The sender account has been deleted, can't reverse transaction" << endl << endl;
		}

		else if(ibanCheck2 == -1)
		{
			cout << "ERROR: The receiver account has been deleted, can't reverse transaction" << endl << endl;
		}
				
		else
		{
			Account temp1 = list[ibanCheck1];
			Account temp2 = list[ibanCheck2];
			MoneyTransfer trans = list2[transIdx];

			if(temp2.getBalance() >= trans.amount)
			{
				double hreversal = trans.amount;
				double reversal = hreversal - trans.tax;
				double fee = (reversal*5)/100;
				temp1.deposit(reversal-fee);
				temp2.withdraw(reversal-fee);
				list[ibanCheck1] = temp1;
				list[ibanCheck2] = temp2;
				int logic = removeTrans(list2, ID);
				cout << "MESSAGE: Transfer completed" << endl;
				cout << "Transaction #" << ID << " reversed" << endl;
				cout << "From " << reversal << " a reversal fee of " << fee << " has been deducted" << endl;
				cout << iban2 << " ==> " << (reversal - fee) << " ==> " << iban1  << endl;
				if(logic == 1)
				{
					cout << "Transaction #"<< ID << " reversed and deleted" << endl << endl;
				}
			}
			else{
				cout << "ERROR: The receiver account does not have enough funds, can't reverse transaction" << endl << endl;
			}
		}
	}
}


bool isOP(string op)
{
	for(unsigned int i = 0; (i < op.length()); i++)
	{
		char ch = op.at(i);
		if(ch > '7' || ch < '1')
		{
			return false;
		}
	}
	int num = atoi(op);

	if (num > 7 || num < 1){
		return false;
	}
	return true;
} 

int menu(string op)
{
	bool control = isOP(op);
	
	while(control == false)
	{
		string newOp;
		cout << "ERROR: \"" << op << "\" INVALID CHOICE!" << endl << endl;
		cout << "Please select your action:" << endl << "1. Print accounts" << endl << "2. Print transactions" << endl << "3. Order accounts by balance (descending)" << endl << "4. Order transactions by amount (descending)" << endl << "5. Delete account" << endl << "6. Delete transaction"<< endl <<"7. Exit program" << endl << "Enter your choice: ";
		cin >> newOp;
		op = newOp;
		control = isOP(newOp);
	}

	int selection = atoi(op);
	return selection;
}

int tidControl(string op)
{
	for(unsigned int i = 0; (i < op.length()); i++)
	{
		char ch = op.at(i);
		if((ch > '9' || ch < '0') && ch != '-')
		{
			return 2;
		}
	}
	if(atoi(op) < 0)
	{
		return 3;
	}
	else if(atoi(op) == 0)
	{
		return 2;
	}
	return 1;
} 

int main()
{
	cout << "Welcome to CS201 Banking Application!" << endl << endl;
	vector<Account> accounts;
	readAccounts(accounts);
	cout << "Accounts are read from file" << endl; 
	vector<MoneyTransfer> operations;
	readTrans(operations);
	cout << "Transactions are read from file" << endl << endl;
	
	string op;
	bool logic = true;

	while(logic == true)
	{
		cout << "Please select your action:" << endl << "1. Print accounts" << endl << "2. Print transactions" << endl << "3. Order accounts by balance (descending)" << endl << "4. Order transactions by amount (descending)" << endl << "5. Delete account" << endl << "6. Delete transaction"<< endl <<"7. Exit program" << endl << "Enter your choice: ";
		cin >> op;
		int selected = menu(op);
		if(selected == 7)
		{
			cout << endl << "Ending program" << endl;
			logic = false;
		}
		else
		{
			if(selected == 1)
			{
				cout << endl;
				displayAll_accounts(accounts);
				cout << endl;
			}
			else if(selected == 2)
			{
				cout << endl;
				displayAll_trans(operations);
				cout << endl;
			}
			else if(selected == 3)
			{
				sortAccounts(accounts);
				cout << endl << "Accounts are now sorted" << endl << endl;
			}
			else if(selected == 4)
			{
				sortTrans(operations);
				cout << endl << "Transactions are now sorted" << endl << endl;

			}
			else if(selected == 5)
			{
				string iban;
				cout << endl << "Please enter IBAN number: ";
				cin >> iban;
				int idx = searchAccount(accounts, iban);
				if(idx == -1)
				{
					ToUpper(iban);
					cout << "IBAN " << iban << " NOT FOUND" << endl << endl;
				}
				else{
					removeAccount(accounts, idx);
					cout << "IBAN " << iban << " found and deleted" << endl << endl;
				}

			}
			else if(selected == 6)
			{
				string TID;
				do{

					cout << endl;
					cout << "Please enter transaction ID: ";
					cin >> TID;
					int control = tidControl(TID);
					if( control == 1)
					{
						int TIDn = atoi(TID);
						handleTrans(accounts, operations, TIDn);
					}

					else if( control == 2)
					{
						cout << "ERROR: \""<< TID <<"\" INVALID VALUE!" << endl;

					}
					else if( control == 3)
					{
						cout << "ERROR: TID CAN'T BE NEGATIVE" << endl;
					}
				}while(tidControl(TID) != 1);
			}
		}
	}

	return 0;
}