//Muhammed Orhun Gale - 26754 - decompressor.cpp (main.cpp)
//Implementation of LZW decompression algorithm for text files  


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int currentSize = 0; //A global counter to follow the number of items in the dictionary

//TODO: Create a string's deep copy on the heap 
string* strDeepCopy(const string& rhs)
{
	string* newStr = new string;

	*newStr = rhs;

	return newStr;
}
//END:	Deep copy of given string is created and a pointer that stores its adress is passed

//TODO:	Initilize dictionary with ASCII codes
void setDictionary(vector<string* > &vec)
{	
	for(; currentSize < 256; currentSize++)
    {
		char ch = (char)currentSize;
		string str = "";
		str += ch;
		vec[currentSize] = strDeepCopy(str);
    }
}
//END:	Dictionary initilized with ASCII codes 0-255


//TODO:	Decompression algorithm
//		Takes a code and by using dictionary decodes it
//		Updates dictionary according to the existence status of the input code in the dictionary
string decompress(const string &code, vector<string* > &dict)
{
	static string prev = "";			//Static string variable to keep track of the latest code that is decompressed
	string decoded = "";				//Returning string

	int pos = stoi(code);				//Convert code from string to int

	if(dict[pos] == nullptr)			//If given code is not in the dictionary yet  ---  It is assumed that there cannot be more than 4096 entries
	{
		string slice = prev + prev[0];	//Previously decoded slice + its first char

		if(currentSize < 4096)
		{
			dict[currentSize] = strDeepCopy(slice); //Create a deep copy of the new dict entry in order to keep it when function gets out of the scope
			
			currentSize++;				
		}
		decoded += slice;				
		prev = slice;					//Set prev (static variable) as current slice
	}

	else{								//If given code is in the dictionary

		string slice = *(dict[pos]);	//Decode from the dictionary
		decoded += slice;				
		
		if(prev != "" && currentSize < 4096) //Do not add to the dictionary if it is the first decoded code
		{
			dict[currentSize] = strDeepCopy(prev+slice[0]); //Previously decoded slice + current slice's first char -- Create deep copy to add the dictionary
			
			currentSize++;
		}
		prev = slice;					//Set prev (static variable) as current slice
	}
	return decoded;
}
//END:	Given code is decoded and returned
//		Dictionary updated according to the algorithm


int main()
{


	vector<string* > dictionary(4096, nullptr); //Create dictionary with max 4096 entries - Not yet added entries represented as 'null pointer'
	setDictionary(dictionary);					//Initilize dictionary with ASCII codes
	
	ifstream compout("compout");			//Input file
	ofstream decompout("decompout");		//Output file

	cout << endl << "Decompression started, please wait..." << endl;
	cout << "*****************************************************************************" << endl << endl << endl;

	char ch;
	int counter = 0;
	while(!compout.eof())						//Read until the end of file
	{
		string code = "";						//String that file will be stored into
		
		do{
			compout.get(ch);
			code += ch;
		}while(ch != ' ' && !compout.eof());	//Get codes that are seperated by spaces

		if(compout.eof())
		{
			break;
		}

		decompout << decompress(code, dictionary); //Decode the text
	}

	cout << "Decompression done!" << endl << endl;

	compout.close();
	decompout.close();

	for (unsigned int i = 0; i < dictionary.size(); i++) //Clear the dynamic memory that is allocated for the dictionary
	{
		if (dictionary[i] != nullptr)
		{
			delete dictionary[i];
		}
	}

	cout << "You can find the decomproessed file as \"decompout\" in the program directory" << endl;
	cout << "*****************************************************************************" << endl << endl;
	
	return 0;
}