//Muhammed Orhun Gale - 26754 
#ifndef PLAYER_H
#define PLAYER_H
#include "morhun_gale_muhammedOrhun_hw6_Board_Class.h"

template <class T>
class Player	 //All functions are done as described in the homework
{

private:
	int score;
	Board<T> & board;

public:
	Player(Board<T>&);
	
	T openCard(int, int);
	bool validMove(int, int);
	
	void increaseNumberOfSuccess();
	int getNumberOfSuccess() const;	

};

#include "morhun_gale_muhammedOrhun_hw6_Player_Class.cpp"
#endif