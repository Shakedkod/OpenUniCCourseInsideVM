#include <stdio.h>

void printBinary(long x)
{
    int size = sizeof(x) * 8;
    unsigned long mask = 1 << (size - 1);
    while (mask)
    {
        printf("%d", (x & mask) ? 1 : 0);
        mask = mask >> 1;
    }
    printf("\n");
}

unsigned long createMask(const char isBaseOne, const int index)
{
    return isBaseOne
        ? ~(1<<(index - 1))
        : 1<<(index - 1);
}

unsigned long lightUpABit(const unsigned long bits, const int index)
{
    const unsigned long mask = 1 << (index - 1);
    return bits | mask;
}

int main()
{
    unsigned long x = 12, y;

    printBinary(x);
    printBinary(lightUpABit(x, 0));
    printBinary(lightUpABit(x, 1));
    printBinary(lightUpABit(x, 2));
    printBinary(lightUpABit(x, 3));
    printBinary(lightUpABit(x, 4));
    printBinary(lightUpABit(x, 5));
    printBinary(lightUpABit(x, 6));
    printBinary(lightUpABit(x, 7));
    printBinary(lightUpABit(x, 8));
    printBinary(lightUpABit(x, 9));

    return 0;
}