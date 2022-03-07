//Muhammed Orhun Gale - 26754

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>



int main(int argc, char *argv[])
{
	printf("I’m SHELL process, with PID: %d - Main command is: man ping | grep \"\\-A\" -A 2 > output.txt \n", (int)getpid());
	
	//Shell process (Main Process) --> (process 0)
	
	int pipe_fd[2];                   //Creating read and write storage for pipe
	pid_t process_tracker[2];	   //In order to keep track of the process ID's, using an array
	
	if(pipe(pipe_fd) < 0)             //Creating pipe, checking in case of eny error
	{
		perror("pipe");
		exit(1);
	}
	
	process_tracker[0] = fork();        //Child process created (process 1)


	if(process_tracker[0] < 0)
	{
		perror("fork");
		exit(1);
	}
	
	else if (process_tracker[0] == 0)    //Child process' domain (process 1)
	{
		
		printf("I’m MAN process, with PID: %d - My command is: man ping\n", (int)getpid());

		process_tracker[1] = fork();   //Grandchild process created (process 2)

		if(process_tracker[1] < 0)
		{
			perror("fork");
			exit(1);
		}

	
		else if (process_tracker[1] == 0) //Grandchild process' domain  (process 2)
		{

			close(pipe_fd[1]);        //Closing pipe's "write" end for this process 
			
			printf("I’m GREP process, with PID: %d - My command is: grep \"\\-A\" -A 2 > output.txt \n", (int)getpid());
			
			int new_file = open("./output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);  //Opening "output.txt" and saving its file_id
			if(dup2(new_file, STDOUT_FILENO) < 0)    // Closing grandchild process' (process 2) standart output and putting the output.txt
			{
				perror("dup2");
				exit(1);
			}

			if(dup2(pipe_fd[0], STDIN_FILENO) < 0)   // Closing grandchild process' (process 2) standart input and giving the pipe's read end as the input of grep command
			{
				perror("dup2");
				exit(1);
			}
			
			
            		char *myargs2[5];	  //Setting the execution parameters
            		
            		myargs2[0] = strdup("grep");
            		myargs2[1] = strdup("\\-A"); // "\\" enables to select special characters
            		myargs2[2] = strdup("-A");   // Enables selecting given number of lines
            		myargs2[3] = strdup("2");
            		myargs2[4] = NULL;
            		
            		execvp(myargs2[0], myargs2); //Executing "grep" command with "-A" variable with extra variables that makes grep get the stated number of lines


		}
		
		else{                             //Child process' domain   (process 1)

			close(pipe_fd[0]);        //Closing pipe's "read" end for this process 

			if(dup2(pipe_fd[1], STDOUT_FILENO) < 0) //Closing child process' (process 1) standart output and putting the pipe's write
			{
				perror("dup2");  
				exit(1);
			}
			
			
			
           		 char *myargs[3];          //Setting the execution parameters
           		 myargs[0] = strdup("man"); 
           		 myargs[1] = strdup("ping");  
           		 myargs[2] = NULL;         
           		 execvp(myargs[0], myargs); //Executing "man" command with "ping" variable

		}

	}
	

	else                                 //Parent process' domain (process 0)
	{
		wait(NULL);         	      //Waiting for the child process to end its execution
      		printf("I’m SHELL process, with PID:%d - execution is completed, you can find the results in output.txt\n", (int)getpid());
	}	
	
}
