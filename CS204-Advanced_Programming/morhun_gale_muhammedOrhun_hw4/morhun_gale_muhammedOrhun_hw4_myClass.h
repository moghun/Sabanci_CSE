#ifndef __MYCLASS
#define __MYCLASS
//In order to access the elements of 2D matrix, the cellStruct designed as it can store the coordinates
struct cellStruct
{
	bool flag;
	char bin;
	int x;  
	int y;

	cellStruct::cellStruct() //Default constructor
	{
		flag = false;
	}
};

struct StackNode
{
	cellStruct el;
	StackNode *next;
};

class Stack
{
public:
	Stack();
	~Stack(); //Destructor

	void push(cellStruct);
	void pop(cellStruct &);
	bool isEmpty();

private:
	StackNode* top;

};
#endif