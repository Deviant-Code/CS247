#include <stdio.h>
#include <stdlib.h>

/*  Jesse Ericksen
	CS 247, Spring 2018
	Lab 5 - Part 3 
	Reverse Engineering Assembly */

int main(){  
	int result;
	int arrayOfInts[7];
	arrayOfInts[0] = 0x17;
	arrayOfInts[1] = 0x13;
	arrayOfInts[2] = 0xc;
	arrayOfInts[4] = 0x2;
	arrayOfInts[5] = 0x3;
	arrayOfInts[6] = 0x1;
	result = 0;
	result += arrayOfInts[0] * arrayOfInts[4];
	result += arrayOfInts[1] * arrayOfInts[5];
	result += arrayOfInts[2] * arrayOfInts[6];
}