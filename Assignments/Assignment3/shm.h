/* Jesse Ericksen
   CSCI 247
   Assignment 3
   *Requires server.c and client.c in same directory.
*/

#ifndef SHM_H
#define SHM_H

enum StatusEnum{ INVALID, VALID, CONSUMED };

typedef struct{
	enum StatusEnum status;
	int data;
} ShmData;

#endif
