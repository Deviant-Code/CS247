#include <stdio.h>
#include <stdlib.h>

/* Jesse Ericksen
   Lab 4 -- Float Manipulation

   This lab demonstrates floating point manipulation using a float's binary
   representation. I have included my own method float2int to convert floats to
   our typedef float_bits for purposes of reflecting the binary representation */ 

typedef unsigned float_bits;
unsigned float2int(float y);
void printFloatClass(int);
float unsigned2float(float_bits f);
void printBits(float_bits);
int floatClass(float_bits f);
int ReverseBits(int var);
float_bits float_negate(float_bits f);
float_bits float_absval(float_bits f);
float_bits float_twice(float_bits f);
float_bits float_twice(float_bits f);
float_bits float_half(float_bits f);

int main(int argc, char* argv[]){
	// Lines 22 - 26 print the float, unsigned and bitlevel reflection of user input.
	float floatForm = atof(argv[1]);
	float_bits unsignedFloat = float2int(floatForm);
	printf("Float Representation: %f\n", floatForm);
	printf("Unsigned Representation: %u\n", unsignedFloat);
	printBits(unsignedFloat);
	
	//Task 1: Classify Float 
    int type = floatClass(unsignedFloat);
	printf("Float Class: %d\n", type);
	printFloatClass(type);

	/* Allows user to input 32 bit binary number to classify float */
	printf("Enter a 32 bit binary number for classification: \n");
	long long longBitRep;
	scanf("%lld", &longBitRep);
	float_bits unsignedFloat2 = *(unsigned *)&longBitRep;
	printBits(unsignedFloat2);
	printf("Float Class: %d\n", floatClass(unsignedFloat2));
	printFloatClass(floatClass(unsignedFloat2));
.0
	//Task 2: Negate Float
	float_bits negateFloat = float_negate(unsignedFloat);
	printf("Reversed bits: %u \n", negateFloat);
	printf("Float Representation: %f \n", unsigned2float(negateFloat));
	printBits(negateFloat);

	//Task 3: Take the absolute value for a float.
	float_bits absValFloat = float_absval(unsignedFloat);
	printf("Absolute value as int: %u \n", absValFloat);
	printf("Float Representation: %f \n", unsigned2float(absValFloat));
	printBits(absValFloat);

	//Task 4: 
	float_bits doubleFloat = float_twice(unsignedFloat);
	printf("Doubled float as int: %u \n", doubleFloat);
	printf("Float Representation: %f \n", unsigned2float(doubleFloat));
	printBits(doubleFloat);
	
	//Task 5: 
	float_bits halfFloat = float_half(unsignedFloat);
	printf("Halved float as int: %u \n", halfFloat);
	printf("Float Representation: %f \n", unsigned2float(halfFloat));
	printBits(halfFloat);
	return 1;

}

float_bits float2int(float y) {
  return *(unsigned *)&y;
}

float unsigned2float(float_bits f){
	return *(float *)&f;
}

void printBits(float_bits f){
	f = ReverseBits(f);
	printf("Bit Representation: ");
	unsigned bit;
	for(int i = 0; i < 32; i++){
		bit = f & 1;
	 	printf("%u", bit);
		f >>= 1;
	}
	printf("\n\n"); 
}

int floatClass(float_bits f){

	unsigned int sign = f >> 31;
    unsigned int expo  = f >> 23 & 0xFF;
    unsigned int fraction = f & 0x7FFFFF;

    // Exponent is all zeros: Denormalized or equal to +/- 0
    if((expo & 0xFF) == 0x00){
    	// Equal to Zero
    	if(!(fraction & 0x7FFFFF)){
    		return 0;
    	} else {
    		// Denormalized
    		return 3;
    	}
    } else if((expo & 0xFF) == 0xFF){ 
    	//Special Cases
    	if((fraction & 0x7FFFFF)){
    		return 2;
    	} else {
    		// if fraction = 0, equals positive or negative infinity
    		return 1;
    	}
    } else {
    	//else exponent is neither all ones or zeros, == normalized
    	return 4;
    }
}

//Prints out the details to return class numbers for floatClass func
void printFloatClass(int num){
	printf("Float Class Represents: ");
	if(num == 0){
		printf("Positive or Negative Zero \n");
	} else if(num == 1) {
		printf("Infinity\n");
	} else if(num == 2) {
		printf("NaN\n");
	} else if(num == 3) {
		printf("Denormalized Number\n");
	} else if(num == 4) {
		printf("Normalized Number\n");
	} else {
		printf("You have broken me!");
	}
	printf("\n");
}

//Bitwise negation on float_bits
float_bits float_negate(float_bits f){
	return f ^ 0xFFFFFFFF;
}

//inverts sign bit
float_bits float_absval(float_bits f){
	unsigned int sign = f >> 31;
	if(sign){
		return f & 0x7FFFFFFF;
	} else {
		return f;
	}
}

//Method involves adding 1 to the exponent bits
float_bits float_twice(float_bits f){
	float_bits exponent = f & 0x7F800000;
	exponent >>= 23;
	exponent += 1;
	exponent <<= 23;
	exponent ^= f;
	//This way allows me to overwrite bits 1-8 with two xors
	f <<= 1;
	f >>= 24;
	f <<= 23;
	f ^= exponent;
	return f;
}

float_bits float_half(float_bits f){
	float_bits exponent = f & 0x7F800000;
	exponent >>= 23;
	exponent -= 1;
	exponent <<= 23;
	exponent ^= f;
	f <<= 1;
	f >>= 24;
	f <<= 23;
	f ^= exponent;
	return f;
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
}