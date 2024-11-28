#include "part1.h"
#include "part2.h"

#define MAC(x) x##2

#define print2(arr, n) \
{ \
    int i = 0; \
    for (; i < n; i++) {\
        if (arr[i] % 2 == 0) \
            printf("%d", arr[i]); \
    } \
    printf("\n"); \
}

#define numOf2(arr, n, result) \
{ \
    int i = 0, counter = 0; \
    for (; i < n; i++) {\
        if (arr[i] % 2 == 0) \
            counter++; \
    } \
    result = counter; \
}

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int res;

    fun1(5);
    fun2(10, 'a');
    printf("%d\n", MAC(5));

    print2(arr, 10)
    numOf2(arr, 10, res)
    printf("%d\n", res);
    return 0;
}