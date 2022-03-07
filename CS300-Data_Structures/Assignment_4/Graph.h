//Muhammed Orhun Gale - 26754

/*
	* A graph class that creates a graph from given word database
	* Represents graph via using adjacency list representation
	* Creates graph right at the beginning, uses Breadth First Search to find operation sequence
	* Precomputation process of graph is optimized via not computing the insertions seperate
						  from deletions since a word that is decided via deleting a charachter from another word is 
															able to recompute first word via inserting the deleted charachter  
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include <unordered_map>
#include <queue>

#define SENTINEL_VALUE "ALERT SENTINEL VALUE \nSENTINEL VALUE ALERT" //Sentinel value that indicates a "path" is ended

using namespace std;

//Struct that represents Edges on a graph
//Stores information of the operations that leads to creation of the particular edge
struct Edge 
{
	string path;		//Indicates the destionation of the edge	
	char operation;		//Operation that used to leads this path(edge)
	char charachter;	//Charachter that is adjusted to find the path
	unsigned short int position; //Position of the charachter which was altered
	char changedCh;		//Only for the 'Change' operation - stores the changed charachter 
};

//Struct that represents Vertices on a graph
//Stores defining variables and variables that helps to operate Breadth First Search (BFS)
struct Vertex
{
	string key;		//Name of the vertex
	vector<Edge>* adj_list;	//Adjacency list that stores information of the vertex's edges
	bool known;		//Indicates that the vertex is visited if it is true - to operate BFS
	int dist;		//Indicates the current distance from the start node - to operate BFS
	string path;	//Indicates next vertex on the found shortest path 
};

//Class that represents a fully established Graph
class Graph
{
public:

	Graph();			//Default constructor
	Graph(ifstream&);	//Parametric constructor
	
	void search(const string&, const string&);	//Searches for the shortest path between given words - Uses BFS
	void resetSearch();							//Resets BFS variables in vertices for next searches
	void printPath(const string&, const string&); //Prints the shortest path (operations that leads to the transformation)
	bool inList(const string&, const string&);  //Checks whether input words are in the database or not

private:
	unordered_map<string, Vertex*> table;	//Hash table that represents the graph via storing vertices
	vector<string*> wordList;				//Vector that stores words in the database

	void createDictionary(ifstream&);		//Reads and saves each word in the database to wordList and table
	void createGraph();						//Creates graph via determining possible edges
	void initilizeEdge(Edge*&, const string&, const char, const char&, const unsigned short int&, const char&);	//Initilizes edges according to the giving operation
	void backtrack(const string&, vector<string*>&); //Tracks the path to print it
};

#endif