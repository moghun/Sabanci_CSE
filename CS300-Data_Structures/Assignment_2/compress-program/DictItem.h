//Muhammed Orhun Gale - 26754 - DictItem.h
//DictItem class that is provided to implement LZW compression algorithm


#ifndef DICTITEM_H
#define DICTITEM_H


#include <string>
#include <vector>

using namespace std;

#define CLOSESTPRIME 8209 //Closest larger prime to the 8192, picked to hold lambda under 0.5 


class DictItem
{
public:
	DictItem();				//Default constructor
	DictItem(int, string);	//Parametric constructor
	
	bool operator==(const DictItem &) const;	//Overloaded "equal" operator among DictItem variables
	bool operator!=(const DictItem &) const;	//Overloaded "not equal" operator among DictItem variables
		
	bool operator==(const string &) const;		//Overloaded "equal" opeator for a string and DictItem variable for easier comparison
	bool operator!=(const string &) const;		//Overloaded "not equal" opeator for a string and DictItem variable for easier comparison

	int getID() const;			//Accessor for the private dictID variable
	string getString() const;	//Accessor for the private dictString variable

	

private:

	int dictID;
	string dictString;
};


#endif