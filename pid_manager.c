#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define MIN_PID 300;
#define MAX_PID 5000;

/* 
 * Create and initialize data structure to represent PIDs
 * returns 1 if successful, -1 if unsuccessful
 */
int allocate_map(void){
	//allocate an integer array large enough to map a bitmap of size MAX_PID - MIN_PID + 1
	int bitmap_size = MAX_PID - MIN_PID + 1;
	int* pid_table = (int*) malloc(bitmap_size * sizeof(int));

	if(pid_table == NULL){
		printf("malloc of pid_table of size %d failed!\n", bitmap_size);
		return -1;
	}
	else{
		printf("malloc of pid_table of size %d successful!\n", bitmap_size);
		return 1;
	}
}

/*
 * Allocate and return a pid; returns -1 if unsuccessful (all pids are in use)
 */
int allocate_pid(void){
	int pid = -1;

	for(int i = 0; i < bitmap_size; i++){
		//if int array element bitAND 1 shifted equals 0, pid not in use
		if(pid_table[i / 32] & (1 << (k % 32)) == 0){
			pid = i + MIN_PID;
		}
	}

	return pid;
}

/*
 * Releases a pid from use
 */
void release_pid(int pid){
	int shiftedIndex = pid - MIN_PID;
	pid_table[shiftedIndex / 32] &= ~(1 << (shiftedIndex % 32));
}
