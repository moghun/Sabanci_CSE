//Muhammed Orhun Gale - 26754
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t semA; //Semaphore to put A fans to sleep until hit the desired fan combination - also signals to wake them up
sem_t semB; //Semaphore to put B fans to sleep until hit the desired fan combination - also signals to wake them up
pthread_mutex_t mutex; //Mutex for enqueue properly
pthread_barrier_t cap; //Barier to hold fans until the car become full 

int waitingA = 0;  //Number of A fans on the queue
int waitingB = 0;  //Number of B fans on the queue

void* fanA_handler(); //Function which checks that if the desired combination (4 A fans or 2 A - 2 B fans) is formed or not for A fans
void* fanB_handler(); //Function which checks that if the desired combination (4 B fans or 2 B - 2 A fans) is formed or not for B fans


int main(int argc, char* argv[])
{
    int numA, numB;
    //Convert input arguments to integers
    numA = atoi(argv[1]);
    numB = atoi(argv[2]);

    //If total number of fans is 4s multitlude and there are even numbers of A and B fans
    if(((numA + numB) % 4 == 0) && (numA % 2 == 0) && (numB %2 == 0))
    {
        //Initialize signaling semaphores
        //Semaphores are initilized as '0' in order to hold first three thread that reaches the wait point to sleep 
        sem_init(&semA, 0, 0);
        sem_init(&semB, 0, 0);
        pthread_barrier_init(&cap, NULL, 4); //Hold all threads until exactly 4 thread call pthread_barrier_wait()

        //Create a dynamic array that holds thread ID's to initilize and wait them properly
        int exec_size = (sizeof(pthread_t)) * (numA + numB);
        pthread_t* threads = (pthread_t*) malloc(exec_size);

        //Initilize threads
        for(int i = 0; i < (numA + numB); i++)
        {
            if(i < numA)
            {
                int fanA = pthread_create(&threads[i], NULL, fanA_handler, NULL);     
            }

            else{
                int fanB = pthread_create(&threads[i], NULL, fanB_handler, NULL);
            }
        }

        //Make main thread wait until all threads join it
        for(int i = 0; i < (numA + numB); i++)
        {
            pthread_join(threads[i], NULL);
        }

        //Free the dynamic list
        free(threads);
        printf("The main terminates\n");    
        
    }

    //If there are any odd number of A or B fans ,or total number of fans is not a multitude of 4 exit program
    else{
        printf("The main terminates\n");
    }
    return 0;
}



void* fanA_handler()
{
    //Mutex that ensures every fan get into the queue properly (w/o any race condition)
    pthread_mutex_lock(&mutex);
    printf("Thread ID: %ld, Team: A, I am looking for a car\n", pthread_self());
    waitingA++;  //Add one A fan to the queue
    int latestArrival;  //Make latest arriving fan the captain of the car

    //If in the queue, there are less than 4 A fans 
                         //and number of A fans is not equal to 2 and 3 given or number of B fans in the queue is less than 2
    if((waitingA < 4) && !((waitingA == 2 || waitingA == 3) && waitingB >= 2)) 
    {
        latestArrival = 0;            //Set that you are not the latest arriving fan
        pthread_mutex_unlock(&mutex); //Then unlock mutex
    }

    else{    
        if(waitingA == 4)   //If there are exactly 4 A fans in the queue
        {
            latestArrival = 1; //Then you are the latest fan arrive
            waitingA -= 4;     //Decrement number of A fans on the queue
            
            //Release 4 A fans
            sem_post(&semA); 
            sem_post(&semA);
            sem_post(&semA);
            sem_post(&semA);   
        }

        else{            //If there are 2 or 3 A fan waiting and number of B fans is more than 2

            latestArrival = 1; //Then you are the latest fan arrive
            waitingA -= 2;  //Decrement number of A fans on the queue
            waitingB -= 2;  //Decrement number of A fans on the queue
            
            //Release 2 A and 2 B fans
            sem_post(&semA);
            sem_post(&semA);
            sem_post(&semB);
            sem_post(&semB);               
        

        }
    }
    //Wait until a car is formed
    sem_wait(&semA);
    printf("Thread ID: %ld, Team: A, I have found a spot in a car\n", pthread_self());

    //Wait until the car gets full
    pthread_barrier_wait(&cap);


    if(latestArrival == 1) //If you are the latest arriving fan
    {
        printf("Thread ID: %ld, Team: A, I am the captain and driving the car\n", pthread_self());
        latestArrival = 0;
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}


void* fanB_handler()
{
    //Mutex that ensures every fan get into the queue properly (w/o any race condition)
    pthread_mutex_lock(&mutex);
    
    printf("Thread ID: %ld, Team: B, I am looking for a car\n", pthread_self());
    waitingB++; //Add one A fan to the queue
    int latestArrival; //Make latest arriving fan the captain of the car
    //If in the queue, there are less than 4 B fans 
                         //and number of B fans is not equal to 2 and 3 given or number of A fans in the queue is less than 2
    if((waitingB < 4) && !((waitingB == 2 || waitingB == 3) && waitingA >= 2))
    { 
        
        latestArrival = 0; //Set that you are not the latest arriving fan
        pthread_mutex_unlock(&mutex); //Then unlock mutex
    }

    else{    
        if(waitingB == 4) //If there are exactly 4 B fans in the queue
        {
            latestArrival = 1; //Then you are the latest fan arrive
            waitingB -= 4;     //Decrement number of B fans on the queue       
            
            //Release 4 A fans
            sem_post(&semB);
            sem_post(&semB);
            sem_post(&semB);
            sem_post(&semB);   
        }

        else{

            latestArrival = 1; //Then you are the latest fan arrive
            waitingB -= 2;      //Decrement number of B fans on the queue
            waitingA -= 2;      //Decrement number of A fans on the queue
            
            //Release 2 B and 2 A fans
            sem_post(&semB);
            sem_post(&semB);
            sem_post(&semA);
            sem_post(&semA);               
        }
    }

    //Wait until a car is formed
    sem_wait(&semB);
    printf("Thread ID: %ld, Team: B, I have found a spot in a car\n", pthread_self());

    //Wait until the car gets full
    pthread_barrier_wait(&cap);


    if(latestArrival == 1) //If you are the latest arriving fan
    {
        printf("Thread ID: %ld, Team: B, I am the captain and driving the car\n", pthread_self());
        latestArrival = 0;
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}