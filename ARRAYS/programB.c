#include <stdio.h>
#include <stdlib.h>

void set_union(int* A, int* B, int size){ 
   int i = 0;
   int j = 0;
   while(i < size && j < size) {
	  if(A[i] == B[j]) {
		 printf("%d ", A[i++]);
		 j++;
	  }
      if(A[i] < B[j]) {
		 printf("%d ", A[i++]);
	  }
	  if(A[i] > B[j]) {
		 printf("%d ", B[j++]);
	  }
   }
   if(i < size) {
      while(i < size) {
		 printf("%d ", A[i++]);
	  }
   }
   if(j < size) {
      while(j < size) {
		 printf("%d ", B[j++]);
	  }
   }
   printf("\n");
}

void set_intersection(int* A, int* B, int size){
   for(int i = 0; i < size; i++) {
      for(int j = 0; j < size; j++) {
         if(A[i] == B[j]) {
            printf("%d ", A[i]);
            break;
         }
      }
   }
   printf("\n");
}

void set_difference(int* A, int* B, int size){
   int j = 0;
   for(int i = 0; i < size; i++) {
      if(A[i] != B[j]) {
         int found = 0;
	     for(int k = 0; k < size; k++) {
		    if(A[i] == B[k]) {
			   found = 1;
               break;
			}
         }
		 if(!found) {
            printf("%d ", A[i]);
         } 
	  } else {
         j++;
      }
   }
   printf("\n");
}

int main(void){
/* These methods assume BOTH arrays are equal in size,
 * go in acending order, and have no duplicates */
   int size = 10;
   int A[] = {1,2,3,4,5,6,7,8,9,10};
   int B[] = {1,3,5,7,9,11,13,15,17,19};

   printf("Array A: {");
   for(int i = 0; i < size-1; i++) {
      printf("%d, ", A[i]);
   }
   printf("%d}", A[size-1]);
   
   printf("\nArray B: {");
   for(int i = 0; i < size-1; i++) {
      printf("%d, ", B[i]);
   }
   printf("%d}\n", B[size-1]);

   printf("\nA u B: ");
   set_union(A, B, size);  

   printf("A n B: ");
   set_intersection(A, B, size);

   printf("A - B: ");
   set_difference(A, B, size);

   printf("B - A: ");
   set_difference(B, A, size);

   return 0;
}
