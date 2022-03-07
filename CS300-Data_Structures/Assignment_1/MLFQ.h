//Muhammed Orhun Gale - 26754
#ifndef MLFQ_H
#define MLFQ_H

#include "Queue.h"

class MLFQ
{
public:
	MLFQ();   //Default constructor
	MLFQ(const int&, const int&, const vector<Process> &);  //Parametric constructor
	~MLFQ();  //Destructor - also deletes the dynamically allocated memory of each queue

	bool isMLFQEmpty() const;  //Checks are there any processes in the MLFQ or not

	string restartQuantum();   //Resets the processes for a new quantum and initializes 
	string startQuantum();     //Starts the processing of a Quantum

private:
	struct listNode   //A struct to build linked list that includes a queue and its features
	{
		int qID;
		int numProcesses;
		Queue queue;
		listNode* next;
	};

	listNode* head;
	int numQueues;
	vector<Process> processList;   //List of the current processes in the MLFQ
	int quantumSize;               //Limiting time of a quantum
	int quantumCt;

	void start(const vector<Process>&);  //Initializes processes into the MLFQ
	vector<Process> takeBack();          //Takes back the current status of the MLFQ in order to restart it according to the queue status
	int processCounter() const;          //Traverse the MLFQ and count the number of processes currently
};
#endif