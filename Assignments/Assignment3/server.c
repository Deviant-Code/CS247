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

int main(int argc, char* argv[])
{
	int retVal = 0;
 // Check for correct number of command line arguments
  if(argc != 2){
    printf("Please provide a argument when running program. \n");
    return -1;
  }

  int fd, i, j, k, l;
  char* ptr;
  //unsure if this is what we are supposed to do here. 
  fd = shm_open("/shm.h", O_CREAT | O_RDWR, 0666);

  if(fd == -1){
    printf("Failure with shm_open\n");
    return -1;
  }
  
  //<Use the POSIX "shm_open" API to open file descriptor with 
    //"O_CREAT | O_RDWR" options and the "0666" permissions>

 // <Use the "ftruncate" API to set the size to the size of your 
   // structure shm.h>
	i = ftruncate(fd, 32);

  //<Use the "mmap" API to memory map the file descriptor>
  ptr = (char *)mmap(NULL, 32, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  
  if(ptr == MAP_FAILED){
    printf("fd: %d \n", fd);
    perror("Map Failed");
    return -1;
  }

  //<Set the "status" field to INVALID>
  ptr->StatusEnum = INVALID;
  //<Set the "data" field to atoi(argv[1])>
  ptr->data = atoi(argv[1]);

  //<Set the "status" field to VALID>
  ptr->StatusEnus = VALID;  

  printf("[Server]: Server data Valid... waiting for client\n");

  while(shmPtr->status != CONSUMED)
    {
      sleep(1);
    }

  printf("[Server]: Server Data consumed!\n");
  
  //<use the "munmap" API to unmap the pointer>
  j = munmap(ptr, 32);

  <use the "close" API to close the file Descriptor>
  k = close(fd);

  if(k = -1){
    perror("Close() failed");
    return -1;
  }

 //<use the "shm_unlink" API to revert the shm_open call above>
  l = shm_unlink("/shm.h");

  printf("[Server]: Server exiting...\n");

  return(retVal);

}

  
  
  
      
  
