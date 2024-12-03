#include <stdio.h>

void printBinary(const unsigned long x)
{
    /* prints an unsigned long number in base 2 insted of base 10. */
    const int size = sizeof(x) * 8;
    unsigned long mask = 1UL << (size - 1);
    while (mask)
    {
        printf("%d", (x & mask) ? 1 : 0);
        mask = mask >> 1;
    }
    printf("\n");
}

unsigned long turnOnBitAtIndex(const unsigned long bits, const int index)
{
    /* turns on a bit in the index that was chosen, starting from 1. */
    const unsigned long mask = 1UL << (index - 1);
    return bits | mask;
}

int isABitOn(const unsigned long bits, const int index)
{
    /* checks if a bit is on at the index that was chosen, starting from 1. */
    const unsigned long mask = 1UL << (index - 1);
    return (bits & mask) ? 1 : 0;
}

int main()
{
    unsigned long x, y;
    int isBit7On = 0;

    /* input */
    printf("Please enter two numbers x and y in this form: x,y.\n");
    scanf("%lu,%lu", &x, &y);

    printf("X is %lu so in base 2 X is ", x);
    printBinary(x);

    printf("Y is %lu so in base 2 Y is ", y);
    printBinary(y);

    /* change */
    x = turnOnBitAtIndex(x, 13);
    isBit7On = isABitOn(y, 7); 

    /* output */
    printf("The new X value is ");
    printBinary(x);

    printf("Is the 7th bit in Y on? ");
    if (isBit7On)
        printf("YES.\n");
    else
        printf("NO.\n");

    return 0;
}