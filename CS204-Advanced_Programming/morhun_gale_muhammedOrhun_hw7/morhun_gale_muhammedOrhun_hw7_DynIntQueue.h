#ifndef HW7DynIntQueue_H
#define HW7DynIntQueue_H

struct ItemNode
{
	int itemId;
	ItemNode* next;
	ItemNode(int num, ItemNode* ptr = NULL)
	{
		itemId = num;
		next = ptr;
	}
};

class HW7DynIntQueue
{
private:
	// These track the front and rear of the queue.
	ItemNode* front;
	ItemNode* rear;
	int currentSize; 
public:
	// Constructor.
	HW7DynIntQueue();
	HW7DynIntQueue(const HW7DynIntQueue& rhs);
	// Member functions.
	int getCurrentSize() const;
	HW7DynIntQueue& operator=(const HW7DynIntQueue& rhs);
	void enqueue(int id);
	void dequeue(int& id);
	bool isEmpty() const;
	//Destructor
	~HW7DynIntQueue();
};
#endif