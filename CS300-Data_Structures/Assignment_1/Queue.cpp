//Muhammed Orhun Gale - 26754
//Modifed version of the Queue class in the CS300 "Stacks and Queues" course slides

#include "Queue.h"
#include <iostream>

Queue::Queue()
{
	qArray = nullptr;
	this->max_size = 0;
	this->makeEmpty();
}

Queue::Queue(int size)
{
	qArray = new Process[size];
	this->max_size = size;
	this->makeEmpty();
}

bool Queue::isEmpty() const
{
	return (this->curr_size == 0);
}

bool Queue::isFull() const
{
	return (this->curr_size == this->max_size);
}

Process Queue::dequeue()
{
	curr_size--;

	Process proc = qArray[front];	
	increment(front);

	return proc;
}

void Queue::enqueue(const Process & proc)
{
	increment(back);
	qArray[back] = proc;

	curr_size++;
}

void Queue::makeEmpty()
{
	curr_size = 0;
	front = 0;
	back = -1;
}

void Queue::increment(int& num)
{
	num++;
	if(num == max_size)
	{
		num = 0;
	}
}