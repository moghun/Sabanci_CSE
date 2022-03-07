//Muhammed Orhun Gale - 26754 - HashTable.h
//Modifed version of the template Hash Table class in the CS300 "Hash Tables (2)" course slides


//Since this class is provided as Template, ***please do not include*** class source files into the project
//To use it, include the source file that you will use to the end

//DictItem.cpp is included for the compressor program that is provided, it is *subject to change* -- Do not add its source file to the project


#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <vector>
#include <string>
#include "DictItem.h"

using namespace std;



template <class HashedObj>
class HashTable
{
public:
	explicit HashTable(const HashedObj &, int);
	
	const HashedObj & find(const HashedObj &) const;
	void makeEmpty();

	bool insert(const HashedObj&);
	void remove(const HashedObj&);

	enum EntryType
	{ACTIVE, EMPTY, DELETED};

	const HashedObj & searchString(const string &, const int &) const; //A member function that finds the entry with given string key
																	   //***For the classes that provides string as the key***

private:

	template <class HashedObj>
	struct HashEntry
	{
	public:
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
			:element(e), info(i) {}
	};

	vector< HashEntry<HashedObj>> arr;
	int currentSize;
	const HashedObj ITEM_NOT_FOUND;

	bool isActive(int) const;
	int findPos(const HashedObj &) const;
};

template <class HashedObj>
int hash(const HashedObj &x, int table_size);

#include "DictItem.cpp"		//Change in accordance with the class that you will use in the Hash Table 
#include "HashTable.cpp"
#endif