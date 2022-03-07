//Muhammed Orhun Gale - 26754
//Modifed version of the Queue class in the CS300 "Stacks and Queues" course slides
#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <istream>
#include <fstream>
#include <sstream>
using namespace std;


struct Process      //A struct to store information of each process
{
	int ID;
	char status;
	int numInstructions;  //Remaining number of instructions
	vector<int> cpuTime;  //Command list of a process
	int currentQueue;
};


class Queue
{
public:
	Queue();
	Queue(int);

	bool isEmpty() const;
	bool isFull() const;
	
	void makeEmpty();
	Process dequeue();
	void enqueue(const Process&);

private:
	Process* qArray;
	int max_size;
	int curr_size;
	int front;
	int back;

	void increment(int&);

	friend class MLFQ; //In order to delete the dynamically allocated memory by each queue when a MLFQ goes out of scope
};

#endif