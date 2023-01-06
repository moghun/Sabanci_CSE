#include <iostream>
#include <string>
#include "morhun_gale_muhammedOrhun_hw3_myClass.h"


using namespace std;

SubSeqsList::SubSeqsList()
{
	hHead = nullptr;
}

void SubSeqsList::add(int n)
{
	SubSeqHeadNode* temp = hHead;

	SubSeqNode* subHead;
	subHead = new SubSeqNode(n, nullptr);
	addSubSeq(subHead, 1);

	while(temp != nullptr)
	{
		int lastNum = lastEl(temp->sHead, temp->size);

		if( lastNum < n)
		{
			SubSeqNode* copiedSub = copySub(temp->sHead);

			SubSeqNode* newHead = copiedSub;
			SubSeqNode* ptr = newHead;
			while(ptr != nullptr)
			{
				ptr = ptr->next;
			}
			
			SubSeqNode* newNode;
			newNode = new SubSeqNode(n, nullptr);
			
			ptr->next = newNode;

			addSubSeq(newHead, temp->size+1);
		}
		temp = temp->next;
	}
}

void SubSeqsList::del(int n)
{
	SubSeqHeadNode* temp = hHead;
	SubSeqHeadNode* hodl = nullptr;

	while(temp != nullptr)
	{
		SubSeqNode* sHead = temp->sHead;
		bool check = checkExist(sHead, n);
		
		if(temp != hHead)
		{
			if(check == true)
			{
				hodl->next = temp->next;

				deleteSubSeq(sHead);
				delete temp;
				
				temp = hodl->next;
			}

			else{
				hodl = temp;
				temp = temp->next;
			}
		}

		else{
			
			if(check == true)
			{
				hHead = hHead->next;

				deleteSubSeq(sHead);
				delete temp;

				temp = hHead;
			}

			else{
				hodl = temp; //If "will be deleted" number does not in the first node, follower node will initilazed here
				temp = temp->next;
			}
		}
	}
}

//Search in order to find the "will be removed" input
bool SubSeqsList::search(int n)
{
	SubSeqHeadNode* temp = hHead;

	while(temp != nullptr)
	{
		if(temp->sHead->value == n)
		{
			return true;
		}

		temp = temp->next;
	}

	return false;
}

void SubSeqsList::print()
{
	SubSeqHeadNode* temp = hHead;

	while(temp != nullptr)
	{
		SubSeqNode* sHead = temp->sHead;

		cout << "FINAL CONTENT" << endl << temp->size << " | " << sHead->value;
		sHead = sHead->next;

		while(sHead != nullptr)
		{
			cout << "--> " << sHead->value;
			sHead = sHead->next;
		}
		cout << endl;

		temp = temp->next;
	}
}

void SubSeqsList:: clear()
{
	while(hHead != nullptr)
	{
		SubSeqHeadNode* temp = hHead->next;

		deleteSubSeq(hHead->sHead);
		delete hHead;

		hHead = temp;
	}
}

//By checking last element of the each node I thought I could compare and list with that way
int SubSeqsList::lastEl(SubSeqNode* node, int size)
{
	SubSeqNode* temp = node;

	for(int i = 0; i < size; i++)
	{
		temp++;
	}

	return temp->value;
}

bool SubSeqsList::checkExist(SubSeqNode* node, int n)
{
	SubSeqNode* temp = node;

	while(temp != nullptr)
	{
		if(temp->value == n)
		{
			return true;
		}

		temp = temp->next;
	}

	return false;
}
//compare two subsequence - with this I thought I could replace in order to make the list from lower to higher
bool SubSeqsList::compare(SubSeqNode* node1, SubSeqNode* node2)
{
	while(node1 != nullptr && node2 != nullptr)
	{
		if(node1->value > node2->value)
		{
			return false;
		}

		else if(node1->value < node2->value)
		{
			return true;
		}
	}
	return false;
}

//If last element of one sequence is smaller than the input num, copy the subsequence to add num and place it to the proper location
SubSeqNode* SubSeqsList::copySub(SubSeqNode* nNode)
{
	SubSeqNode* node = nNode;
	int firstValue = node->value;

	SubSeqNode* copyHead;
	copyHead = new SubSeqNode(firstValue, nullptr);

	SubSeqNode* temp = nullptr;

	while(node->next != nullptr)
	{
		SubSeqNode* newNode;
		newNode = new SubSeqNode(node->next->value, nullptr);

		temp->next = newNode;
		temp = newNode;

		node = node->next;
	}

	return copyHead;
}


//Compare according to list size and last element wise if finds a place to put it will, in theory...
void SubSeqsList::addSubSeq(SubSeqNode* node, int size)
{
	SubSeqHeadNode* temp = hHead;
	
	if(hHead == nullptr)
	{
		hHead = new SubSeqHeadNode(size, node);
	}

	else if(size == 1)
	{
		if( node->value < temp->sHead->value)
		{
			SubSeqHeadNode* newFirstEl;
			newFirstEl = new SubSeqHeadNode(1, node);
			hHead = newFirstEl;
		}

	}

	else{
		while(temp->next != nullptr && temp->next->size <= size)
		{
			if(temp->next->size == size)
			{
				bool check = compare(node, temp->next->sHead);
				if(check == true)
				{
					break;
				}
				temp = temp->next;
			}
		}

		SubSeqHeadNode* nHead;
		nHead = new SubSeqHeadNode(size, node);		
		nHead->next = temp->next;
		temp->next = nHead;
	}
}

void SubSeqsList::deleteSubSeq(SubSeqNode* node)
{
	SubSeqNode* temp = node;
	SubSeqNode* hodl = nullptr;

	while(node != nullptr)
	{
		hodl = temp->next;
		
		delete temp;

		temp = hodl;
	}
}