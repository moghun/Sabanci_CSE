//Muhammed Orhun Gale - 26754
#include "MLFQ.h"
#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>

using namespace std;

//TODO: Takes folder directory as input
string getFolderName()
{
	string folderName;
	cout << "Please enter the process folder name: ";
	cin >> folderName;
	return folderName;
}
//END:  Returns folder directory as a string

//TODO: Reads configuration file
vector<int> getConfigs(string &fileDirectory)
{
	ifstream configFile;
	configFile.open(fileDirectory+ "/configuration.txt");

	vector<int> configurations;

	//If configuration file cannot be found in the given directory ask a new directory
	if(!(configFile.is_open()))
	{
		fileDirectory = getFolderName();
		configurations = getConfigs(fileDirectory);   //Recursively asks for a new input
	}


	else
	{
		string currentLine;

		while (getline(configFile, currentLine))         
		{
			istringstream stringStream(currentLine);  //A string stream to get configurations one by one
			int config;
			if(stringStream>>config)
			{
				configurations.push_back(config);     //Push each configuration to returning vector
			}
		}
	}
	configFile.close();
	return configurations;
}
//END:  Returns a vector that includes MLFQ configurations

//TODO: Read each process txt and create a new process for each
void getProcesses(string fileDirectory, const int &numOfProcesses, const int &numOfQueues,vector<Process> & procList)
{
	//Ends function if there are no processes
    if (numOfProcesses == 0)
    {
        return;
    }

    for (int i = 1; i <= numOfProcesses; i++)
    {
        ifstream processFile;
        processFile.open(fileDirectory + "/p" + to_string(i) + ".txt");   //Open each process txt

		//Create a process and initilizate data members
        Process currentProcess;
		currentProcess.ID = i;
		currentProcess.currentQueue = numOfQueues;
		currentProcess.status = '9';

		//Push instructors that are given for each process
        string currentLine;
        while (getline(processFile, currentLine))
        {
            istringstream stringStream(currentLine);
            int inst;
            if(stringStream >> inst)
            {
				currentProcess.cpuTime.push_back(inst);
            }
        }

		currentProcess.numInstructions = currentProcess.cpuTime.size();   //Initilize process' number of instruction data member
		procList.push_back(currentProcess);    //Push back each process to passed vector
		processFile.close();
    }
}
//END:  Processes are created and pushed into process list vector 

//TODO: Starts MLFQ also handles the output part
void startMLFQ(const vector<Process> &programCommands, const int &numberOfQueues, const int &quantumSize, string fileDirectory)
{
	ofstream output;
	output.open(fileDirectory+"/output.txt");

	MLFQ MLFQ(numberOfQueues, quantumSize, programCommands);   //Creates a MLFQ object

	//Content of the output file will be created via giving following strings to the output file
	string resultOutput;
	string takeBackOutput;

	int counter = 1;

	//While there is at least one process in the MLFQ
	while(MLFQ.isMLFQEmpty() == false)
	{
		resultOutput = MLFQ.startQuantum();       //Start a new quantum
		takeBackOutput = MLFQ.restartQuantum();   //Set back for a new quantum
		if(MLFQ.isMLFQEmpty() == true)
		{
			//Eleminates the last "\n" in the output file
			if(resultOutput != "")
			{
				resultOutput.pop_back();
			}
			if(takeBackOutput != "")
			{
				takeBackOutput.pop_back();
			}
		}
		output << resultOutput << takeBackOutput;  //Adds resulting and restarting outputs to the output file
	}
	output.close();
}
//END:  Processes are processed via MLFQ, output txt is created

int main()
{
	string fileDirectory;
	fileDirectory = getFolderName();

	vector<int> configs;
	configs = getConfigs(fileDirectory);
	cout << "When all processes are completed, you can find execution sequence in" << endl <<"\"" << fileDirectory << "/output.txt\"" << endl;
	
	//Set MLFQ settings
	int numberOfQueues, numberOfProcesses, quantumSize;

	numberOfQueues = configs[0];
	numberOfProcesses =  configs[1];
	quantumSize = configs[2];

	//Create processes
	vector<Process> procList;

	getProcesses(fileDirectory, numberOfProcesses, numberOfQueues, procList);

	//Start MLFQ and handle the processes
	startMLFQ(procList, numberOfQueues, quantumSize, fileDirectory);

	return 0;
}