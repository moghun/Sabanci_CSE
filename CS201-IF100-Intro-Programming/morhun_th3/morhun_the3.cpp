#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"
#include <climits>
#include <cfloat>

using namespace std;

bool isOP(string op)
{
	for(int i = 0; (i < op.length()); i++)
	{
		char ch = op.at(i);
		if(ch > '6' || ch < '1')
		{
			return false;
		}
	}
	int num = atoi(op);

	if (num > 6 || num < 1){
		return false;
	}
	return true;
} 
//checker for menu selection input

int menu(string op)
{
	bool control = isOP(op);
	
	while(control == false)
	{
		string newOp;
		cout << "ERROR: \"" << op << "\" INVALID CHOICE!" << endl << endl;
		cout << "Please select your action:" << endl << "1. Create transaction" << endl << "2. Search transaction" << endl << "3. Show biggest transaction" << endl << "4. Show smallest transaction" << endl << "5. Show transaction stats" << endl << "6. Exit program" << endl << "Enter your choice: ";
		cin >> newOp;
		op = newOp;
		control = isOP(newOp);
	}

	int selection = atoi(op);
	return selection;

}
//main screen

bool digitCheck(string inp)
{
	int l1 = inp.length();
	bool logic = true;

	for (int i = 2; i < l1; i++) {
		char ch = inp.at(i);
		if (ch < '0' || ch > '9')
		{
			logic = false;
		}
	}
	return logic;
}

int countryCheck(string inp1, string inp2) //return= 0 valid, 1 not valid country code, 2 not the same country codes
{
	string cc1 = inp1.substr(0,2);
	string cc2 = inp2.substr(0,2);

	ToLower(cc1);
	ToLower(cc2);

	int pick = 0; 

	if(cc1 != "tr" && cc1 != "dz" && cc1 != "is") {

		pick = 1;
		return pick;
	}

	else if (cc2 != "tr" && cc2 != "dz" && cc2 != "is") {

		pick = 1;
		return pick;
	}
	
	else if(cc1 == cc2)
	{
		pick = 2;
		return pick;
	}
	return pick;
}

int lengthCheck(string inp1, string inp2) //return= 0 valid, 1 not same length, 2 length not 10
{
	int l1 = inp1.length();
	int l2 = inp2.length();
	int logic =0;

	if(l1 != l2){
		logic = 1;
		return logic;
	}

	else if(l1 != 10 || l2 != 10){
		logic = 2;
		return logic;
	}

	else {
		return logic;
	}
}

bool ibanVer(string inp1, string inp2)
{
	bool logic = false;
	if (lengthCheck(inp1,inp2) == 1)
	{
		cout << "ERROR: The length of the IBAN numbers must be the same!" << endl;
	}

	else if (lengthCheck(inp1,inp2) == 2)
	{
		cout << "ERROR: Length of IBAN numbers must be 10!" << endl;
	}

	else if (lengthCheck(inp1,inp2) == 0)
	{
		if (countryCheck(inp1,inp2) == 1)
		{
			cout << "ERROR: Invalid country code. Country codes can only be TR, IS or DZ!" << endl;
		}

		else if (countryCheck(inp1,inp2) == 0 || countryCheck(inp1, inp2) == 2)
		{
			if(digitCheck(inp1) == false || digitCheck(inp2) == false)
			{
				cout << "ERROR: IBAN numbers should only contain digits after the country abbreviation!" << endl;
			}
			
			else
			{
				if((inp1.substr(2,9) == inp2.substr(2,9)) && (countryCheck(inp1, inp2) == 2))
				{
					cout << "ERROR: IBAN numbers should be different!" << endl;
				}
				else{
					logic = true;
				}
			}
		}
	}
	return logic;
}

void iban(string &inp1, string &inp2)
{
	bool logic = false;

	while(logic == false){
		cout << endl << "Please enter the sender and receiver IBAN numbers: ";
		cin >> inp1 >> inp2;
		ToUpper(inp1);
		ToUpper(inp2);
		logic = ibanVer(inp1, inp2);

	}
}
//global IBAN checker

int transCount()
{
	string filename = "transactions.txt";
	ifstream input;
	input.open(filename.c_str());
	string line;
	int counter = 0;
	while(getline(input, line))
	{
		counter++;
	}
	input.close();
	return counter;
}

double taxer(double &amount)
{
	double tax = 0;

	if(amount <= 100)
	{
		tax = (amount/100)*1;
	}

	else{
		tax = (amount/100)*3;
	}
	amount = amount - tax;
	return tax;
}

void addTrans(string inp1, string inp2)
{
	double transAmount;
	int curTransCount = transCount();
	bool logic =true;
	while(logic){
		cout << "Please enter the amount to be sent: ";

		if(!(cin >> transAmount))
		{
			string s;
			cin.clear();
			cin >> s;
			cout << "ERROR: \""<< s << "\" INVALID CHOICE!" << endl << endl;
		}

		else if(transAmount <= 0)
		{
			cout << "ERROR: \""<< transAmount << "\" INVALID AMOUNT!" << endl << endl;
			
		}

		else{
			logic = false;
		}
	}

	string filename = "transactions.txt";
	ofstream output;
	output.open(filename.c_str(),ios::app);
	int newTransCount = curTransCount +1; 
	double tax = taxer(transAmount);
	output << newTransCount << " " << inp1 << " " << inp2 << " " << transAmount << " " << tax << endl;
	cout << "Transaction added with TID: " << newTransCount << endl << endl;
	output.close();
}

bool tidControl(string op)
{
	for(int i = 0; (i < op.length()); i++)
	{
		char ch = op.at(i);
		if(ch > '9' || ch < '0')
		{
			return false;
		}
	}
	return true;
} 

void searchTrans(int op)
{

	if (transCount() < op)
	{
		cout << "ERROR: TRANSACTION #" << op << " NOT FOUND!" << endl << endl;
	}

	else
	{
		string filename = "transactions.txt";
		ifstream input;
		input.open(filename.c_str());
		string line;
		while(getline(input,line))
		{
			string i1;
			string i2;
            string ts;
			string t;
			string a;
			int a_l;
			int tn;
			a_l = line.find(" ",24) -2;
			a = line.substr(24, a_l - 22);
			int t_start;
			t_start = a_l + 1;
			i1 = line.substr(2,10);
			i2 = line.substr(13,10);
            ts = line.substr(0,1);
            t = line.substr(t_start+2);
			tn = atoi(ts);
			if(tn == op)
			{
				cout << "TRANSACTION #"<< tn << endl << i1 << " ==> " << i2 << endl << "Amount: " << a << endl << "Tax: " << t << endl << endl;
			}
		}

	}


}

void maxTrans()
{
	string filename = "transactions.txt";
	ifstream input;
	input.open(filename.c_str());
	if(input.fail())
	{
		cout << endl <<	"ERROR: TRANSACTION FILE IS EMPTY!" << endl << endl;
	}

	else{
		string line;
		double max = 0;
		int maxL;
		while(getline(input,line))
		{
			string i1;
			string i2;
            string ts;
			string t;
			string a;
			int a_l;
			int tn;
			double amount;
			double tax;
			double t_amount;
			a_l = line.find(" ",24) -2;
			a = line.substr(24, a_l - 22);
			int t_start;
			t_start = a_l + 1;
			i1 = line.substr(2,10);
			i2 = line.substr(13,10);
            ts = line.substr(0,1);
            t = line.substr(t_start+2);
			tn = atoi(ts);
			amount = atof(a);
			tax = atof(t);
			t_amount = amount + tax;
			if(amount > max)
			{
				max = amount;
				maxL = tn;
			}
		}

		string line2;
		input.clear();
		input.seekg(0);
		while(getline(input,line2))
		{
			string i1;
			string i2;
            string ts;
			string t;
			string a;
			int a_l;
			int tn;
			a_l = line2.find(" ",24) -2;
			a = line2.substr(24, a_l - 22);
			int t_start;
			t_start = a_l + 1;
			i1 = line2.substr(2,10);
			i2 = line2.substr(13,10);
            ts = line2.substr(0,1);
            t = line2.substr(t_start+2);
			tn = atoi(ts);
			if(tn == maxL)
			{
				cout << endl << "TRANSACTION #"<< tn << endl << i1 << " ==> " << i2 << endl << "Amount: " << a << endl << "Tax: " << t << endl << endl;
			}
		}				
	}	
}

void minTrans()
{
	string filename = "transactions.txt";
	ifstream input;
	input.open(filename.c_str());
	if(input.fail())
	{
		cout << endl <<	"ERROR: TRANSACTION FILE IS EMPTY!" << endl << endl;
	}

	else{
		string line;
		double min;
		min= DBL_MAX;
		int minL;
		while(getline(input,line))
		{
			string i1;
			string i2;
            string ts;
			string t;
			string a;
			int a_l;
			int tn;
			double amount;
			double tax;
			double t_amount;
			a_l = line.find(" ",24) -2;
			a = line.substr(24, a_l - 22);
			int t_start;
			t_start = a_l + 1;
			i1 = line.substr(2,10);
			i2 = line.substr(13,10);
            ts = line.substr(0,1);
            t = line.substr(t_start+2);
			tn = atoi(ts);
			amount = atof(a);
			tax = atof(t);
			t_amount = amount+tax;
			if(amount < min)
			{
				min = amount;
				minL = tn;
			}
		}

		string line2;
		input.clear();
		input.seekg(0);
		while(getline(input,line2))
		{
			string i1;
			string i2;
            string ts;
			string t;
			string a;
			int a_l;
			int tn;
			a_l = line2.find(" ",24) -2;
			a = line2.substr(24, a_l - 22);
			int t_start;
			t_start = a_l + 1;
			i1 = line2.substr(2,10);
			i2 = line2.substr(13,10);
            ts = line2.substr(0,1);
            t = line2.substr(t_start+2);
			tn = atoi(ts);
			if(tn == minL)
			{
				cout << endl << "TRANSACTION #"<< tn << endl << i1 << " ==> " << i2 << endl << "Amount: " << a << endl << "Tax: " << t << endl << endl;
			}
		}				
	}	
}

bool stats(double &total_e, double &total_a, double &total_t)
{
	string filename = "transactions.txt";
	ifstream input;
	input.open(filename.c_str());
	if(input.fail() || transCount() == 0)
	{
		cout<< endl <<	"ERROR: NO TRANSACTIONS FOUND!" << endl;
		return false;
	}

	else{

		string line;
	
		while(getline(input,line))
		{
			string i1;
			string i2;
            string ts;
			string t;
			string a;
			int a_l;
			int tn;
			double amount;
			double tax;
			double t_amount;
			a_l = line.find(" ",24) -2;
			a = line.substr(24, a_l - 22);
			int t_start;
			t_start = a_l + 1;
			i1 = line.substr(2,10);
			i2 = line.substr(13,10);
            ts = line.substr(0,1);
            t = line.substr(t_start+2);
			tn = atoi(ts);
			amount = atof(a);
			tax = atof(t);
			t_amount = amount+tax;
			total_e += t_amount;
			total_a += amount;
			total_t += tax;
		}
		return true;
	}
}

int main()
{
	string op;
	cout << "Welcome to CS201 Banking Application!" << endl;
	cout << "Welcome admin user" << endl << endl;


	bool logic = true;
	
	while(logic == true)
	{
		cout << "Please select your action:" << endl << "1. Create transaction" << endl << "2. Search transaction" << endl << "3. Show biggest transaction" << endl << "4. Show smallest transaction" << endl << "5. Show transaction stats" << endl << "6. Exit program" << endl << "Enter your choice: ";
		cin >> op;
		int selection = menu(op);
		if (selection == 6)
		{
			cout << endl;
			cout << "Thank you..." << endl;
			logic = false;
		}
	
		else
		{
			if(selection == 1)
			{
				string newop1;
				string iban1, iban2;
				iban(iban1, iban2);
				addTrans(iban1, iban2);
			}

			else if(selection == 2)
			{
				string tids1;
				do{
					cout << endl;
					cout << "Please enter a Transaction ID: ";
					cin >> tids1;
					bool c1 = tidControl(tids1);
					if( c1 == true)
					{
						int tidn1 = atoi(tids1);
						searchTrans(tidn1);
					}

					else{
						cout << "ERROR: \""<< tids1 << "\" INVALID TID!" << endl;

					}
				}while(tidControl(tids1) == false);
			}
			else if(selection == 3)
			{
				maxTrans();
			}
			else if(selection == 4)
			{
				minTrans();
			}
			else if(selection == 5)
			{
				double total_e = 0;
				double total_a = 0;
				double total_t = 0;
				bool flogic = stats(total_e,total_a,total_t);
				
				if(flogic == true)
				{
					int tc = transCount();
					double av_a = total_a/tc;
					double av_t = total_t/tc;
					cout << endl << "TRANSACTION STATS" << endl;
					cout << "Total money transferred (including tax): " << total_e << endl;
					cout << "Total money transferred (excluding tax): " << total_a << endl;
					cout << "Average money transferred per transaction (excluding tax): " << av_a << endl;
					cout << "Average tax deducted per transaction: " << av_t << endl;
					cout << "Total tax deducted: " << total_t << endl << endl;
				}
				else{
					cout << endl;
				}
			}
		}
	}

	return 0;
}