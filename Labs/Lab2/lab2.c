/* Jesse Ericksen
   CSCI247, Spring 2018
   Laboratory Excercise 2
   16 April 2018

   The purpose of this program is to implent the itoa function to convert
   integers to strings given a specific number base */

   #include<stdio.h>
   #include<string.h>

   char* itoa(int num, char* str, int base);

   int main(int argc, char* argv[]){
     char* str[50];
     itoa(1203, *str, 4);

     return 0;
   }

   char* itoa(int num, char* str, int base){
     /* Handle Base Case if num is 0, it always equates to 0 */
     if(num == 0){
       return "0";
     }
     /* Sets a flag if number is negative, and converts to positive int */
     int flag = 0;
     if(base == 10){
       if(num < 0){
         flag++;
         num *= -1;
       }
     }

     /* While there are digits to add, finds least sig dig and adds to string */
     int count = 0;
     while(num > 0){
       int lsd = num % base;
       str[count] =  '0' + lsd;
       num /= base;
       count++;
     }

     if(flag != 0){
       str[count] = '-';
     }

     printf("%s", str);

   }
