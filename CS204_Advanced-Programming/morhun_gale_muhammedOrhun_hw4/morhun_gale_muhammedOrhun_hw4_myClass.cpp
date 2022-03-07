#include <iostream>
#include "morhun_gale_muhammedOrhun_hw4_myClass.h"
using namespace std;

Stack::Stack()
{
	top = nullptr; 
}


Stack::~Stack()
{
	StackNode* temp = top;

	while(temp != nullptr)
	{
		StackNode* next = temp->next;
		delete temp;
		temp = next;
	}
}


void Stack::push(cellStruct element)
{
	StackNode *newNode;

	newNode = new StackNode;
	newNode->el = element;

	if (isEmpty())
	{
		top = newNode;
		newNode->next = nullptr;
	}
	else	
	{
		newNode->next = top;
		top = newNode;
	}
}


void Stack::pop(cellStruct &element)
{
	StackNode *temp;

	if (!isEmpty())
	{
		element = top->el;
		temp = top->next;
		delete top;
		top = temp;	
	}
}

bool Stack::isEmpty()
{
	return top == nullptr;
}

