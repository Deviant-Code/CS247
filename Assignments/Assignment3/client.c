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
  int          retVal = 0;
  int fd;
  ShmData* shmPtr;

  //<Use the POSIX "shm_open" API to open file descriptor with
    //"O_RDWR" options and the "0666" permissions>
  fd = shm_open("/shm.h",O_RDWR, 0666);

  //<Use the "mmap" API to memory map the file descriptor>
  shmPtr = mmap(NULL, 32, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  printf("[Client]: Waiting for valid data ...\n");

  while(shmPtr->status != VALID)
    {
      sleep(1);
    }

  printf("[Client]: Received %d\n",shmPtr->data);

  shmPtr->status = CONSUMED;
  //<use the "munmap" API to unmap the pointer>
  munmap(shmPtr, 32);
  //add error check int


  printf("[Client]: Client exiting...\n");

  return(retVal);

}
