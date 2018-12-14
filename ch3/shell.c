/** 
 * Author: Brian Meehan
 * Date 12/13/18
 *
 * Ch3 Programming Project
 * Design C program to serve as a shell interface
 * that accepts user commands and executes each 
 * command in a separate process
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_LINE 80 // The maximum length command
        
int main(void)
{
	char buffer[MAX_LINE]; // raw user input
	char *token; // individual processed token
	char *args[MAX_LINE/2 + 1]; // array of parsed command line arguments
	int numArgs; // number of cl args input by user
	int parent_wait = 0; // flag if parent process should invoke wait()
	pid_t pid; // process id
	int should_run = 1; // flag to determine when to exit program 

	while (should_run) {
		// print shell prompt
		printf("osh> ");
		fflush(stdout);
	
		// read user input
		fgets(buffer, sizeof(buffer), stdin);
		
		// parse input into tokens, store count of args that were input
		token = strtok(buffer, " ");
		numArgs = 0;
		while(token != NULL){
			args[numArgs++] = token;
			token = strtok(NULL, " ");
		}

		// if user inputs "exit", switch running flag
		if(strcmp(args[0], "exit") == 0){
			should_run = 0;
		}

		// if user includes '&' as last argument, flag parent wait()
		if(strcmp(args[numArgs-1], "&") == 0){
			parent_wait = 1;
		}

		pid = fork();
		if (pid < 0){ // error occured
			fprintf(stderr, "Fork failed!\n");
			return 1;
		}
		if (pid > 0){ // parent process
			if(parent_wait){
				wait(NULL);
			}
		} 
		else { // child process
			if (execvp(args[0], args) < 0) {
           		fprintf(stderr, "exec failed!\n");
           		exit(1);
          	}	
		}
		
		/**
		 * After reading user input, the steps are:
		 * (1) fork a child process using fork()
		 * (2) the child process will invoke execvp()
		 * (3) if command included &, parent will invoke wait() 
		 */
    }

	return 0;
}