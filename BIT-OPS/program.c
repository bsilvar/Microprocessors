#include <stdio.h>
#include <stdlib.h>

unsigned int bitCheck(int i, int num) {
   /* Shifting to the specified bit, then ANDing with 1 
      to check what that "i-th" bit is set to */
   return (num >> i) & 1;
}

void count(int num) {
   int i;
   int org = num;
   // counter for number of bits that are 0's
   int count0 = 0;
   // counter for number of bits that are 1's
   int count1 = 0;
   // Traversing throught a 32-bit number 
   for(i = 0; i < 32; i++) {
      // check if bit is 0 or 1
      if(num & 1) { // found bit is set to 1
         count1++;
      } else {      // found bit is set to 0
         count0++; 
      }
      num >>= 1;    // logical shift right to check next bit
   }
   printf("The decimal number (%d) ", org);
   printf("has %d bit/s set to 0 ", count0);
   printf("and %d bit/s set to 1\n\n", count1);
}

void power_of_two(int num) {
   int org = num;
   // counter for number of bits that are 1's
   int count1 = 0;
   // Traversing throught until number is 0
   if(num == 1) {
      count1++; // ignores 1 as being a power of 2   
   }
   while(num > 0) {
      // check if bit is 1
      if(num & 1) { // found bit is set to 1
         count1++;
      }
      num >>= 1;    // LSR to check next bit
   }
   /* check if 'num' has more than one bit set to 1 since having
      only one bit set to 1 means the number IS a power of 2 */
   if(count1 > 1) {
      printf("The decimal number (%d) NOT a power of 2\n", org);
   } else {
      printf("The decimal number (%d) IS a power of 2\n", org);
   }
}

int main(void) {
   printf("Bit Operations in \"C\"\n");
   printf("Program 1:\n");
   int i = 3;
   int num = 5;
   int bit = bitCheck(i, num);
   printf("The decimal number (%d) has bit %d set to: %d\n\n", num, i, bit);

   printf("Program 2:\n");
   num = 128;
   count(num);

   printf("Program 3:\n");
   num = 16;
   power_of_two(num);
   return 0;
}
