//Muhammed Orhun Gale - 26754

//It does not work properly :(

//I believe my algorithm is working but I could not debug it, I believe the problem is one of my "ptr->next" statements but I could not find it,
//it is really hard to debug when there is a problem with class functions

#include <iostream>
#include <string>
#include <sstream>
#include "morhun_gale_muhammedOrhun_hw3_myClass.h"

using namespace std;

string getInput()
{
	string input;
	cout << "Please enter the numbers in a line: ";

	getline(cin, input);

	return input;
}


int main()
{

	string nums = getInput();

	if (nums == "")
	{
		cout << "FINAL CONTENT" << endl;
		cout << "List is empty" << endl;

		return 0;
	}

	else{
		istringstream numbers(nums);

		SubSeqsList list;	
		int num;

		while(numbers >> num)
		{
			if (num >= 0)
			{
				if(list.search(num) == true)
				{
					cout << num  << " is already in the list!" << endl;
				}
				
				else{
					list.add(num);
					cout << "Subsequence(s) containing "<< num <<" has/have been added" << endl;
				}
			}
			
			else{
				int pNum = num * (-1);
				list.del(pNum);
				cout << "Subsequence(s) containing "<< num <<" has/have been deleted" << endl;
			}
		}
		
		cout << endl;

		list.print();
		list.clear();

		return 0;
	}
}