#include <stdio.h>

int main(void)
{
    int A[10];
    for(int i = 0; i < 10; i++) {
        printf("[%d]Enter an integer: ", i+1);
        scanf(" %d", &num);
        A[i] = num;
    }
    int i = 0;
    int found = 0;
    int foundOdd = 0;
    int foundEven = 0;
    while(i < 10 && found != 2) {
        if(A[i] % 2 && foundOdd != 1) {
            foundOdd++;
            printf("Odd: %d at index %d\n", A[i], i);
            found += foundOdd;
        }
        if((A[i] % 2) == 0 && foundEven != 1) {
            foundEven++;
            printf("Even: %d at index %d\n", A[i], i);
            found += foundEven;
        }
        i++;
    }
    return 0;
}

