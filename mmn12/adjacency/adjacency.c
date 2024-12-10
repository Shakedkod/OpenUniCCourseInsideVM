#include "constants.h"

Bool path(adjmat treeMap, int indexU, int indexV)
{
    int i = 0;

    if (indexU >= N || indexV >= N)
        return FALSE;
    if (treeMap[indexU][indexV])
        return TRUE;
    
    for (; i < N; i++)
    {
        if (treeMap[indexU][i])
            if (path(treeMap, i, indexV))
                return TRUE;
    }

    return FALSE;
}

int main()
{
    return 0;
}