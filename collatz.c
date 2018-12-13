#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	//error check that user inputs one positive integer
	if(!(argc == 2)){
		fprintf(stderr, "usage: %s int \n", argv[0]);
		exit(1);
	}

	//convert input into integer
	int start;
	sscanf(argv[1], "%d", &start);

	if(start < 0){
		fprintf(stderr, "Must enter a positive integer \n");
		exit(2);
	}

 	const int SIZE = 4096; // the size (in bytes) of shared memory object
	const char *name = "Shared"; // name of the shared memory object
	int shm_fd; // shared memory file descriptor
	void *ptr; // pointer to shared memory object

	// create child process
	pid_t pid;
	pid = fork();

	if(pid < 0){
		fprintf(stderr, "fork failed");
		return 1;
	}
	else if(pid == 0){ // child process + shared_mem producer
		// create the shared memory object
		shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

		// configure shared memory size
		ftruncate(shm_fd, SIZE);

		// memory map the shared memory object
		ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

		while(start != 1){
			//calculate length of message
			int message_len = snprintf(NULL, 0, "%d ", start);
			snprintf(ptr, message_len + 1, "%d ", start);
			ptr += message_len;
			if(start % 2 == 0){
				start /= 2;
			} else {
				start = (3 * start) + 1;
			}
		}
		// add trailing 1
		int message_len = snprintf(NULL, 0, "1\n");
		snprintf(ptr, message_len + 1, "1\n");
		ptr += message_len;
	}
	else{ // parent process + shared mem consumer
		wait(NULL);

		// open shared memory object
		shm_fd = shm_open(name, O_RDONLY, 0666);

		// memory map the shared object
		ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

		// read and print from the shared memory object
		printf("%s", (char *)ptr);

		// remove the shared memory object
		shm_unlink(name);
	}

	return 0;
}