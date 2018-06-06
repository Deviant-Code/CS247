/* Jesse Ericksen
   CSCI247, Spring 2018
   Assignment 3

   *Requires server.c and shm.h files in directory
   *Run server.c first with argument, then client.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "shm.h"

int main(int argc, char* argv[])
{
  //Current size of shared memory set to size of struct in shm.h
  int size = sizeof(ShmData);
  int retVal = 0;
  int fd, err;
  ShmData* shmPtr;

  //Open file descriptor with read/write permissions
  fd = shm_open("/shm.h",O_RDWR, 0666);

  if(fd == -1){
    perror("shm_open");
    exit(EXIT_FAILURE);
  }

  //Memory map the file descriptor
  shmPtr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  if(shmPtr == MAP_FAILED){
    close(fd);
    perror("mmap");
    exit(EXIT_FAILURE);
  }

  printf("[Client]: Waiting for valid data ...\n");

  while(shmPtr->status != VALID)
    {
      sleep(1);
    }

  printf("[Client]: Received %d\n",shmPtr->data);

  shmPtr->status = CONSUMED;

  //Unmap the pointer
  err = munmap(shmPtr, size);

  if(err == -1){
    close(fd);
    printf("Error with munmap\n");
    exit(EXIT_FAILURE);
  }
  printf("[Client]: Client exiting...\n");
  
  close(fd);

  return(retVal);
}
