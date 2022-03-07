#include <iostream>
#include "morhun_gale_muhammedOrhun_hw7_DynIntQueue.h"
using namespace std;

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
HW7DynIntQueue::HW7DynIntQueue()
{
	front = NULL;
	rear = NULL;
	currentSize = 0;
}



//************************************************
// Copy Constructor.                             *
//************************************************
HW7DynIntQueue::HW7DynIntQueue(const HW7DynIntQueue& rhs)
{
	front = NULL;
	rear = NULL;
	currentSize = 0;

	if(!rhs.isEmpty())
	{
		currentSize = 0;
		ItemNode* tmp = rhs.front;
		while (tmp != NULL)
		{
			enqueue(tmp->itemId);
			tmp = tmp->next;
		}
	}
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void HW7DynIntQueue::enqueue(int num)
{
	 if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new ItemNode(num);
		rear = front;
		currentSize++;

	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new ItemNode(num);
		rear = rear->next;
		currentSize++;

	}

}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void HW7DynIntQueue::dequeue(int & num)
{
	ItemNode* temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		num = front->itemId;
		temp = front;
		front = front->next;
		delete temp;
		currentSize--;
	}
}

//*********************************************
// Function getCurrentSize returns current    *
// size of the queue.						  *
//*********************************************
int HW7DynIntQueue::getCurrentSize() const
{
	return currentSize;
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool HW7DynIntQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else
		return false;
}

//*********************************************
// Assignment Operator						  *
//*********************************************
HW7DynIntQueue& HW7DynIntQueue::operator=(const HW7DynIntQueue& rhs)
{
	if (this != &rhs) //self assignment check
	{

		int value;   // Dummy variable for dequeue
		while (!isEmpty())
			dequeue(value); //delete all elements
	
		front = NULL;
		rear = NULL;
		currentSize = 0;
		
		ItemNode* tmp = rhs.front;
		while (tmp != NULL)
		{
				enqueue(tmp->itemId);
				tmp = tmp->next;
		}

	}
	return *this;
}
//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
HW7DynIntQueue::~HW7DynIntQueue()
{
	int value;   // Dummy variable for dequeue

	while (!isEmpty())
		dequeue(value); //delete all elements
}

