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
  int retVal = 0;
  int size = 16;
  int fd, err;
  ShmData* shmPtr;

  //Open file descriptor with read/write permissions
  fd = shm_open("/shm.h",O_RDWR, 0666);

  if(fd == -1){
    printf("Error with Shm_open\n");
    return -1;
  }

  //Memory map the file descriptor
  shmPtr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

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
    printf("Error with munmap\n");
    return -1;
  }

  printf("[Client]: Client exiting...\n");

  return(retVal);
}
