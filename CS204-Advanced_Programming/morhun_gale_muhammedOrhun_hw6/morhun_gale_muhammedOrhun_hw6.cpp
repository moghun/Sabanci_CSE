#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

#include "morhun_gale_muhammedOrhun_hw6_Board_Class.h"
#include "morhun_gale_muhammedOrhun_hw6_Player_Class.h"

template<class itemType>
void playGame(Board<itemType> &board, Player<itemType> players[2], ifstream & input)
{
	itemType openedCard1, openedCard2;

	board.readBoardFromFile(input); // initializes the board by reading values from the file

	//bool turnPlayer1 = true; // player1: true, player2: false
	bool continueGame = true;
	int i = 0;//i == 0 first player's turn, if i == 1 2nd player's turn 
	while(continueGame) // loops until the game finishes
	{
		system("cls");
		int row1, col1, row2, col2;

		
			cout<<"PLAYER "<< i+1 << " (Score: "<<players[i].getNumberOfSuccess()<<")"<<endl;

			board.displayBoard();

			// player enter row and column values to open the first card
			cout<<"\nEnter row and column of the first card "<<endl;
			cin>>row1>>col1;

			// player enters row and column values until they are valid
			while(!players[i].validMove(row1, col1))
			{
				cout << endl<<"The cell either is not valid or already opened"<<endl<<"Invalid move, try again!" << endl<<endl;
				cout<<"Enter row and column of the first card "<<endl;

				cin>>row1>>col1;
			}
			
			// open the card at the corresponding row and column
			openedCard1 = players[i].openCard(row1, col1);
			cout << endl;
			board.displayBoard();

			// player enter row and column values to open the second card
			cout<<"\nEnter row and column of the second card "<<endl;
			cin>>row2>>col2;

			while(!players[i].validMove(row2, col2))
			{
				cout << endl<<"The cell either is not valid or already opened"<<endl<<"Invalid move, try again!" << endl<<endl;
				cout<<"Enter row and column of the second card "<<endl;
				cin>>row2>>col2;
			}

			openedCard2 = players[i].openCard(row2, col2);
			cout << endl;
			board.displayBoard();

			// check whether cards are equal or not
			if(openedCard1 == openedCard2)
			{
				players[i].increaseNumberOfSuccess();
				cout<<"CORRECT! Current Score of Player " << i + 1<<" is "<< players[i].getNumberOfSuccess() << endl;
			}
			else
			{
				board.closeCard(row1, col1);
				board.closeCard(row2, col2);
				cout<<"WRONG CHOICE"<<endl;
			}
		
			
	

		cout<<"Press Enter to continue"<<endl;
		cin.get();
		cin.ignore(256,'\n');
		
		// check whether the game continues or finishes
		if((players[0].getNumberOfSuccess() + players[1].getNumberOfSuccess()) == (board.getRow() * board.getColumn()) / 2)
		{
			continueGame = false;
		}
		++i %= 2; //changing the turn
	}

}


int main()
{
	int rows, columns; // number of rows and columns of the board
	
	cout<<"********************************************"<<endl;
	cout<<"********************************************"<<endl;
	cout<<"**********   CARD MATCHING GAME   **********"<<endl;
	cout<<"********************************************"<<endl;
	cout<<"********************************************"<<endl<<endl;

	string fileName;
	cout << "Enter the input file name that contains integers" << endl;
	getline(cin, fileName); //get input file name from the user
	stringstream fileNameLine(fileName);
	fileNameLine >> fileName;
	ifstream input;
	input.open(fileName);
	cout << endl;

	while(!input.is_open()) // check whether the file is opened correctly. If not, repeat until the correct file name is provided
	{
		cout<< "Could not open the file " << fileName << endl;
		cout << "Enter the input file name that contains integers" << endl;
		getline(cin, fileName);
		stringstream fileNameLine2(fileName);
		fileNameLine2 >> fileName;
		input.open(fileName);
		cout << endl;
	}
	string line = "";
	getline(input,line);
	stringstream ss(line);
	ss >> rows >> columns;
	Board<int> board1(rows, columns); // create a new board object
	Player<int> intPlayers[2] = { Player<int>(board1), Player<int>(board1) };
	//Player<int> player1(board1); // create a new player object who plays on board1
	//Player<int> player2(board1); // create a new player object who plays on board2

	system("cls");
	
	playGame(board1, intPlayers, input); // start playing the game with the defined players and board
	board1.displayBoard();

	// conditions which determines the winner of the game
	if (intPlayers[0].getNumberOfSuccess() > intPlayers[1].getNumberOfSuccess())
		cout<<"Player 1 wins: "<< intPlayers[0].getNumberOfSuccess() <<" successful choice(s)"<<endl;
	else if (intPlayers[0].getNumberOfSuccess() < intPlayers[1].getNumberOfSuccess())
		cout<<"Player 2 wins: "<< intPlayers[1].getNumberOfSuccess() <<" successful choice(s)"<<endl;
	else
		cout<<"Draw: Both players have "<< intPlayers[0].getNumberOfSuccess() <<" successful choice(s)"<<endl;
	
	cout<<"Press Enter to continue"<<endl;
	cin.get();
	cin.ignore(256,'\n');

	system("cls");

	// The first game on integer board ends here
	// The following codes are written to play the game on a char board

	cout<<"********************************************"<<endl;
	cout<<"********************************************"<<endl;
	cout<<"**********   CARD MATCHING GAME   **********"<<endl;
	cout<<"********************************************"<<endl;
	cout<<"********************************************"<<endl<<endl;
	
	input.close();
	cout << "Enter the input file name that contains chars" << endl;
	getline(cin, fileName); //get input file name from the user
	stringstream fileNameLine3(fileName);
	fileNameLine3 >> fileName;
	input.open(fileName);
	cout << endl;
	while(!input.is_open()) // check whether the file is opened correctly. If not, repeat until the correct file name is provided
	{
		cout<< "Could not open the file " << fileName << endl;
		cout << "Enter the input file name that contains chars" << endl;
		getline(cin, fileName); 
		stringstream fileNameLine4(fileName);
		fileNameLine4 >> fileName;
		input.open(fileName);
		cout << endl;
	}

	line = "";
	getline(input,line);
	stringstream ss2(line);
	ss2 >> rows >> columns;
	
	Board<char> board2(rows, columns);
	Player<char> charPlayers[2] = { Player<char>(board2), Player<char>(board2)};
	//Player<char> player3(board2);
	//Player<char> player4(board2);
	
	system("cls");

	playGame(board2, charPlayers,input);

	board2.displayBoard();

	if (charPlayers[0].getNumberOfSuccess() > charPlayers[1].getNumberOfSuccess())
		cout<<"Player 1 wins: "<< charPlayers[0].getNumberOfSuccess() <<" successful choice(s)"<<endl;
	else if (charPlayers[0].getNumberOfSuccess() < charPlayers[1].getNumberOfSuccess())
		cout<<"Player 2 wins: "<< charPlayers[1].getNumberOfSuccess() <<" successful choice(s)"<<endl;
	else
		cout<<"Draw: Both players have "<< charPlayers[0].getNumberOfSuccess() <<" successful choice(s)"<<endl<<endl;
	
	cout<<"Press Enter to continue"<<endl;
	cin.get();
	cin.ignore(256,'\n');
	return 0;
}

