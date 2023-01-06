//Muhammed Orhun Gale - 26754 
#include <iostream>
#include "morhun_gale_muhammedOrhun_hw6_Player_Class.h"

using namespace std;

//TODO: Parametric constructor
template <class T>
Player<T>::Player(Board<T>& b)
	:score(0), board(b)
{}
//END:  Player object is constructed with referenced board object


//TODO: Evaluates a move is valid or not according to the board sizes and card status
template <class T>
bool Player<T>::validMove(int row, int col)
{
	if(!(0 <= row && row < board.getRow()) || !(0 <= col && col < board.getColumn()))
	{
		return false;
	}

	else{
		char status = board.getStatus(row, col);

		if(status == 'o')
		{
			return false;
		}

		if(status == 'c')
		{
			return true;
		}
	}
}
//END:  Validness of the move is returned



//TODO: Change a card's status to open by updating the status matrix in the board object
template <class T>
T Player<T>::openCard(int row, int col)
{
	board.opensCard(row, col);
	return board.getCard(row, col);
}
//END:  Card's status is updated


//TODO: Increase player's score
template <class T>
void Player<T>::increaseNumberOfSuccess()
{
	score++;
}
//END:  Player's score is increased



//TODO: Returns score of a player
template <class T>
int Player<T>::getNumberOfSuccess() const
{
	return score;
}
//END:  Score information is returned
