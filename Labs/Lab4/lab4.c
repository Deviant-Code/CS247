#include <stdio.h>
#include <stdlib.h> 

typedef unsigned float_bits;
unsigned float2int(float y);

int floatClass(float_bits f);
float_bits float_negate(float_bits f);
float_bits float_absval(float_bits f);
float_bits float_twice(float_bits f);

int main(int argc, char* argv[]){
	
	float bit = atof(argv[1]);
	float_bits bits = float2int(bit);
	printf("bits: %u\n ", bits);

	// int type = floatClass(bits);
	// printf("%d\n", type);

	printf("Reversed bits: %u \n", float_negate(bits));
	//printf("Absolute value: %u \n", float_absval(bits));
	return 1;
}

unsigned float2int(float y) {
  return *(unsigned *)&y;
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

/*float_bits float_negate(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp  = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF & frac != 0) 
        return f;

    return (~sign << 31) | (f & 0x7FFFFFFF);
}*/

float_bits float_negate(float_bits f){
	return f ^ 0xFFFFFFFF;
}

float_bits float_absval(float_bits f){
	unsigned int sign = f >> 31;
	if(sign){
		return f & 0x7FFFFFFF;
	} else {
		return f;
	}
}

float_bits float_twice(float_bits f){
	return 0;

}
