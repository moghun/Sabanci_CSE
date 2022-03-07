//Muhammed Orhun Gale - 26754 - Homework 4

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "morhun_gale_muhammedOrhun_hw4_myClass.h"

using namespace std;

//TODO: Get matrix information from user
//      Get file information from user and open it
//      Creat a cellStruct matrix to hold flag/binary information  
cellStruct** getMatrix(	int &rows, int &cols)
{
	string fName;
	cout << "Please enter the number of rows: ";
	cin >> rows;
	cout << "Please enter the number of columns: ";
	cin >> cols;
	cout << "Please enter the name of the input file that contains the matrix: ";
	cin >> fName;
	
	ifstream inFile;
	inFile.open(fName.c_str());

	while(inFile.fail())
	{
		string nFName;
		cout << "File cannot be opened." << endl;
		cout << "File name is incorrect, please enter again: ";
		cin >> nFName;
		inFile.open(nFName.c_str());
	}

	cellStruct** matrix;
	matrix = new cellStruct*[rows];

	string line;
	int i = 0;
	while(getline(inFile, line))
	{
		matrix[i] = new cellStruct[cols];
		for(int j = 0; j < cols; j++)
		{
			cellStruct element;
			element.bin = line[j];
			element.x = i;
			element.y = j;
			matrix[i][j] = element;
		}
		i++;
	}

	inFile.close();
	return matrix;
}
//END: File read - Matrix created 


//TODO: Search input by using the algorithm that is given by the homework
void search(cellStruct** tempMatrix, string &input, const int &rows, const int &cols)
{

	if(input[0] != tempMatrix[0][0].bin) 
	{
		tempMatrix[0][0].flag = true;
	}

	
	cellStruct currentElement = tempMatrix[0][0]; 
	
	Stack stack;  //Stack which will be used for holding elements
	
	int strCounter = 0;
	string foundStr = "";

	while((input != foundStr) && tempMatrix[0][0].flag == false)
	{
		if(tempMatrix[currentElement.x][currentElement.y].flag == false && currentElement.bin == input[strCounter])
		{
			stack.push(currentElement);
			foundStr += currentElement.bin;
			
			if((input == foundStr))
			{
				break;
			}

			else{
				int xCoord = currentElement.x;
				int yCoord = currentElement.y;
				strCounter++;

				//Algorithm is selected as firstly the one "down" of the current position be checked

				if(xCoord+1 != rows && tempMatrix[xCoord+1][yCoord].flag == false && tempMatrix[xCoord+1][yCoord].bin == input[strCounter])
				{
					currentElement = tempMatrix[xCoord+1][yCoord];
				}

				else if(yCoord+1 != cols && tempMatrix[xCoord][yCoord+1].flag == false && tempMatrix[xCoord][yCoord+1].bin == input[strCounter])
				{
					currentElement = tempMatrix[xCoord][yCoord+1];
					
				}

				else{
					tempMatrix[currentElement.x][currentElement.y].flag = true;
					cellStruct newElement;
					stack.pop(newElement);
					if (!stack.isEmpty()) 
					{	
						stack.pop(newElement);
					}
					else {
					}
					currentElement = newElement;
					foundStr = foundStr.substr(0,foundStr.length()-2);  //Since currently searched char is not changed took back the changes
					strCounter -= 2;
				}
			}
		}

		else if((tempMatrix[currentElement.x][currentElement.y].flag == true) || (currentElement.bin != input[strCounter]))
		{
			tempMatrix[currentElement.x][currentElement.y].flag = true;
			cellStruct newElement;
			stack.pop(newElement);
			if (stack.isEmpty()) {
						
			}
			else {
				stack.pop(newElement);
				tempMatrix[newElement.x][newElement.y].flag = true;
				if (!stack.isEmpty()) 
				{
					stack.pop(newElement);
				}
			}
			currentElement = newElement;
			foundStr = foundStr.substr(0,foundStr.length()-2); //Since currently searched char is not changed took back the changes
			strCounter -= 2;
		}
	}


	if(tempMatrix[0][0].flag == true) //No path exist
	{
		cout << "The bit string " << input <<" could not be found." << endl;
	
		for(int m = 0; m < rows; m++) //Convert all flags back to false to further searches
		{
			for(int n = 0; n < rows; n++)
			{
				tempMatrix[m][n].flag = false;
			}
		}
	}

	else{  //There exist a path

		cout << "The bit string " << input <<" is found following these cells:" << endl;

		Stack stack2;  //Stack which will be used for printing
		while(stack.isEmpty() == false)
		{
			cellStruct cell;
			stack.pop(cell);
			stack2.push(cell);
		}
		
		while(stack2.isEmpty() == false) //Prints the path
		{
			cellStruct cell2;
			stack2.pop(cell2);
			cout << "("<<cell2.x << "," << cell2.y << ")" << "  ";

		}
		cout << endl;
	}	
}
//END: Path found and printed / Path cannot be found and told to the user


//TODO: Deletes the matrix in spite of memory leaks
void deleteMatrix(cellStruct** &matrix, int &rows, int &cols)
{
	for(int i = 0; i < rows; i++)
	{
		delete matrix[i];
	}
	delete matrix;
}
//END: Matrix is deleted

int main()
{
	int rows;
	int cols;
	
	cellStruct** matrix = getMatrix(rows, cols); //Matrix created
	cellStruct** temp = matrix; //Matrix information is stored for a possible update

	bool flag = true;

	while(flag == true)
	{
		cout <<"Please enter a string of bits to search (CTRL+Z to quit): ";
		string input;
		cin >> input;

		if(!cin.eof()) //If the input is not ^Z 
		{
			search(matrix, input, rows, cols);
			cout << "---------------------------------------------------------" << endl;
			matrix = temp; //Matrix is restored to its first condition
		}

		else{
			flag = false;
			deleteMatrix(matrix, rows, cols);
			cout << endl << "Program ended successfully!" << endl << endl;
		}
		cin.clear();
	}

	return 0;
}























/*
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Header.h"

using namespace std;


cellStruct** getMatrix(	int &rows, int &cols)
{
	string fName;
	cout << "Please enter the number of rows: ";
	cin >> rows;
	cout << "Please enter the number of columns: ";
	cin >> cols;
	cout << "Please enter the name of the input file that contains the matrix: ";
	cin >> fName;
	
	ifstream inFile;
	inFile.open(fName.c_str());

	while(inFile.fail())
	{
		string nFName;
		cout << "File cannot be opened." << endl;
		cout << "File name is incorrect, please enter again: ";
		cin >> nFName;
		inFile.open(nFName.c_str());
	}

	cellStruct** matrix;
	matrix = new cellStruct*[rows];

	string line;
	int i = 0;
	while(getline(inFile, line))
	{
		matrix[i] = new cellStruct[cols];
		for(int j = 0; j < cols; j++)
		{
			cellStruct element;
			element.bin = line[j];
			element.x = i;
			element.y = j;
			matrix[i][j] = element;
		}
		i++;
	}

	inFile.close();
	return matrix;
}


string getInput()
{
	string input;
	cout <<"Please enter a string of bits to search (CTRL+Z to quit): ";
	cin >> input;

	return input;
}


bool isFound(string searched, string current)
{
	return searched == current;
}

void search(cellStruct** &matrix, string &input, const int &rows, const int &cols)
{
	cellStruct** tempMatrix = matrix;

	if(input[0] != tempMatrix[0][0].bin)
	{
		cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << endl;
		tempMatrix[0][0].flag = true;
	}

	
	cellStruct currentElement = tempMatrix[0][0]; 
	
	Stack stack;
	
	int strCounter = 0;
	string foundStr = "";

	while((input != foundStr) && tempMatrix[0][0].flag == false)
	{
		if(currentElement.flag == false && currentElement.bin == input[strCounter])
		{
			stack.push(currentElement);
			foundStr += currentElement.bin;
			
			if((input == foundStr))
			{
				cout << "bbbbbbbbbbbbbbbbbbbbbbbbbb " << endl;
				break;
			}

			else{
				int xCoord = currentElement.x;
				int yCoord = currentElement.y;
				strCounter++;

				if(xCoord+1 != rows && tempMatrix[xCoord+1][yCoord].flag == false && tempMatrix[xCoord+1][yCoord].bin == input[strCounter])
				{
					currentElement = tempMatrix[xCoord+1][yCoord];
					cout << "35 ";
				}

				else if(yCoord+1 != cols && tempMatrix[xCoord][yCoord+1].flag == false && tempMatrix[xCoord][yCoord+1].bin == input[strCounter])
				{
					currentElement = tempMatrix[xCoord][yCoord+1];
					cout << "67 ";
				}

				else{
					if(stack.isEmpty() == true)
					{
						currentElement.flag = true;
					}

					else{
						currentElement.flag = true;
						foundStr.substr(0,foundStr.length()-1);
						stack.pop(currentElement);
						cout << "99 ";
					}
				}
			}
		}

		else if((currentElement.flag == true) || (currentElement.bin != input[strCounter]))
		{
			currentElement.flag = true;
			stack.pop(currentElement);
			cout << "71 ";
		}
	}


	if(tempMatrix[0][0].flag == true)
	{
		cout << "ERROR" << endl;
	}

	else{

		Stack stack2;
		while(stack.isEmpty() == false)
		{
			cellStruct cell;
			stack.pop(cell);
			stack2.push(cell);
		}
		
		while(stack2.isEmpty() == false)
		{
			cellStruct cell2;
			stack2.pop(cell2);
			cout << "("<<cell2.x << "," << cell2.y << ")" << endl;

		}
	}	
}



int main()
{
	int rows;
	int cols;
	cellStruct** matrix = getMatrix(rows, cols);

	cellStruct** temp = matrix;

	string input = getInput();

	cout << input << endl << endl;

	search(matrix, input, rows, cols);


	return 0;
}

*/