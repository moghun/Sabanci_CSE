//Muhammed Orhun Gale - 26754 - HashTable.cpp
//Modifed version of the template Hash Table class in the CS300 "Hash Tables (2)" course slides

//DO NOT INCLUDE THIS FILE TO THE PROJECT IN ORDER TO PREVENT "UNRESOLVED EXTERNAL" ERRORS


#include "HashTable.h"
#include "DictItem.h"
#include <vector>

using namespace std;

template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj & notFound, int size)
	:ITEM_NOT_FOUND(notFound), arr(size)
{
	this->makeEmpty();
}

template <class HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
	for(unsigned int i = 0; i < arr.size(); i++)
	{
		HashEntry<HashedObj> x = arr[i];
		x.info = EMPTY;
		arr[i] = x;
	}
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
	HashEntry<HashedObj> x = arr[currentPos];
	return x.info == ACTIVE;
}

template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj & x)
{
	int i = 0;
	unsigned int p;
	p = ::hash(x, (this->arr).size());  //Overload the hash function in accordance with the user class

	HashEntry<HashedObj> b = arr[p];

	int currentPos = findPos(x);
	
	if( isActive(currentPos))
	{
		arr[currentPos].info = DELETED;
	}
}

template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find(const HashedObj & x) const
{
	int currentPos = findPos(x);
	
	if(currentPos == -1)
	{
		return ITEM_NOT_FOUND;
	}

	else if(isActive(currentPos)) 
	{
		return arr[currentPos].element; 
	}

	else{
		return ITEM_NOT_FOUND;
	}
}

template <class HashedObj>
bool HashTable<HashedObj>::insert( const HashedObj & x )
{
	int i = 0;
	unsigned int p; 
	p = ::hash(x, (this->arr).size());	//Overload the hash function in accordance with the user class
	
	int currentPos = findPos(x);
	
	if(isActive(currentPos))
	{
		return false;
	}
	
	arr[currentPos] = HashEntry<HashedObj>(x, ACTIVE);
	return true;
}

template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj &x) const
{
	int i = 0;
	unsigned int p;
	p = ::hash(x, (this->arr).size());	//Overload the hash function in accordance with the user class

	while((arr[p].info != EMPTY) && (arr[p].element != x))
	{
		i++;
		p += i;

		if(p >= arr.size())
		{
			p -= arr.size();
		}

		if(i == arr.size())
		{
			return -1;
		}
	}
	return p;
}

//TODO: A special member function ***for the classes that provides string as key***
//		Searches for given string based on the fact that only unique elements will be inserted into the list (See the insert function) 
template <class HashedObj>
const HashedObj & HashTable<HashedObj>::searchString(const string& search, const int &hashV) const
{
	int i = 0;
	unsigned int p = hashV;

	while((arr[p].info != EMPTY) && (arr[p].element != search))
	{
		i++;
		p += i;

		if(p >= arr.size())
		{
			p -= arr.size();
		}

		if(i == arr.size())
		{
			return ITEM_NOT_FOUND;
		}
	}
	return arr[p].element;
}
//END:	Entry that includes given string is returned

//TODO:	Hash given elements according to the hash function that is overloaded by the user class
template <class HashedObj>
int hash(const HashedObj &x, int table_size) 
{
    return ::hash(x, table_size); //Overload the hash function in accordance with the user class
}
//END:	Given values passed to the overloaded class