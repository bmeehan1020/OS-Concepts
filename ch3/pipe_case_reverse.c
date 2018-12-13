/*
 * Author: Brian Meehan
 * Date: 12/13/2018
 * Use UNIX ordinary pipes to send message to child process
 * child process will reverse the case of each character and 
 * send the altered message back to the parent process
 * This program uses 2 pipes since ordinary UNIX pipes are unidirectional
 * Ordinary pipes are a simple example of Interprocess Communication (IPC)
 */

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

/*
 * Takes a string and reverses the case of each character
 * e.g. "Have a Nice Day!" -> "hAVE A nICE dAY!"
 */
void reverse_case(char* s){
	int c = 0;

	while(s[c] != '\0'){
		if(islower(s[c])){
			s[c] = toupper(s[c]);
		}
		else if (isupper(s[c])){
			s[c] = tolower(s[c]);
		}
		c++;
	}
}

int main(void)
{
	char write_msg[BUFFER_SIZE]; // buffer to write into pipe
	char read_msg[BUFFER_SIZE]; // buffer to read from pipe
	int input_pipefd[2]; // first pipe to send message btw processes
	int output_pipefd[2]; // second pipe to send altered message btw processes
	pid_t pid; // id of parent + child processes

	// create the pipes
	if (pipe(input_pipefd) == -1 || pipe(output_pipefd) == -1) {
   		fprintf(stderr,"Pipe failed");
		return 1;
	}

	//fork a child process 
	pid = fork();
	if (pid < 0){ // error occured
		fprintf(stderr, "Fork failed!\n");
		return 1;
	}
	if (pid > 0){ // parent process
		//close unused end of both pipes
		close(input_pipefd[READ_END]);
		close(output_pipefd[WRITE_END]);

		// process user input
		printf("Enter a string:\t");
		if(fgets(write_msg, BUFFER_SIZE, stdin) == NULL){
			fprintf(stderr, "Read user input into buffer failed!\n");
		}

		// write input to pipe
		write(input_pipefd[WRITE_END], write_msg, strlen(write_msg)+1);

		// read from child pipe, blocks until child closes pipe
		read(output_pipefd[READ_END], read_msg, BUFFER_SIZE);
		
		// print altered message to stdout
		printf("%s", read_msg);

		// close both pipes
		close(input_pipefd[WRITE_END]);
		close(output_pipefd[READ_END]);
	}
	else { // child process
		//close unused end of both pipes
		close(input_pipefd[WRITE_END]);
		close(output_pipefd[READ_END]);

		// read message from input pipe
		read(input_pipefd[READ_END], read_msg, BUFFER_SIZE);

		// reverse case of each character in message_msg);
		reverse_case(read_msg);

		// write altered message into output pipe
		write(output_pipefd[WRITE_END], read_msg, strlen(read_msg)+1);

		// close both pipes
		close(input_pipefd[READ_END]);
		close(output_pipefd[WRITE_END]);
	}

	return 0;
}
