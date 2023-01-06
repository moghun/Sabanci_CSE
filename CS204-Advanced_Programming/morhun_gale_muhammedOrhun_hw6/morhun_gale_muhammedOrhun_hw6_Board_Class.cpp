//Muhammed Orhun Gale - 26754 
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "morhun_gale_muhammedOrhun_hw6_Board_Class.h"
using namespace std;


//TODO: Default constructor
template <class T>
Board<T>::Board()
{
	row = 0;
	col = 0;
	matrixAccsess = nullptr;
	statusMatrix = nullptr;
}
//END:  Board object is constructed


//TODO: Parametric constructor
template <class T>
Board<T>::Board(int r, int c)
{
	row = r;
	col = c;
	
	matrixAccsess = new T*[row];
	statusMatrix = new char*[row];

	for(int i = 0; i < row; i++)
	{
		matrixAccsess[i] = new T[col];
		statusMatrix[i] = new char[col];
	}
}
//END:  Board object is constructed with statusMatrix and informationMatrix



//TODO: Destructor 
template <class T>
Board<T>::~Board()
{
	for(int i = 0; i < row; i++)
	{
		delete [] statusMatrix[i];	
		delete [] matrixAccsess[i];

	}
	delete [] matrixAccsess;
	delete [] statusMatrix;
	
	row = 0;
	col = 0;
	matrixAccsess = nullptr;
	statusMatrix = nullptr;
}
//END:  Object is destructed and dynamically allocated memory is freed


//TODO: Transfer file includings to the information matrix
template <class T>
void Board<T>::readBoardFromFile(ifstream& input)
{
	for(int i = 0; i < row; i++)
	{
		int j = 0;
		T temp;
		while(col > j && input >> temp)
		{
			matrixAccsess[i][j] = temp;
			statusMatrix[i][j] = 'c';
			j++;
		}
	}
}
//END:  File content is transfered to the information matrix and 


//TODO: Display the current status of the board
template <class T>
void Board<T>::displayBoard()
{
	cout << endl;
	for(int i=0; i < row; i++)
	{
		for(int j =0; j < col; j++)
		{
			
			if(statusMatrix[i][j] == 'c')
			{
				cout << 'X' << " ";

			}

			else{
				cout << matrixAccsess[i][j] << " ";
			}
		}
		cout << endl;
	}
}
//END:  Current status of the board is displayed


//TODO: Update status of a card to close
template <class T>
void Board<T>::closeCard(int &rowLoc, int &colLoc)
{
	statusMatrix[rowLoc][colLoc] = 'c';
}
//END:  Status of a card is changed to close

//TODO: Update status of a card to open
template <class T>
void Board<T>::opensCard(int &rowLoc, int &colLoc)
{
	statusMatrix[rowLoc][colLoc]  = 'o';
}
//END:  Status of a card is changed to open

//TODO: Return the info on the card
template <class T>
T Board<T>::getCard(int &rowLoc, int &colLoc) const
{
	return matrixAccsess[rowLoc][colLoc] ;
}
//END:  Card info returned


//TODO: Return board's row count
template <class T>
int Board<T>::getRow() const
{
	return this->row;
}
//END:  Row count returned

//TODO: Return board's column count
template <class T>
int Board<T>::getColumn() const
{
	return this->col;
}
//END:  Column count returned


//TODO: Return a card's status
template <class T>
char Board<T>::getStatus(int &rowLoc, int &colLoc) const
{
	return statusMatrix[rowLoc][colLoc] ;
}
//END:  Card status returned