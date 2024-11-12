#include <stdio.h>

void printBinary(unsigned long x)
{
    int size = sizeof(x) * 8;
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
    const unsigned long mask = 1UL << (index - 1);
    return bits | mask;
}

int main()
{
    unsigned long x = 12, y;

    printBinary(x);
    printBinary(turnOnBitAtIndex(x, 1));
    printBinary(turnOnBitAtIndex(x, 2));
    printBinary(turnOnBitAtIndex(x, 3));
    printBinary(turnOnBitAtIndex(x, 4));
    printBinary(turnOnBitAtIndex(x, 5));
    printBinary(turnOnBitAtIndex(x, 6));
    printBinary(turnOnBitAtIndex(x, 7));
    printBinary(turnOnBitAtIndex(x, 8));
    printBinary(turnOnBitAtIndex(x, 9));

    return 0;
}