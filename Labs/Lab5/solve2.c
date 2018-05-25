#include <stdio.h>

/*  Jesse Ericksen
	CS 247, Spring 2018
	Lab 5 - Part 2 
	Reverse Engineering Assembly */

int main(){
	int x, y, z, q;
	x = 19;
	y = 34;
	z = 12;
	q = 3*x + (y << 2) + 2*z;
	return q;
}
