#include <iostream>
#include <string>
#include "strutils.h"


using namespace std;

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

	else if(cc1 != cc2)
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

		else if (countryCheck(inp1,inp2) == 2)
		{
			cout << "ERROR: Country codes of IBAN numbers must be same!" << endl;
		}

		else if (countryCheck(inp1,inp2) == 0)
		{
			if(digitCheck(inp1) == false || digitCheck(inp2) == false)
			{
				cout << "ERROR: IBAN numbers should only contain digits after the country abbreviation!" << endl;
			}
			
			else
			{
				logic = true;
			}
		}
	}
	return logic;
}

void sibCheck(string inp1, string inp2)
{

	int counter = 0;
	int logic = true;
	for(int i = 2; i < 10 && logic == true; i++)
	{
		bool zcheck = (inp1.at(i) == '0' || inp2.at(i) == '0');
		bool scheck = (inp1.at(i) == inp2.at(i));

		if (zcheck == true && scheck == false)
		{
			cout << "The IBANs are not \"sibling\", the 0's are not at the same place";
			logic = false;
		}

		else
		{
			counter++;
		}
	}
	

	if(counter == 8)
	{
		int sum1 = 0;
		int sum2 = 0;
		
		for(int i = 2; i < 10; i++)
		{
			sum1 += inp1.at(i);
			sum2 += inp2.at(i);
		}
		
		if(sum1 == sum2)
		{
			cout << "The IBAN numbers" << endl << inp1 << endl << inp2 << endl << "are \"sibling\" IBAN numbers!";
		}

		else
		{
			cout << "The IBANs are not \"sibling\", the summation of non-zero values are not equal";
		}
	}
}



int main()
{
	string inp1;
	string inp2;
	bool logic = true;

	cout << "Hello, welcome to the \"sibling\" IBAN calculator!" << endl;


	while(logic == true){
		cout << "Please enter the IBANs to compare: ";
		cin >> inp1 >> inp2;

		if(inp1 == "exit" && inp2 == "program")
		{
			logic = false;
		}

		else
			{
			if(ibanVer(inp1,inp2) == true)
			{
				sibCheck(inp1,inp2);
				cout << endl;
			}

			cout << endl;
		}
	}

	return 0;
}