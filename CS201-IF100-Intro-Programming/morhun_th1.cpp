#include <iostream>
#include <string>
#include "strutils.h"

using namespace std;

bool checkWord(string word)
{
	for (unsigned int i = 0; i < word.length(); i++)
	{
		if ( word.at(i) < 'a' || word.at(i) > 'z') {
			return false;
		}
	return true;
	}
}


string getSource()
{
	string input;
	string source = "";

	cout << "Enter the source string: ";
	

	do {
		cin >> input;
		ToLower(input);
		if (input != "end" && checkWord(input) == true) {
			source += input + " ";
		}
	
	} while (input != "end");

	return source.substr(0,source.length()-1);
	
}


bool checkSearch(string word)
{
	if (word.length() < 0) 
	{
		return false;
	}

	string validOps = "+.*";

	if (validOps.find(word.at(word.length()-1)) == string::npos){
		return false;
	}

	for (unsigned int i = 0; i < word.length()-1; i++)
	{
		if (word.at(i) < 'a' || word.at(i) > 'z'){
			return false;
		}
	}
	return true;
}

void getSearch()
{
	string input;
	string search;
	string op;
	unsigned long lastIdx;

	cout << "Please enter the searching string: ";
	cin >> input;

	ToLower(input);

	while (input != "quit")
	{
		if (!checkSearch(input))
		{
			cout << "Invalid search string! Please re-enter: " << endl;
		}
		else{
			lastIdx = input.length()-1;
			op = input.substr(lastIdx);
			search = input.substr(0,lastIdx);
			cout << "Valid search string!" << endl;
			cout << "Enter the search string: " << endl; 
		}
		cin >> input;
		ToLower(input);
	}
}



int main()
{
	string source = getSource();
	cout << source << endl;
	getSearch();

	return 0;
}