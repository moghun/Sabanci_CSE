/* Muhammed Orhun Gale - 26754 - morhun*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "morhun_gale_muhammedOrhun_hw1_strutils.h"

//TODO: A struct for keep tidy each line's information
struct infHold {
	string info;
	int rw;
	int cl;
	string cell;
	string rot;
};


//TODO: Extract the information of each line of the text file and create a matrix to hold it.
//      Invastigate user and file sourced errors and give appropriate error message
bool getInfo(vector<infHold> &infoMatrix, int &rows, int &cols)
{
	string fName;
	cout << "Please enter the name of the file: ";
	cin >> fName;
	
	ifstream inFile;
	inFile.open(fName.c_str());

	while(inFile.fail())
	{
		string nFName;
		cout << "File name is incorrect, please enter again: ";
		cin >> nFName;
		inFile.open(nFName.c_str());
	}

	string line;
	int lineCount = 0;
	vector<infHold> tempMatrix;
	while(getline(inFile, line))
	{
		lineCount++;
		if(lineCount == 1)
		{
			char ch;
			istringstream nums(line);
			int numCount = 0;
			string mRow = "";
			string mCol = "";
			while(nums.get(ch))
			{
				if(ch != ' ' && numCount == 0)
				{
					mRow += ch; 
				}
				else if(ch != ' ' && numCount != 0)
				{
					mCol += ch;
				}
				else if(ch == ' ')
				{
					numCount++;
				}
			}
			int nRow = atoi(mRow);
			int nCol = atoi(mCol);

			if(nRow < 1 || nCol < 1)
			{
				cout << "Invalid number for row and/or column!" << endl;
				return false;                                           //Displays an error in main function
			}

			else{
				rows = nRow;
				cols = nCol;
			}
		}
		else{
			infHold wordObject;

			istringstream words(line);
			string word;
			int infCount = 0;
			bool flag = true;
			bool startPointChecker = true;
			bool falseFiveChecker = true;
			string falseStarting = "";

			while(words >> word && flag == true)
			{
				infCount++;
				if(infCount == 1)
				{
					wordObject.info = word;
				}

				else if(infCount == 2)
				{
					int numRow = atoi(word);
					if(!(numRow < 0 || numRow >= rows))
					{
						wordObject.rw = atoi(word);
						falseStarting += word;
					}
					else{
						startPointChecker = false;
						falseStarting += word;

					}
				}
				
				else if(infCount == 3)
				{
					int numCol = atoi(word);
					if(!(numCol < 0 || numCol >= cols))
					{
						wordObject.cl = atoi(word);
						if(startPointChecker == false)
						{
							falseStarting = falseStarting + " " + word;
							cout << "Starting point is out of range! Point: " << falseStarting << endl;
							infCount--;
							falseFiveChecker = false;
							break;
						}						
					}

					else{
						startPointChecker = false;
						flag = false;
						if(startPointChecker == false)
						{
							falseStarting = falseStarting + " " + word;
							cout << "Starting point is out of range! Point: " << falseStarting << endl;
							falseFiveChecker = false;
						}
					}
				}

				else if(infCount == 4)
				{
					if(word == "r" || word == "l" || word == "u" || word == "d")
					{
						wordObject.cell = word;
					}

					else{
						cout << "Invalid input for direction! Direction: " << word << endl; 
						flag = false;
						falseFiveChecker = false;
					}
				}

				else if (infCount == 5)
				{
					if(word == "CW" || word == "CCW")
					{
						wordObject.rot = word;
					}

					else{
						cout << "Invalid input for orientation! Orientation: " << word << endl;
						flag = false;
						falseFiveChecker = false;
						infCount--;
					}
				}
			}
			
			if(infCount != 5 && falseFiveChecker == true)
			{
				cout << "Invalid line! Number of values is different than 5." << endl;
			}

			else if(infCount == 5) 
			{
				tempMatrix.push_back(wordObject);
				infoMatrix = tempMatrix;
			}
		}
	}
	inFile.close();
	return true;
}
//END: An information matrix is created - error messages given - board size information passed by refference parameter



//TODO: Create the board matrix
vector<vector<char> > createBoard(const int rows, const int cols)
{
	vector<vector<char> > board(rows, vector<char> (cols, '-'));
	return board;
}
//END: Board created



//TODO: Extract each charachter of the word that will be placed
vector<char> getInfoLetters(string info)
{
	int length = info.length();
	vector<char> charVector(length);

	for(int i = 0; i < info.length(); i++)
	{
		charVector[i] = info[i];
	}

	return charVector;
}
//END: A matrix with charachters of the word is created



//TODO: Try to place the first element of the given word to the board
bool putFirstLetter(vector<vector<char> > &board, char letter, int firstRow, int firstCol)
{
	char checkCh = board[firstRow][firstCol];

	if(checkCh != '-')
	{
		return false; //Error: Cannot be placed - displayed in the solver
		
	}

	else{
		board[firstRow][firstCol] = letter;
		return true; //Placed
		
	}
}
//END: True: First element is placed to the board and information passed by refference
//    False: Error displayed and passed to the next line




//TODO: Print board for the user
void printBoard(const vector<vector<char> > &board)
{
	for(int i = 0; i < board.size(); i++)
	{
		for(int j = 0; j < board[0].size(); j++)
		{
			cout << "  " << board[i][j] << "   ";
		}
		cout << endl << endl;
	}
}
//END: Board printed



//TODO: Place next letters of the given word
//   First: Put to first cell in given direction - If fails do second
//  Second: Rotate direction according to the given information
//  Output= cell that is finally proceeded as {r, d, l, u} - If fails {e} and proceed to the next line
char putNextLetter(vector<vector<char> > &board , int currentRow, int currentCol, char cell, string rot, char letter)
{   
	if(rot == "CW")	
	{
		if(cell == 'r')
		{
			if(currentCol + 1 < board[0].size())             
			{
				if(board[currentRow][currentCol+1] == '-')		
				{
					board[currentRow][currentCol+1] = letter;
					return 'r'; //Right
				}
			}
			
			if(currentRow + 1 < board.size())
			{
				if(board[currentRow+1][currentCol] == '-')
				{
					board[currentRow+1][currentCol] = letter;
					return 'd'; //Down
				}
			}
			
			if(currentCol - 1 >= 0)
			{
				if(board[currentRow][currentCol-1] == '-')
				{
					board[currentRow][currentCol-1] = letter;
					return 'l'; //Left
				}
			}
			
			if(currentRow - 1 >= 0)
			{
				if(board[currentRow-1][currentCol] == '-')
				{
					board[currentRow-1][currentCol] = letter;
					return 'u'; //Up
				}
			}
			return 'e';
		
		}
	
	
		else if(cell == 'l')
		{
		
			if(currentCol - 1 >= 0)
			{
				if(board[currentRow][currentCol-1] == '-')
				{
					board[currentRow][currentCol-1] = letter;
					return 'l';
				}
			}		
		
			if(currentRow - 1 >= 0)
			{
				if(board[currentRow-1][currentCol] == '-')
				{
					board[currentRow-1][currentCol] = letter;
					return 'u';
				}
			}
		
			if(currentCol + 1 < board[0].size())
			{
				if(board[currentRow][currentCol+1] == '-')
				{
					board[currentRow][currentCol+1] = letter;
					return 'r';
				}
			}
			
			
			if(currentRow + 1 < board.size())
			{
				if(board[currentRow+1][currentCol] == '-')
				{
					board[currentRow+1][currentCol] = letter;
					return 'd';
				}
			}
			return 'e';
		}
		
		
		else if(cell == 'd')
		{

			if(currentRow + 1 < board.size())
			{
				if(board[currentRow+1][currentCol] == '-')
				{
					board[currentRow+1][currentCol] = letter;
					return 'd';
				}
			}			
			
			if(currentCol - 1 >= 0)
			{
				if(board[currentRow][currentCol-1] == '-')
				{
					board[currentRow][currentCol-1] = letter;
					return 'l';
				}
			}			

			if(currentRow - 1 >= 0)
			{
				if(board[currentRow-1][currentCol] == '-')
				{
					board[currentRow-1][currentCol] = letter;
					return 'u';
				}
			}
			
			if(currentCol + 1 < board[0].size())
			{
				if(board[currentRow][currentCol+1] == '-')
				{
					board[currentRow][currentCol+1] = letter;
					return 'r';
				}
			}			
			return 'e';
		}		
		
		
		else if(cell == 'u')
		{

			if(currentRow - 1 >= 0)
			{
				if(board[currentRow-1][currentCol] == '-')
				{
					board[currentRow-1][currentCol] = letter;
					return 'u';
				}
			}		
		
			if(currentCol + 1 < board[0].size())
			{
				if(board[currentRow][currentCol+1] == '-')
				{
					board[currentRow][currentCol+1] = letter;
					return 'r';
				}
			}

			if(currentRow + 1 < board.size())
			{
				if(board[currentRow+1][currentCol] == '-')
				{
					board[currentRow+1][currentCol] = letter;
					return 'd';
				}
			}

			if(currentCol - 1 >= 0)
			{
				if(board[currentRow][currentCol-1] == '-')
				{
					board[currentRow][currentCol-1] = letter;
					return 'l';
				}
			}
			
			return 'e';
		}
	}	
	
	
	else if(rot == "CCW")
	{
	
		if(cell == 'r')
		{
			if(currentCol + 1 < board[0].size())
			{
				if(board[currentRow][currentCol+1] == '-')
				{
					board[currentRow][currentCol+1] = letter;
					return 'r';
				}
			}
			
			if(currentRow - 1 >= 0)
			{
				if(board[currentRow-1][currentCol] == '-')
				{
					board[currentRow-1][currentCol] = letter;
					return 'u';
				}
			}			
			
			if(currentCol - 1 >= 0)
			{
				if(board[currentRow][currentCol-1] == '-')
				{
					board[currentRow][currentCol-1] = letter;
					return 'l';
				}
			}			
			
			if(currentRow + 1 < board.size())
			{
				if(board[currentRow+1][currentCol] == '-')
				{
					board[currentRow+1][currentCol] = letter;
					return 'd';
				}
			}			
			
			return 'e';
		}
		
		
		else if(cell == 'l')
		{
		
			if(currentCol - 1 >= 0)
			{
				if(board[currentRow][currentCol-1] == '-')
				{
					board[currentRow][currentCol-1] = letter;
					return 'l';
				}
			}		
		
			if(currentRow + 1 < board.size())
			{
				if(board[currentRow+1][currentCol] == '-')
				{
					board[currentRow+1][currentCol] = letter;
					return 'd';
				}
			}		
		
			if(currentCol + 1 < board[0].size())
			{
				if(board[currentRow][currentCol+1] == '-')
				{
					board[currentRow][currentCol+1] = letter;
					return 'r';
				}
			}		
		
			if(currentRow - 1 >= 0)
			{
				if(board[currentRow-1][currentCol] == '-')
				{
					board[currentRow-1][currentCol] = letter;
					return 'u';
				}
			}
			return 'e';
		}
		
		
		else if(cell == 'd')
		{
		
			if(currentRow + 1 < board.size())
			{
				if(board[currentRow+1][currentCol] == '-')
				{
					board[currentRow+1][currentCol] = letter;
					return 'd';
				}
			}		
		
			if(currentCol + 1 < board[0].size())
			{
				if(board[currentRow][currentCol+1] == '-')
				{
					board[currentRow][currentCol+1] = letter;
					return 'r';
				}
			}			

			
			if(currentRow - 1 >= 0)
			{
				if(board[currentRow-1][currentCol] == '-')
				{
					board[currentRow-1][currentCol] = letter;
					return 'u';
				}
			}			
			
			if(currentCol - 1 >= 0)
			{
				if(board[currentRow][currentCol-1] == '-')
				{
					board[currentRow][currentCol-1] = letter;
					return 'l';
				}
				
			}			
			
			return 'e';
		}
		
		else if(cell == 'u')
		{
		
			if(currentRow - 1 >= 0)
			{
				if(board[currentRow-1][currentCol] == '-')
				{
					board[currentRow-1][currentCol] = letter;
					return 'u';
				}
			}		
	
			if(currentCol - 1 >= 0)
			{
				if(board[currentRow][currentCol-1] == '-')
				{
					board[currentRow][currentCol-1] = letter;
					return 'l';
				}
			}	

			if(currentRow + 1 < board.size())
			{
				if(board[currentRow+1][currentCol] == '-')
				{
					board[currentRow+1][currentCol] = letter;
					return 'd';
				}
			}
	
	
			if(currentCol + 1 < board[0].size())
			{
				if(board[currentRow][currentCol+1] == '-')
				{
					board[currentRow][currentCol+1] = letter;
					return 'r';
				}
			}
			return 'e';
		}
	}

	return 'e';
}
//END: Given letter is placed according to the information - board status passed by refferance
//     Next position that will be checked given by outputs



//TODO: Process the information matrix
//      Run putFirstLetter & putNextLetter to get the solution
//      Give placement errors
void solver(const vector<infHold> &infoMatrix, const int &boardRows, const int &boardCols)
{
    vector<vector<char> > board = createBoard(boardRows, boardCols);
	
	for(int k = 0; k < infoMatrix.size(); k++)
	{
		infHold word = infoMatrix[k];
		string rot = word.rot;
		char cell = (word.cell)[0];
		int currentRow = word.rw;
		int currentCol = word.cl;

		vector<char> chars = getInfoLetters(word.info);

		vector<vector<char> > temp = board;

		bool firstLetterCond = putFirstLetter(board, chars[0], currentRow, currentCol);
		cout << endl;

		if(firstLetterCond == false)
		{
			cout << "\"" << word.info << "\" could not be put into the matrix with given starting point: " << word.rw << "," << word.cl << "   direction: " << word.cell << "   orientation: " << word.rot << endl;
		}

		else{

			bool printFlag = true;
			char ogoDirection = ' ';

			for(int i = 1; i < chars.size() && ogoDirection != 'e'; i++)
			{
				char letter = chars[i];
				
				ogoDirection = putNextLetter(board, currentRow, currentCol, cell, rot, letter);
				
				if(ogoDirection == 'r')
				{
					currentCol++;
				}

				else if(ogoDirection == 'd')
				{
					currentRow++;
				}

				else if(ogoDirection == 'l')
				{
					currentCol--;
				}

				else if(ogoDirection == 'u')
				{
					currentRow--;
				}

				else if(ogoDirection == 'e')
				{
					board = temp;
					printFlag = false;
					cout << "\"" << word.info << "\" could not be put into the matrix with given starting point: " << word.rw << "," << word.cl << "   direction: " << word.cell << "   orientation: " << word.rot << endl << endl;
				}
			}

			if(printFlag == true)
			{
				cout << "\"" << word.info << "\" was put into the matrix with given starting point: " << word.rw << "," << word.cl << "   direction: " << word.cell << "   orientation: " << word.rot << endl;
			}
		}
		printBoard(board);
	}
}
//END: Process of the solution and solved board is displayed
//     Placement errors gived



int main()
{
	vector<infHold> infoMatrix;
	int rows;
	int cols;
	bool isInfoCorrect = getInfo(infoMatrix, rows, cols);

	if(isInfoCorrect == false)
	{
		cout << endl;
		return 0; //Exit due to invalid board size informations
	}

	solver(infoMatrix, rows, cols);

	return 0;
}
