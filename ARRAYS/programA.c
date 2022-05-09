#include <stdio.h>
#include <stdlib.h>

int main(void) {
   int num;
   int size;
   int oddCount = 0;
   int evenCount = 0;
   printf("Enter a size for array: ");
   scanf(" %d", &size);
   int A[size];
   for(int i = 0; i < size; i++) {
      printf("Enter a number: ");
      scanf(" %d", &num);
      A[i] = num;
      if((A[i] % 2) == 0) {
	     evenCount += A[i];
	  } else {
	     oddCount += A[i];
	  }
   }
   if(evenCount > oddCount) {
      printf("output(even) = %d\n", evenCount);
   }
   if(evenCount < oddCount) {
      printf("output(odd) = %d\n", oddCount);
   }
   if(evenCount == oddCount) {
      printf("even = odd =  %d\n", oddCount);
   }
   return 0;
}
