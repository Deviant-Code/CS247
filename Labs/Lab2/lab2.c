/* Jesse Ericksen
   CSCI247, Spring 2018
   Laboratory Excercise 2
   16 April 2018

   The purpose of this program is to implent the itoa function to convert
   integers to strings given a specific number base 

   Experimenting with memset for practice, but if memory were to be constrained, I would alternatively use malloc and calculate the exact number
   of bytes required to use my itoa function for a given number and base.  */

   #include<stdio.h>
   #include<string.h>
   #include<stdlib.h>
   #include<ctype.h>

   char* itoa(int num, char* str, int base);

   int main(int argc, char* argv[]){
      
     int number;
     int base; 
     char str[500];
     memset(&str, '\0', sizeof(char));
     
     if ((argc >= 2) && (isdigit(*argv[1]) || *argv[1] ==  '-')) {
        number = atoi(argv[1]);
     } else {
        fprintf(stderr, "ERROR: './itoa number base'\n");
        return 1;
     }
     
     if ((argc >= 3) && isdigit(*argv[2])) {
        base = atoi(argv[2]);
     } else {
        fprintf(stderr, "ERROR: './itoa number base'\n");
        return 1;
     }
     
     printf("%s\n", itoa(number, str, base));

     return 0;
   }

   char* itoa(int num, char* str, int base){
     /* Handle Base Case if num is 0, it always equates to 0 */
     if(num == 0){
       return "0";
     }
     
     /* Sets a flag if number is negative, and converts to positive int */
     int flag = 0;
       if(num < 0){
         flag++;
         num *= -1;
       }
     
     /* THIS IS JUST FOR FUN */
     if (base == 1) {
        int count = 0;
        while (num > 0) {
            if (count > 500) {
                fprintf(stderr, "ERROR: Number conversion too big for array.");
                str[0] = '\0';
                return str;
            }
            num--;
            str[count] = '|';
            count++;
        }
        return str;
    }

     /* While there are digits to add, finds least sig dig and adds to string */
     int count = 0;
     while(num > 0){
       int lsd = num % base;
       if(lsd > 9){
          lsd -= 10;
          str[count] =  'a' + lsd;

       } else {
          str[count] =  '0' + lsd;
      }
      num /= base;
      count++;
     }

     if(flag){
       str[count] = '-';
       count++;
     }
     
     /* needs to be reversed */
     char temp;
     int index = 0;
     count--;
   
     while(count>= index) {
        temp = str[index];
        str[index] = str[count];
        str[count] = temp;
        index++;
        count--;
     }
     return str;

   }