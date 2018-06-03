#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Jesse Ericksen
   CSCI247, Spring 2018
   Lab 7: Cache Misses */

 /* Note* Lab Recommended use of perf tool for calculating stats which I was unable to 
	get to work with current versions of Ubuntu. I was able to use a recommended package 
	"valgrind" to display results using "valgrind --tool=cachegrind ./CacheLab SIZE METHOD

	Test 1 : Size = 64 x 64 ==> Accumulator: 258048
	Method 1: L1 Cache Misses: 3,505 (2.4%)
	Method 2: L1 Cache Misses: 3,505 (2.4%)

	Test 2: Size = 128 x 128 ==> Accumulator: 2080768
	Method 1: L1 Cache Misses: 6,398 (1.6%)
	Method 2: L1 Cache Misses: 21,757 (5.4%)

	Test 3: Size = 256 x 256 ==> Accumulator: 16711680
	Method 1: L1 Cache Misses: 15,614 (1.1%)
	Method 2: L1 Cache Misses: 77,053 (5.4%)

	Test 4: Size = 512 x 512 ==> Accumulator: 133955584
	Method 1: L1 Cache Misses: 53,573 (0.9%)
	Method 2: L1 Cache Misses: 298,237 (5.4%)
    ________________________________________________________________________

	Explanation: 
	
	When evaluating the above data, I noticed two significant trends. The first thing I noticed
	were the results from Test 1, where the choice of method (wether we transcend our array
	by row then column or vice versa) did not have any effect on the total number of cache misses. 
	This is because our array was small enough that when accessing a stored element in the cache, 
	we were able to pull out all surrounding elements that we would need for future calculation in that
	array. This has to do with how computers implement cache. Rather than requesting one single element
	from a cache, they pull out a chunk of data which in this case was our entire array.	

	Secondly, there was a trend noticable in Test 2 through Test 4 where the method made a huge difference
	on Cache Miss rate. Method 1 was able to access the exact same data and make the same calculations while
	averaging just 20% of the Cache Misses that Method 2 had. This makes sense because of the way our array
	was stored linearly in the Cache. Even though our elements are grouped together in the cache, they are 
	situated column by column, not row by row. Once our array became too large to pull all elements out, we
	saw more cache misses when trying to access elements that belonged to different rows.

	In conclusion, the data above provides us with good reason to use method 1's approach to accessing data in 
	multi-dimensional arrays in an effort to improve program effectiveness and lower cache misses so data can 
	be accessed and stored as quick as possible... */

int accessArray(int,int);

int main(int argc, char* argv[]){
	//Checks for correct number of arguments passed into program
	if(argc != 3){
		printf("To run, specify a matrix size and computation method: ./CacheLab size method\n");
		return 1;
	}

	int size = atoi(argv[1]);
	int method = atoi(argv[2]);

	//Error-Check argument requirements
	if(size < 1){
		printf("Size must be greater than zero\n");
		return 1;
	} else if(method != 1 && method != 2){
		printf("Method must be 1 or 2\n");
		return 1;
	}

	//Core Method for Building and Accessing Array
	accessArray(size, method);
}

int accessArray(int size, int method){

	//Initialize Array:
	int row, column; 
	int arrayArea = size * size;
	int array[size][size];
	memset(array,0,arrayArea * sizeof(int));

	for(row = 0; row < size; row++){
		for(column = 0; column < size; column++){
			array[row][column] = row + column;
		}
	}

	//Access elements using one of two methods while calculating sum.
	
	int accumulator = 0;

	//Method 1: 
	if(method == 1){
		for(row = 0; row < size; row++){
			for(column = 0; column < size; column++){
				accumulator += array[row][column];
			}
		}
	}

	//Method 2:
	if(method == 2){
		for(column = 0; column < size; column++){
			for(row = 0; row < size; row++){
				accumulator += array[row][column];
			}
		}
	}

	//Print value of accumulator
	printf("Accumulator = %d\n", accumulator);
	return 1;
}

