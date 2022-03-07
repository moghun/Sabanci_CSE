//Muhammed Orhun Gale - 26754
#include "MLFQ.h"
#include "Queue.h"
#include <iostream>

//TODO: Default constructor for MLFQ
MLFQ::MLFQ()
{
	head = nullptr;
	numQueues = 0;
	quantumSize = 0;
	quantumCt = 0;

	cout << "No \"Process List\" have been initilized" << endl;
}
//END:  Empty MLFQ object created

//TODO: MLFQ constructor with settings
MLFQ::MLFQ(const int& numOfQ, const int& quantSize, const vector<Process>& processes)
{
	//Initialize MLFQ data members
	numQueues = numOfQ;
	quantumSize = quantSize;
	quantumCt = 0;
	processList = processes;
	int qSize = processList.size();

	//Create the linkedlist structure
	head = new listNode;
	listNode* ptr = head;
	for(int i = numOfQ; 0 < i; i--)
	{
		ptr->numProcesses = 0;
		ptr->qID = i;
		
		Queue q(qSize);   //Initilize each nodes' queue
		ptr->queue = q; 

		ptr->next = new listNode;

		if(i == 1)       //Set the last nodes' next ptr as nullptr
		{
			ptr->next = nullptr;
		}

		else{
			ptr = ptr->next;
		}
	}

	start(processes); //Initilize processes to queues
}
//END:  MLFQ object is created with given settings

//TODO: Destructor for MLFQ
MLFQ::~MLFQ()
{
	listNode* ptr = head;
	listNode* node2bDeleted;

	while(ptr != nullptr)
	{
		node2bDeleted = ptr;
		ptr = ptr->next;
		delete node2bDeleted;
		delete [] (ptr->queue).qArray;     //Dynamically allocated memory by each queue is deleted
	}
	head = nullptr;
}
//END:  MLFQ object and queues are destructed

//TODO: Initialize processes in queues
void MLFQ::start(const vector<Process> &list)
{
	for(unsigned int i = 0; i < list.size(); i++)
	{
		(head->queue).enqueue(list[i]);
	}

	head->numProcesses = list.size();
}
//END:  Processes are initialized

//TODO: Take back processes from MLFQ in order
vector<Process> MLFQ::takeBack()
{
	vector<Process> list2bReturned;

	listNode* ptr = head;
	while(ptr != nullptr)
	{
		for(int i = 0; i < ptr->numProcesses; i++)
		{
				list2bReturned.push_back((ptr->queue).dequeue());
		}
		ptr->numProcesses = 0;
		(ptr->queue).makeEmpty();
		ptr = ptr->next;
	}

	return list2bReturned;
}
//END: Processes are taken back and returned as a vector

//TODO: Reset a quantum with the latest status of processes via carrying all of the processes to the topmost queue
//      Handle and return the "back" output update
string MLFQ::restartQuantum()
{
	vector<Process> oldQuant = takeBack();

	vector<Process> newQuant;

	string out = "";


	for(unsigned int i = 0; i < oldQuant.size();i++)
	{
		if(oldQuant[i].status != 'E')        //Check if the process is ended or not
		{
			if(oldQuant[i].currentQueue == this->numQueues)  //If it is already on the topmost prior queue, do not include it to the returning output
			{
				Process wbPush;
				oldQuant[i].currentQueue = head->qID;   
				newQuant.push_back(oldQuant[i]);
				oldQuant[i].status = 'Z';
			}

			else                               //Set status as 'B'
			{
				oldQuant[i].currentQueue = head->qID;   
				newQuant.push_back(oldQuant[i]);
				oldQuant[i].status = 'B';
			}
		}
	}

	quantumCt = 0;          //Reset the quantum counter

	for(unsigned int j = 0; j < oldQuant.size(); j++)          //"back" output
	{
		if(oldQuant[j].status != 'Z')
		{
			out = out + oldQuant[j].status + ", PC" + to_string(oldQuant[j].ID) + ", Q" + to_string(oldQuant[j].currentQueue) + "\n";
		}
	}

	start(newQuant);        //Start new quantum

	return out;
}
//END:  A new quantum is initialized and "back" output is returned

//TODO: Traverse the list and count how many processes are there currently
int MLFQ::processCounter() const
{
	int curr_numQ = 0;

	listNode* ptr = head;
	while(ptr != nullptr)
	{
		curr_numQ += ptr->numProcesses;
		ptr = ptr->next;
	}
	return curr_numQ;
}
//END:  Current number of processes is returned

//TODO: Check is there any process remain in the MLFQ or not
bool MLFQ::isMLFQEmpty() const
{
	int curr_numQ = processCounter();

	if(curr_numQ == 0)
	{
		return true;
	}

	else{
		return false;
	}
}
//END:  Emptiness condition checked

//TODO: 
string MLFQ::startQuantum()
{
	string out = "";

	listNode* ptr = head;

	while(ptr != nullptr && quantumCt < quantumSize) //If it is not the last queue and the quantum time is not finished yet
	{
		if(ptr->numProcesses == 0)                  //If no process in a queue, go next
		{
			ptr = ptr->next;
		}

		else
		{
			while((quantumCt < quantumSize) && (ptr->numProcesses != 0))     //If there are processes in the queueu and quantum time remained
			{
				Process p;
				p = ptr->queue.dequeue();           //Take process


				if(p.status == 'E')            //Check if it is ended or not
				{
					ptr->queue.enqueue(p);
					quantumCt--;               //If it is ended afterwards reset the remaining quantum time 

				}

				else
				{
					vector<int> commandList = p.cpuTime;   //Take the current commands of a process
					int command = p.cpuTime[(commandList.size()-p.numInstructions)];     //According to the number of instructions left, decide which command will be taken

					p.numInstructions--;   //Instruction taken, decrement remaining insturctions

					if(p.numInstructions == 0) //If there are no remaining instructions, it is finished - set as finished
					{
						p.status = 'E';
						p.currentQueue = -1;
						ptr->numProcesses--;  //Number of processes is decremented in the current queue
					}

					else
					{
						if(command == 0)     //If the current command is 0, do not move to the lower queue
						{
							p.status = '0';
							ptr->queue.enqueue(p);     //Enqueue to the same queue
						}


						else
						{
							if(ptr->next != nullptr)    //If it is not the last queue
							{
								p.status = '1';         //Enqueue to the lower queue
								p.currentQueue = ptr->next->qID;
								
								ptr->numProcesses--;        //Decrement number of processes of the current queue
								ptr->next->numProcesses++;  //Increment number of processes of the lower queue
								ptr->next->queue.enqueue(p);
							}

							else  //If last queue, enqueue to the same queue
							{
								p.status = '1';
								ptr->queue.enqueue(p);  
							}
						}
					}

				}
				quantumCt++;   //Quantum is done, increment quantum counter
				
				//Set "result" output
				out = out+ p.status + ", PC" + to_string(p.ID) + ", Q";
				if(p.currentQueue != -1)
				{
					out = out + to_string(p.currentQueue) + "\n";
				}
				else{
					out = out + "X\n";
				}
			}
			ptr = ptr->next;
		}
		
	}
	return out;
}
//END:  A quantum is processed and the "result" of that quantum is returned