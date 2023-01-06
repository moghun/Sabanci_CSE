#include <iostream>
#include <string>
#include <sstream>
#include "morhun_gale_muhammedOrhun_hw2_strutils.h"

using namespace std;

//TODO: Build linked list - given in homework
struct node
{
int value;
node* next;

};


//  Head of the linked list
node* head = nullptr;



//TODO: Getting order of arrangement from the user
//      Asks until it get a correct input
char getMode()
{
	string mode;

	cout << "Please enter the order mode (A/D): ";
	cin >> mode;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');

	if(mode == "A" || mode == "D")
	{
		if(mode == "A")
		{
			return 'A';
		}

		else{
			return 'D';
		}
	}

	else{
		bool flag = false;

		while(flag == false)
		{
			string newMode;
			cout << "Please enter the order mode again (A/D): ";
			cin >> newMode;
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			
			if(newMode == "A" || newMode == "D")
			{
				flag = true;
				return newMode[0];
			}
		}
	}
}

//END: Returns the order mode



//TODO: Gets input line from the user from the console
string getInput()
{

	string numbers;

	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers);

	return numbers;
}
//END: Returns a string with numbers



//TODO: Clears the rest of a linked list
void deleteRest(node* &ptr)
{
	node* temp = nullptr;
	while(ptr != nullptr)
	{
		temp = ptr->next;
		delete ptr;
		ptr = temp;
		delete temp;
	}
	delete temp;
}
//END: Not used parts are cleared



//TODO: Prints a linked list until the end of it
void printEOF(node* &ptr)
{
	while(ptr != nullptr)
	{
		cout << ptr->value << " ";
		ptr = ptr->next;
	}

	cout << endl;
}
//END: Linked list printed



//TODO: Arrange linked list in ascending order
//    : Adds number to the list if it is empty or it is bigger than other elements
//    : To add a smaller element than some of the inputs, delete bigger elements and adds to end of the file
void ascendingOrder(string number)
{
	cout << "Next number: " << number << endl;
	int num = atoi(number);
	if(head == nullptr)
	{
		cout << "Deleted nodes: None" << endl;
		cout << "Appended: " << num << endl;
		head = new node;
		head->value = num;
		head->next = nullptr;
	}

	else{
		if(num < head->value)
		{
			cout << "Deleted nodes: ";
			printEOF(head);
			deleteRest(head);

			cout << "Appended: " << num << endl;
			head = new node;
			head->value = num;
			head->next = nullptr;
		}

		else if(num > head->value){
			node* ptr = head;

			while((ptr->next != nullptr) && (num > ptr->next->value))
			{
				ptr = ptr->next;
			}

			if(ptr->next == nullptr)
			{
				cout << "Deleted nodes: None" << endl;
				cout << "Appended: " << num << endl;
				ptr->next = new node;
				ptr->next->value = num;
				ptr->next->next = nullptr;
			}

			else{
				if(ptr->next->value == num)
				{
					cout << num << " is already in the list!" << endl;
				}

				else{
					
					cout << "Deleted nodes: ";
					printEOF(ptr->next);
					deleteRest(ptr->next);

					cout << "Appended: " << num << endl;
					ptr->next = new node;
					ptr->next->value = num;
					ptr->next->next = nullptr;
				}
			}
		}

		else{
			cout << num << " is already in the list!" << endl;
		}
	}
	node* printPtr = head;
	cout << "List content: ";
	printEOF(printPtr);
}
//END: List is ordered and printed


//TODO: Arrange linked list in descending order
//    : Adds number to the list if it is empty or it is smaller than other elements
//    : To add a bigger element than some of the inputs, delete smaller elements and adds to end of the file
void descendingOrder(string number)
{
	cout << "Next number: " << number << endl;
	int num = atoi(number);
	if(head == nullptr)
	{
		cout << "Deleted nodes: None" << endl;
		cout << "Appended: " << num << endl;
		head = new node;
		head->value = num;
		head->next = nullptr;
	}

	else{
		if(num > head->value)
		{
			cout << "Deleted nodes: ";
			printEOF(head);
			deleteRest(head);

			cout << "Appended: " << num << endl;
			head = new node;
			head->value = num;
			head->next = nullptr;
		}

		else if(num < head->value){
			node* ptr = head;

			while((ptr->next != nullptr) && (num < ptr->next->value))
			{
				ptr = ptr->next;
			}

			if(ptr->next == nullptr)
			{
				cout << "Deleted nodes: None" << endl;
				cout << "Appended: " << num << endl;
				ptr->next = new node;
				ptr->next->value = num;
				ptr->next->next = nullptr;
			}

			else{
				if(ptr->next->value == num)
				{
					cout << num << " is already in the list!" << endl;
				}

				else{
					
					cout << "Deleted nodes: ";
					printEOF(ptr->next);
					deleteRest(ptr->next);

					cout << "Appended: " << num << endl;
					ptr->next = new node;
					ptr->next->value = num;
					ptr->next->next = nullptr;
				}
			}
		}

		else{
			cout << num << " is already in the list!" << endl;
		}
	}
	node* printPtr = head;
	cout << "List content: ";
	printEOF(printPtr);
}
//END: List is ordered and printed


//TODO: Gets input numbers and mode of order
//      Process list through ascendingOrder and descendingOrder functions
void processNumbers(string &numbers, const char &mode)
{
	istringstream nums(numbers);

	string number;

	if(mode == 'A')
	{
		while(nums >> number)
		{
			ascendingOrder(number);
			cout << endl;
			
		}
	}
	else if(mode == 'D')
	{
		while(nums >> number)
		{
			descendingOrder(number);
			cout << endl;
		}
	}

	node* ptr = head;
	
	if(numbers != "")
	{
		
		cout << "All the nodes are deleted at the end of the program: ";
		printEOF(ptr);
		cout << endl;
		
		deleteRest(ptr); //List cleared
		delete head;  
	}
}
//END: List processed and printed
//     Whole linked list is deleted


int main()
{
	char mode = getMode();

	string numbers = getInput();
	
	cout << endl;
	
	processNumbers(numbers, mode);

	if(numbers == "") //Checks empty input
	{
		cout << "The list is empty at the end of the program and nothing is deleted" << endl << endl;
	}

	return 0;
}

