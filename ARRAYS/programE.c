#include <stdio.h>

int main(void)
{
    printf("Enter an integer: ");
    int num;
    scanf(" %d", &num);
    int count = 0;
    for(int i = 0; i < 32; i++) {
        if(num & (1<<i)) {
            count++;
        }
    }
    printf("total 1's: %d\n", count);
    return 0;
}
