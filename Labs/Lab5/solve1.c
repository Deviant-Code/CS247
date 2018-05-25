 #include <stdio.h>

/*  Jesse Ericksen
	CS 247, Spring 2018
	Lab 5 - Part 1 
	Reverse Engineering Assembly */
 
 int main(){
 	int x, y;
 	x = 0;
 	y = 0;
 	y = x + y;
 	x = y + x;
	y = x++;
 }