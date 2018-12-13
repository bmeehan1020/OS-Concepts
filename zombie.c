#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t pid;

	pid = fork();

	if(pid < 0){ // error occured
		fprintf(stderr, "fork failed");
		return 1;
	}
	else if(pid == 0){ // child process

	}
	else { // parent process
		sleep(10);
		wait(NULL);
	}

	return 0;
}