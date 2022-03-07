//Muhammed Orhun Gale - 26754
#include "Graph.h"

//TODO:	Default constructor for Graph class
Graph::Graph()
{

	//Initilize variables
	unordered_map<string, Vertex*> map;
	vector<string*> words;

	this->table = map;
	this->wordList = words;
}
//END:	Private variables are initilized with empty objects

//TODO:	Parametric constructor for Graph class
//		Takes ifstream variable from the user to turn it into a graph
Graph::Graph(ifstream& file)
{
	//Initilize variables
	unordered_map<string, Vertex*> map;
	vector<string*> words;
	this->wordList = words;
	this->table = map;

	//Set them properly via using private member functions provided
	createDictionary(file);
	createGraph();
}
//END:	Graph representation of the given database of words is established


//TODO:	Searches the shortest path between given two words via using Breadth First Search strategy
void Graph::search(const string& word1, const string& word2)
{
	queue<Vertex*> Queue;	//Create a queue to keep track of vertices that are on the same amount of distance from the starting point 
	Vertex *v, *w;
	Queue.push(this->table[word1]);	//Initilize the BFS algorithm via pushing the starting word to the queue
	this->table[word1]->dist = 0;	//Set it as the base level
	this->table[word1]->path = SENTINEL_VALUE;	//Set starting word as the end point of the found shortest path

	bool flag = true;		//Escape condition for BFS when it finds the end word
	while (!Queue.empty() && flag == true) //Until find the end word or reach all reachable vertices
	{
		v = Queue.front();	//Get a vertex
		Queue.pop();
		v->known = true;	//Set it as known since we reached it in its level

		for (unsigned int i = 0; i < v->adj_list->size(); i++)	//For all vertices adjacent to the current vertex
		{
			Edge edge = (*v->adj_list)[i];	//Get an edge
			
			w = this->table[edge.path];		//Label it as reachable for the next itteration of the BFS 
			if (w->dist == INT_MAX)
			{
				w->dist = v->dist + 1;		//Set its distance
				w->path = v->key;			//Set the direction of the shortest path that leads to the start word

				Queue.push(this->table[edge.path]); //Push it to the queue for the next itteration of the BFS

				if (edge.path == word2)		//If the end word is found
				{
					w->known = true;		//Set it as known
					flag = false;			//Terminate the BFS
				}
			}
		}
	}
}
//END:	Shortest path from start word to end word is established
//		Vertices that are processed labeled as known and their distance level is set

//TODO:	Prints the found shortest path
void Graph::printPath(const string& word, const string& startWord)
{
	vector<string*> Stack;	//Use a stack for backtracking

	if (this->table[word]->known == true) //If given end word is reachable from the start word
	{	
		backtrack(word, Stack);	//Fill stack according to path
	}

	else {					//If given end word is not reachable from the start word
		cout << endl << "ERROR: No sequence of one letter transformations exists for *" << startWord << "* to *" << word << "*" << endl;
		return;
	}

	//Print according to the operations
	for (int i = (Stack.size() - 1); 0 <= i; i--)
	{
		if (i != 0)
		{
			Vertex* current = this->table[*Stack[i]];
			string next = *Stack[i - 1];

			for (unsigned int j = 0; j < current->adj_list->size(); j++)
			{
				if ((*current->adj_list)[j].path == next) //Find the edge according to the given path
				{
					Edge edge = (*current->adj_list)[j];
			
					//Determine the operation type 
					if (edge.operation == 'A')				//Insertion
					{
						cout << next << " (insert " << edge.charachter << " after position " << edge.position << ")" << endl;
						break;
					}

					else if (edge.operation == 'D')			//Deletion
					{
						cout << next << " (delete " << edge.charachter << " at position " << edge.position + 1 << ")" << endl;
						break;
					}

					else {									//Change
						cout << next << " (change " << edge.charachter << " at position " << edge.position + 1 << " to " << edge.changedCh << ")" << endl;
						break;
					}
				}
			}
		}
	}
}
//END:	Shortest path (order of operations) is printed from start word to end word

//TODO:	Create word database via reading words from the external database line by line
void Graph::createDictionary(ifstream& file)
{
	string key;
	while (file >> key)	//Read line by line
	{
		this->wordList.push_back(new string(key));	//Add to word list
		this->table[key] = new Vertex;				//Create a vertex for new word
		this->table[key]->key = key;
		this->table[key]->adj_list = new vector<Edge>;	//Create its adjacency list
		this->table[key]->known = false;			//Initilize BFS variable known
		this->table[key]->dist = INT_MAX;			//Set distance unknown (INFINITY)
	}
}
//END:	Database is created from the given external source

//TODO:	Establish possible edges between given vertices
void Graph::createGraph()
{
	for (unsigned int i = 0; i < this->wordList.size(); i++) //For all words in the database
	{
		string currWord = *wordList[i];
		for (unsigned int j = 0; j < currWord.size(); j++)	//For each charachter of the current word
		{
			string delWord = currWord;
			delWord.erase(j, 1);	//Delete a charachter
			
			if (this->table.find(delWord) != table.end() && delWord != currWord) //If the new word (delWord) is in the database
			{
				Edge* newEdge1 = new Edge;			//Create an edge from currentWord's vertex to delWord's vertex
				initilizeEdge(newEdge1, delWord, 'D', currWord[j], j, 0);
				((this->table[currWord])->adj_list)->push_back(*newEdge1); //Add new edge to the adjacency list of the currentWord

				Edge* newEdge2 = new Edge;			//Since delWord is in the database, it can derive currentWord via inserting the char that was deleted
				initilizeEdge(newEdge2, currWord, 'A', currWord[j], j, 0);
				((this->table[delWord])->adj_list)->push_back(*newEdge2);  //Add new edge to the adjacency list of the delWord
			}

			for (int k = 97; k < 125; k++)			//For each charachter of the current word
			{
				string changeWord = currWord;
				char ch;
													//Change the charachter with a lowercase letter, " - " or " ' " 
				if (k == 123) { ch = 45; }
				else if (k == 124) { ch = 39; }
				else {  ch = k; }
				changeWord[j] = ch;

				if (this->table.find(changeWord) != table.end() && changeWord != currWord) //If changeWord is in the database and not a replica of a currentWord 
				{
					Edge* newEdge3 = new Edge;		//Create an edge from currentWord's vertex to changeWord's vertex
					initilizeEdge(newEdge3, changeWord, 'C', currWord[j], j, ch);
					((this->table[currWord])->adj_list)->push_back(*newEdge3);	//Add new edge to the adjacency list of the changeWord
				}
			}
		}
	}
}
//END:	Edges of the Graph are created and operations that leads to particular edge are indicated

//TODO:	Resets BFS variables for following searches
void Graph::resetSearch()
{
	for (unsigned int i = 0; i < this->wordList.size(); i++)
	{
		this->table[*wordList[i]]->known = false;
		this->table[*wordList[i]]->dist = INT_MAX;
	}
}
//END:	BFS variables are resetted

//TODO:	Initilizes an edge according to given values
void Graph::initilizeEdge(Edge* &newEdge, const string &path, const char operation, const char &charachter, const unsigned short int &position, const char &changedCh)
{
	newEdge->path = path;
	newEdge->operation = operation;
	newEdge->charachter = charachter;
	newEdge->position = position;
	newEdge->changedCh = changedCh;
}
//END:	Given edge is initilized

//TODO:	Follow the shortest path starting from the end word to decide operation sequence
void Graph::backtrack(const string& word, vector<string*> &backtrackVector)
{
	
	backtrackVector.push_back(new string(word));

	string tracker = this->table[word]->path;
	while (tracker != SENTINEL_VALUE)
	{
		backtrackVector.push_back(new string(tracker));
		tracker = this->table[tracker]->path;
	}
}
//END:	Operation sequence is pushed to the vector passed by reference

//TODO:	Checks that given two words are in the database or not, return true both are in the database
//																	Gives error if at least one of them is not in the database
bool Graph::inList(const string& word1, const string& word2)
{
	if (this->table.find(word1) == table.end() && this->table.find(word2) == table.end() && word1[0] != '*')
	{
		cout << endl << "ERROR: *" << word1 << "* and *" << word2 << "* are not in the words.txt, try with words that are in the words.txt" << endl;
		return false;
	}

	if (this->table.find(word1) == table.end() && word1[0] != '*')
	{
		cout << endl <<"ERROR: *" << word1 << "* is not in the words.txt, try with a word that is in the words.txt" << endl;
		return false;
	}


	if (this->table.find(word2) == table.end() && word1[0] != '*')
	{
		cout << endl << "ERROR: *" << word2 << "* is not in the words.txt, try with a word that is in the words.txt" << endl;
		return false;
	}

	return true;
}
//END:	Existence of given words are checked and returned as a bool