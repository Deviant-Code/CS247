/* Jesse Ericksen
   Lab 3 - CSCI247
   Each individual method is commented off and are meant to be ran individually.
   Simply uncomment the method to test. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int CountSetBits(unsigned int var);
int IdentifyUniqueInteger(int arrayCount, int* intArray);
int ReverseBits(int var);
bool OnlyOneBitSet(int);
bool OnlyOneBitSetInEvenPostion(int);
int ModWithoutUsingModOperator(int numerator, int denominator);
int SwapNibbles(int);
int NumberOfOperationsRequired(int);


int main(int argc, char *argv[]){
	/* Task 1: Count set bits from user input decimal
	unsigned int dec ;
	printf("Enter a positive base 10 integer for which you would like to check set bits: \n");
	scanf("%u", &dec);
	int count = CountSetBits(dec);
	printf("Set Bits: %d\n", count);  */

	/* Task 2: Find the unique element in array of duplicate ints 
	int digits[argc];
	for(int i = 0; i < argc; i++){
		digits[i] = atoi(argv[i]);
	}
	int result = IdentifyUniqueInteger(argc, digits);
	printf("%d\n", result); */ 

	/* Task 3: Reverse the bits in an integer  
	if(argc != 2){
		printf("Please enter only one integer in command line\n");
	} else {
		int result = ReverseBits(atoi(argv[1]));
		printf("Result of reversed bits: %d\n", result); 
	} */

	/* Task 4: Find out if only one bit is set in an Integer 
	bool result = OnlyOneBitSet(atoi(argv[1]));
	printf("\nResult: %d\n", result); */

	/* Task 5: Find out if an integer with a single bit set has the set bit at an odd or even position 
	if(OnlyOneBitSet(atoi(argv[1]))){
		bool evenPosition = OnlyOneBitSetInEvenPostion(atoi(argv[1]));
		printf("%d\n", evenPosition);
	} else {
		printf("The number provided has more than one set bit\n"); 
	} */

	/* Task 6: Perform Modulus operation when denominator only has 1 bit set without using “%” 
	int numerator = atoi(argv[1]);
	int denominator = atoi(argv[2]);
	if(OnlyOneBitSet(denominator)){
		int mod = ModWithoutUsingModOperator(numerator, denominator);
		printf("The modulus of %d and %d is: %d\n", numerator, denominator, mod);
	} else {
		printf("Please enter a denominator with only one bit set\n");
	} */

	/* Task 7: Swap nibbles within each byte of an integer 
	int result = SwapNibbles(atoi(argv[1]));
	printf("Result of swapping nibbles: %d\n", result); */

	/* Task 8: Counter Game: 
	int result = NumberOfOperationsRequired(atoi(argv[1]));
	printf("Result: %d\n", result); */
}

int CountSetBits(unsigned int var){
	int count = 0;
	int place = 1;
	while(var){
		count += var & 1;
		var >>= 1;
	}
	return count;
}

int IdentifyUniqueInteger(int arrayCount, int* intArray){
	int result = intArray[0];
	for(int i = 1; i < arrayCount; i++){
		result = result ^ intArray[i];
	}
	return result;
}

int ReverseBits(int var){
	/* reverses all bits from 0-31 including sign bit */
	int reverseVar = 0;
	int i;
	for(i = 0; i < 32; i++){
		reverseVar<<=1;
		reverseVar = reverseVar | (var & 1);
		var >>= 1;
	}
	return reverseVar;
	/* reverses bits of unsigned
	int reverseVar = 0;
	while(var){
		reverseVar <<= 31;
		if((var & 1) == 1){
			reverseVar ^= 1;
		}
		var >>= 1;
	}
	return reverseVar;*/
}

bool OnlyOneBitSet(int var){
	bool set = 0;
	while(var){
		if((var & 1) == 1){
			if(set == 1){
				return false;
			}
			set += 1;
		}
		var >>= 1;
	}
	if(set == 0){ 
		return false; 
	}
	return true;
}

bool OnlyOneBitSetInEvenPostion(int var){
	int count = 1;
	while(var){
		if(((var & 1) == 1) && ((count % 2) == 0)){
			return true;
		}
		var >>= 1;
		count++;
	}
	return false; 
}

int ModWithoutUsingModOperator(int numerator, int denominator){
	int count = 0;
	int modNum = 0;
	while(denominator){
		if((denominator & 1) == 1){
			break;
		}
		denominator >>= 1;
		count++;
	}

	for(int i = 0; i < count; i++){
		modNum |= (numerator & 1) << i;
		numerator >>= 1;
	}
	return modNum;
}

int SwapNibbles(int var){
	int temp = var & 0xF0F0F0;
	temp >>= 4;
	var &= 0x0F0F0F;
	var <<= 4;
	var |= temp;
	return var;
}

int NumberOfOperationsRequired(int val){
	int count = 0;
	/* First check if number is a power of 2, subtract 1 and count set bits */
	if((val & (val-1)) == 0){
		val = val-1;
		while(val != 0){
			val = (val & val-1);
			count++;
		}
	} else {
		int lowestBit = log(val & -val) / log(2);
		while(val > 0){
			val = (val & val-1);
			count++;
		}
		count += lowestBit - 1;
	/* Alternative Approach to calculating shifts based on logs 
	while(val > 1){
		int temp = (int) floor(log(val)/log(2));
		temp = (int) pow((double) temp, 2);
		val -= temp;
		count++;
	} */
}
	return count;
}