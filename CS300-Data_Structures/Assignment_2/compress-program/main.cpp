//Muhammed Orhun Gale - 26754 - compressor.cpp (main.cpp)
//Implementation of LZW compression algorithm for text files using a template "HashTable" class and "DictItem" class  


/* ***ADD ONLY HEADER FILES TO THE PROJECT, *DO NOT ADD "DictItem.cpp" and "HashTable.cpp"**
											
											CLASS SOURCES FILES ARE INCLUDED AT THE END OF THE "HashTable.h" FOR PRACTICAL PURPOSES*** */  


#include <iostream>
#include <fstream>
#include "DictItem.h"
#include "HashTable.h"


using namespace std;

//Sentinel Value
DictItem NOT_FOUND(-619, "\nI coded the DictItem class to use in the HashTable template. Therefore, I need to include both DictItem.cpp and HashTable.cpp at the end of the HashTable.h in order to put them into the same translator unit. However, right now, I am very anxious about if the DictItem.cpp is included to the project and I get tons of unresolved external errors and eventually get a 0 from this homework, I hope including a class does not get me into trouble. \nAlso, in MT1, I believe that I did solve the last question correctly. Even If I did not, I think most of it should be correct :(. Literally two days before the midterm, I randomly solved the question in the GeeksForGeeks' practice range. You can take a look at it by Googling \"Iterative Preorder Traversal GfG\". \nOkay for the rest I think I need to type some random things.\n333333333333333333333rewfzdasdfasfaewrasdcasdasfawedadfafaewadafsrfaewdafsdfafasfasfasdfaserawfasdcasdasdvadsvadvadasda_____________________Fasdfasdfasdfasdfasdvasd\n");

int dictNum = 256;		//A global counter to keep track of the number of items in the dictionary


//TODO:	Calculate hash value for given string by using DictItem hash function
int getStringHash(const string& searchWord)
{
	DictItem dummy(-2, searchWord);
	int hashVal = ::hash(dummy, CLOSESTPRIME);	

	return hashVal;
}
//END:	Hash value calculated and returned



//TODO:	Search a string key is in the dictionary or not
bool inDict(const string &searchWord, const HashTable<DictItem> &dict)
{

	int hashVal = getStringHash(searchWord);

	DictItem entry = dict.searchString(searchWord, hashVal);

	if(entry.getID() == -1)			//If not in dictionary
	{
		return false;
	}

	else{
		return true;
	}
}
//END:	If the item in the dictionary returned true; else returned false



//TODO:	Initilize dictionary with ASCII codes
void setupDictionary(HashTable<DictItem> &dict)
{
    for(int i = 0; i < 256; i++)
    {
		char ch = (char)i;
		string str = "";
		str += ch;
		DictItem newDictEntry(i, str);
		dict.insert(newDictEntry);
    }
}
//END:	Dictionary initilized with ASCII codes 0-255



//TODO:	Compression algorithm
//		Takes the text as a string and decodes it
//		Updates dictionary according to the algorithm to make use of recursive words
string compressor(const string &text, HashTable<DictItem> &dict)
{
	string coded = "";				//Returning string
	unsigned int counter = 0;		//Counting the number of charachters processed

	while(counter < text.size())	//Until end of the string
	{
		string slice = "";			//Get the next char processed
		string slice2 = "";			//Keep track of the latest addition

		slice += text[counter];	
		slice2 += text[counter];

		while((inDict(slice, dict) == true) && (counter < text.size()))	//If slice is in the dictionary and still have the chars to process
		{
			counter++;				
			slice2 = slice;			//Set as previous
			slice += text[counter];	//Add next char
		}

		if(dictNum < 4096)			//Do not allow to add more than 4096 elements to the dictionary
		{
			
			if(slice[1] == '\0')	//If empty string (not space!), do not add to the dictionary
			{
				slice.pop_back();	
			}

			DictItem newDictEntry(dictNum, slice);		//Create new dictionary entry
			bool inserted = dict.insert(newDictEntry);	//Insert to the dictionary
			if(inserted == true)						//If insertion is successful, i.e. if it is a new dictionary entry
			{
				dictNum++;								//Increment number of current entries in the dictionary
			}
		}
		
		int hashSearchV = getStringHash(slice2);				//Get hash value
		DictItem dum = dict.searchString(slice2, hashSearchV);	//Find it in the dictionary to get its code

		coded += (to_string(dum.getID()) + " ");
	}
	return coded;
}
//END:	Text is coded according to the algorithm and returned
//		Dictionary updated for the further usage


int main()
{
	HashTable<DictItem> dictionary(NOT_FOUND, CLOSESTPRIME); //Initilize the dictionary with the closest prime to the 8192, it is picked to hold lambda under 1/2
	setupDictionary(dictionary);		//Initilize dictionary with ASCII codes
	
	ifstream compin("compin");		//Input file
	ofstream compout("compout");	//Output file

	cout << endl <<  "Compression started, please wait..." << endl;
	cout << "*****************************************************************************" << endl << endl << endl;

	char ch;		
	int counter = 0;
	string input = "";
	while(compin.get(ch))				//Read file char by char
	{
		input += ch;
	}

	string output =	compressor(input, dictionary); //Compress the text into a string

	cout << "Compression done!" << endl << endl;

	compout << output;								//Write compressed text to the output file

	
	cout << "You can find the compressed file as \"compout\" in the program directory" << endl;
	cout << "*****************************************************************************" << endl << endl;

	compin.close();
	compout.close();
	
	return 0;
}