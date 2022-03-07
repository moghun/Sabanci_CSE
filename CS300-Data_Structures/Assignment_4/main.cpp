//Muhammed Orhun Gale - 26754
#include "Graph.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream file;  //Get external database
	file.open("words.txt");

	Graph wordGraph(file);	//Create a graph out of given words
	
	//Get two words that will be transformed
	string a;
	string b;

	cout << endl << "********************************************************************************************************************" << endl;
	cout << "Welcome to word transformation program" << endl;
	cout << "Please enter words you want to transform from - to with a space between them" << endl << endl;
	do {
		
		cout << "Inputs: ";
		cin >> a >> b;
		cout << "------------------------------" << endl;

		bool inList = wordGraph.inList(a, b);	//Check if input words are in the database
		if (a[0] != '*' && inList == true)		//If they are in the database and exit command did not given
		{
			
			cout << "Transformation result: " << endl << endl;
			cout << a << endl;
			
			wordGraph.search(a, b);				//Decide shortest path
			wordGraph.printPath(b, a);			//Print the operation order

			wordGraph.resetSearch();			//Reset BFS variables for next transformation
			a = ""; b = "";
			cout << "------------------------------" << endl << endl;
		}

		else if(a[0] != '*' && inList == false){	//If at least one word is not in the database
			cout <<"------------------------------" << endl << endl;
		}

		else {		//If termination command is given, terminate the program
			cout << endl << "*PROGRAM TERMINATES*" << endl;

			cout << "********************************************************************************************************************" << endl << endl;
		}

		cout << endl;
	} while (a[0] != '*');

	file.close(); //Close the database
	return 0;
}