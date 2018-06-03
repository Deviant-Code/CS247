#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

int arrayFunction(int column, int row);

int arrayFunction(int matrixSize, int method)
{
  int dataStuff = (matrixSize)*(matrixSize);
  int* myArray;
  myArray = malloc(sizeof(int)* dataStuff); //mallocing an array of pointers


  int rows =0;
  int cols=0;
  int accumulator =0 ;

  for(int i=0; i<matrixSize; i++)
  {
    for(int j=0;j<matrixSize;j++)
    {

      myArray[(matrixSize *i)+ j] = i+j;

    }
  }

  if(method == 1 )
  {
    for(rows=0; rows<matrixSize; rows++)
    {
      for(cols=0;cols<matrixSize;cols++)
      {

        accumulator = accumulator+ myArray[(matrixSize *rows)+ cols];

      }
    }
  }else if(method == 2)
  {
    for(cols=0; cols<matrixSize; cols++)
    {
      for(rows=0;rows<matrixSize;rows++)
      {
        accumulator = accumulator+ myArray[(matrixSize *rows)+ cols];
      }
    }
  }else
  {
    printf("Enter a 1 or a 2 for the method pls\n" );
  }

  printf("Accumulator: %d\n", accumulator );

}



int main(int argc, char* argv[])// MAIN FUNCTION!!!
{
  // Takes 2 arguments in function, <matrix size>, <computation method>
  int sizeOfMatrix = atoi(argv[1]);
  int computationMethod = atoi(argv[2]); // must be 1 or 2

  arrayFunction(sizeOfMatrix, computationMethod);


}
