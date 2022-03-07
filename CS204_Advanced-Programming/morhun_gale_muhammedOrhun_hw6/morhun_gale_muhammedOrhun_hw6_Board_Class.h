//Muhammed Orhun Gale - 26754 
#ifndef BOARD_H
#define BOARD_H

template <class T>
class Board		 //Different functions other than mentioned in the homework are indicated
{
private:
	int row;
	int col;
	T** matrixAccsess;
	char** statusMatrix;  //Matrix that is used to hold the card status

public:
	Board();
	Board(int, int);
	~Board();

	void readBoardFromFile(std::ifstream &); 
	void displayBoard();
	void closeCard(int&, int&);
	void opensCard(int&, int&); //A mutator to change the status of a card

	T getCard(int&, int&) const; //An accessor to pass the information on a card
	int getRow() const;
	int getColumn() const;
	char getStatus(int&,int&) const; //An accessor to pass the status of a card
	
};

#include "morhun_gale_muhammedOrhun_hw6_Board_Class.cpp"
#endif