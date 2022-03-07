//Muhammed Orhun Gale - 26754 - CS204_HW7

#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <random>
#include <time.h>
#include "morhun_gale_muhammedOrhun_hw7_DynIntQueue.h"

using namespace std;


HW7DynIntQueue productionLine; //Queue which simulates production line
HW7DynIntQueue packagingLine;  //Queue which simulates packaging line

mutex productionMutex; //Mutex that controls production line process
mutex packagingMutex;  //Mutex that controls packaging line process
mutex coutMutex;       // Mutex that tidies up the outputs

int maxItemCount; //Number of items which is gonna produced
int counter1 = 0; //Counts the number of filled items by fillers
int counter2 = 0; //Counts the number of packaged items by packagers

int minProducer, maxProducer; //Range of the wait time of producer
int minFiller, maxFiller;     //Range of the wait time of fillers
int minPackager, maxPackager; //Range of the wait time of packagers



// TODO: Random number generator in a given range - provided by homework
int random_range(const int & min, const int & max) 
{ 
	static mt19937 generator(time(0)); 
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator); 
}
//  END: A random number is returned in the range of given interval



// TODO: The function that simulates the production
void producer()
{
	for(int i = 1; i <= maxItemCount; i++)
	{
		productionMutex.lock();
		productionLine.enqueue(i);  //Item enqueued to production line
		productionMutex.unlock();

		coutMutex.lock();
		time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
		struct tm *ptm = new struct tm; 
		localtime_s(ptm, &tt); 
		cout <<"Producer has enqueued a new box "<< i <<" to filling queue (filling queue size is "<< productionLine.getCurrentSize() << ") : " << put_time(ptm,"%X") <<endl;
		coutMutex.unlock();

		int second = random_range(minProducer, maxProducer);  //Randomization
		this_thread::sleep_for(chrono::seconds(second));  //Waiting time

	}
}
//  END: Given number of items produced and provided to the production line
//       coutMutex part is taken from the codes provided in the recitations 



// TODO: The function that simulates the provided number of fillers
//       Processes the items on the production line
void filler(int id)
{
	int itemID;
	

	while(counter1 < maxItemCount)
	{
		productionMutex.lock();		
		if (!productionLine.isEmpty()) 
		{  
			productionLine.dequeue(itemID);   //Item is taken from the production line
			counter1++;                       //Number of items processed incremented
			productionMutex.unlock();
			
		
			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<<"Filler " << id <<" started filling the box "<< itemID <<	" (filling queue size is "<< productionLine.getCurrentSize() <<") :" << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
			
			int secondF = random_range(minFiller, maxFiller);  //Randomization
			this_thread::sleep_for(chrono::seconds(secondF));  //Waiting time

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			localtime_s(ptm, &tt); 
			cout<<"Filler " << id <<" started filling the box "<< itemID <<": " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();


			packagingMutex.lock();
			packagingLine.enqueue(itemID);   //Filled item enqueued to packaging line
			packagingMutex.unlock();
	
			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			localtime_s(ptm, &tt); 
			cout<<"Filler " << id <<" put box "<< itemID <<" into packaging queue (packaging queue size is "<< packagingLine.getCurrentSize() <<") :" << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
		}
		else
		{
			productionMutex.unlock();
		}

	}
}
//  END: Given number of items filled and provided to the packaging line
//       coutMutex part is taken from the codes provided in the recitations 




// TODO: The function that simulates the provided number of packagers
//       Processes the items on the packaging line
void packer(int id)
{
	int itemID;

	while(counter2 < maxItemCount)
	{
		packagingMutex.lock();
		if (!packagingLine.isEmpty()) 
		{  

			packagingLine.dequeue(itemID);  //Item is taken from the packaging line
			counter2++;                     //Number of filled items incremented
			packagingMutex.unlock();
			

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<<"Packager " << id <<" started packaging the box "<< itemID <<" (packaging queue size is "<< packagingLine.getCurrentSize() <<") :" << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
			
			int secondP = random_range(minPackager, maxPackager); //Randomization
			this_thread::sleep_for(chrono::seconds(secondP));     //Waiting time

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			localtime_s(ptm, &tt); 
			cout<<"Packager " << id <<" finished packaging the box "<< itemID <<": " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();

		}
		
		else
		{
			packagingMutex.unlock();
		}
	}
}
//  END: Given number of items packaged
//       coutMutex part is taken from the codes provided in the recitations 



int main()
{

	cout << "Please enter the total number of items: ";
	cin >> maxItemCount;

	cout << "Please enter the min-max waiting time range of producer:" << endl;
	cout << "Min: ";
	cin >> minProducer;
	cout << "Max: "; 
	cin >> maxProducer;

	cout << "Please enter the min-max waiting time range of filler workers:" << endl;
	cout << "Min: ";
	cin >> minFiller;
	cout << "Max: "; 
	cin >> maxFiller;

	cout << "Please enter the min-max waiting time range of packager workers:" << endl;
	cout << "Min: ";
	cin >> minPackager;
	cout << "Max: "; 
	cin >> maxPackager;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 

	cout <<endl << "Simulation starts: "<< put_time(ptm,"%X") << endl << endl;


	thread thr0(producer);
	thread thr1(filler, 1);
	thread thr2(filler, 2);
	thread thr3(packer, 1);
	thread thr4(packer, 2);


	thr0.join();
	thr1.join();
	thr2.join();
	thr3.join();
	thr4.join();

	tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	localtime_s(ptm, &tt); 

	cout << endl << "End of the simulation: " << put_time(ptm,"%X") << endl << endl;
	return 0;
}
