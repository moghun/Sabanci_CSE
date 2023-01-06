//Muhammed Orhun Gale - 26754 - DictItem.cpp

//DO NOT INCLUDE THIS FILE TO THE PROJECT IN ORDER TO PREVENT "UNRESOLVED EXTERNAL" ERRORS


#include "HashTable.h"
#include <iostream>
using namespace std;

//TODO:	Default constructor for the DictItem class
DictItem::DictItem()
{
	this->dictID = -1;
	this->dictString = "";
}
//END:	DictItem constructed

//TODO:	Parametric constructor for the DictItem class
DictItem::DictItem(int ID, string str)
{
	this->dictID = ID;
	this->dictString = str;
}
//END:	DictItem constructed


//TODO:	Accessor for the private dictID variable
int DictItem::getID() const
{
	return this->dictID;
}
//END:	DictItem's ID is returned


//TODO:	Accessor for the private dictString variable
string DictItem::getString() const
{
	return this->dictString;
}
//END:	DictItem's key string is returned


//TODO: Overloaded "equal" operator among DictItem variables
bool DictItem::operator==(const DictItem &rhs) const
{
	return ((this->dictID == rhs.getID())) && (this->dictString == rhs.getString());
}
//END:	Returned if given two DictItem are equal


//TODO: Overloaded "not equal" operator among DictItem variables
bool DictItem::operator==(const string &rhs) const
{
	return (this->getString() == rhs);
}
//END:	Returned if given two DictItem are not equal


//TODO:	Overloaded "equal" opeator to decide that if the given string is equal to the DictItem's dictString private variable
bool DictItem::operator!=(const string &rhs) const
{
	return !(*this == rhs);
}
//END:	Returned if the string is equal to the DictItem's dictString variable

//TODO:	Overloaded "not equal" opeator to decide that if the given string is not equal to the DictItem's dictString private variable
bool DictItem::operator!=(const DictItem &rhs) const
{
	return !(*this == rhs);
}
//END:	Returned if the string is not equal to the DictItem's dictString variable


//TODO:	Hash function for the DictItem class
//		Add all the ASCII values of the key string and multiply it with 1151 then return the hash value
int hash(const DictItem & item, const int tableSize)
{
	int hashed = 0;

	for(unsigned int i = 0; i < (item.getString()).length(); i++)
	{
		char ch = (item.getString())[i];
		if(ch != '\0')							//Do not include end of the string sign's value to the calculation
		{
			hashed = hashed + (ch * 1151);		//1151 is the closest prime to the 31*37
		}
	}

	hashed = hashed % tableSize;				//Take mod to fit the variable into the table

	if(hashed < 0)								//In case of negative values
	{
		hashed += tableSize;
	}
	return hashed;
}
//END:	Given DictItem is hashed according to its string key and hash value is returned 
