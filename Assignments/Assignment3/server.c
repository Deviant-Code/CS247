/*  Jesse Ericksen
    CSCI 247, Spring 2018
    Assignment 3

    *Requires client.c and shm.h in directory
    *Compile with -lrt flag and run with a valid integer argument. Characters will evaluate to 0.

    Task 5: How can we use IPC and timers to periodically retrieve data between processes?

    Using the timer_create API, we could set regular intervals to interrupt a process in order to retrieve data
    from the producer. Just as we accomplished in the previous assignment, we could set a timer period and using
    shared memory we could have our producer save necessary data fields to a structure in shared memory using
    shm_open and mmap API's. Then we are able to signal our client process to retrieve the new data from the same 
    structure in shared memory. I can see this being a extremely useful tool for maintaining data between processes
    at regular intervals but also a method that we need to be cautious in implementing the right protections.  
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "shm.h"
#include <ctype.h>

int main(int argc, char* argv[])
{
	int retVal = 0;
  int size = 16;
  int fd, err;
  ShmData* shmPtr;

  //Check for correct number of command line arguments.
  if(argc != 2){
    printf("Program requires one integer argument.\n");
    return -1;
  }

  //Create a new shared memory location w/ read write permission using shm.h file
  fd = shm_open("shm.h", O_CREAT | O_RDWR, 0666);

  if(fd == -1){
    printf("Failure with shm_open.\n");
    return -1;
  }

	//Set size of shm shared memory structure
  err = ftruncate(fd, size);

	if(err == -1){
		return -1;
	}

  //<Use the "mmap" API to memory map the file descriptor>
  shmPtr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  if(shmPtr == MAP_FAILED){
    perror("Error w/ mmap\n");
    return -1;
  }

  //Set the shared structure data value to the user arg
  shmPtr->status = INVALID;
  shmPtr->data = atoi(argv[1]);
  shmPtr->status = VALID;

  printf("[Server]: Server data Valid... waiting for client.\n");

  while(shmPtr->status != CONSUMED){
      sleep(1);
  }

  printf("[Server]: Server Data consumed!\n");

  err = munmap(shmPtr, size);

	if(err == -1){
    printf("Error with munmap.\n");
		return -1;
	}

  err = close(fd);

  if(err == -1){
    perror("Error closing fd.\n");
    return -1;
  }

  err = shm_unlink("shm.h");

  if(err == -1){
    printf("Error with shm_unlink.\n");
		return -1;
	}

  printf("[Server]: Server exiting...\n");

  return(retVal);

}
