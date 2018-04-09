/*
   Jesse Ericksen
   W01173602
   Course: CSCI 247 - Spring 2018
   File Name: Lab1.c

   Task 3:
   - "#" marks a call to the preprocesser to include the following file in program
   - Forward declarations are required because the compiler reads sequentially and our method does not yet exist when called in main
   - Macros can both speed up compiling, as well as make it easier for the user to read our variables when they are being called more than once.
     They are part of the pre-processor directive.
   - Function calls like any other language allow us to departmentalize our program by what each section is doing, making our program more
     efficient, as well as allowing us to call functions more than once in order to limit our code.
   - Escape characters allow us to print characters that have a specific meaning in the C language.
   - Operators are represented by specific characters which are already defined by the compiler to yield a specific operation. Functions are blocks
     of code that generally yield multiple instructions defined by the programmer which execute whenever it is called. Functions are part of the compiling process
     where as macros are part of the preprocessing.
   - Keywords are words that have a specific meaning to a programming language. We used many keywords in this simple program including return, char, and void
   - Printf produces output to the standard out "stdout" module. Whereas stdin would allow for input, and stderr would output error messages
*/

#include<stdio.h>
#include<string.h>

#define CHAR_DATA_TYPE "char"
#define INT_DATA_TYPE "int"
#define SHORTINT_DATA_TYPE "short int"
#define LONGINT_DATA_TYPE "long int"
#define FLOAT_DATA_TYPE "float"
#define DOUBLE_DATA_TYPE "double"

void DataTypeSizes(void);
char* GetStringFromStdin(char* str);
void DisplayString(const char* str);

int main(int argc, char* argv[])
{
  int i;
  printf("argc: \"%d\"\nargv: \"%s\" \n", argc, argv[i]);
  DataTypeSizes();
  char str[100];
  GetStringFromStdin(str);
  DisplayString(str);
  return(0);
}

void DataTypeSizes(void)
{
  /* print char */
  printf("\"%s\" is a standard C datatype. Size of a \"%s\" data type is %ld\r\n",
	 CHAR_DATA_TYPE, CHAR_DATA_TYPE, sizeof(char));
  /* print int */
  printf("\"%s\" is a standard C datatype. Size of a \"%s\" data type is %ld\r\n",
	 INT_DATA_TYPE, INT_DATA_TYPE, sizeof(int));
   /* print short int */
  printf("\"%s\" is a standard C datatype. Size of a \"%s\" data type is %ld\r\n",
 	 SHORTINT_DATA_TYPE, SHORTINT_DATA_TYPE, sizeof(short int));
  /* print long int */
  printf("\"%s\" is a standard C datatype. Size of a \"%s\" data type is %ld\r\n",
 	 LONGINT_DATA_TYPE, LONGINT_DATA_TYPE, sizeof(long int));
  /* print float */
  printf("\"%s\" is a standard C datatype. Size of a \"%s\" data type is %ld\r\n",
	 FLOAT_DATA_TYPE, FLOAT_DATA_TYPE, sizeof(float));
  /* print double */
  printf("\"%s\" is a standard C datatype. Size of a signed  \"%s\" data type is %ld\r\n",
	 DOUBLE_DATA_TYPE, DOUBLE_DATA_TYPE, sizeof(double));
}

char* GetStringFromStdin(char* str)
{
fgets(str,100,stdin);
return str;
}

void DisplayString(const char* str)
{
fputs(str, stdout);
}
