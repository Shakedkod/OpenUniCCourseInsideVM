#include <stdio.h>

int main()
{
    int a[] = {1,2,3,4,5,6,7,8,9,0};
    int c = 21, d = 11;
    printf("%d", a[(c/3 + 2) & d - 4] + 1);
}