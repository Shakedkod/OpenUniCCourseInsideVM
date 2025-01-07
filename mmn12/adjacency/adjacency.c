#include <stdio.h>

#include "constants.h"
#include "adjmat.h"

Bool findPath(adjmat treeMap, int indexU, int indexV, Bool visited[N])
{
    /* this function gets an adjmat and two indexes and checks if there is a path from indexU to indexV */
    int i = 0;

    if (indexU >= N || indexV >= N)
        return FALSE;
    if (visited[indexU]) /* if we return to the same one there is a loop in the adjmat */
        return FALSE;
    if (treeMap[indexU][indexV] || indexU == indexV)
        return TRUE;

    visited[indexU] = TRUE;
    
    for (; i < N; i++)
    {
        if (treeMap[indexU][i])
            if (findPath(treeMap, i, indexV, visited))
                return TRUE;
    }

    return FALSE;
}

Bool path(adjmat treeMap, int indexU, int indexV)
{
    /* this function gets a adjmat and two indexes and checks if there is a path from indexU to indexV */
    Bool visited[N] = {0};
    if (indexU >= N || indexV >= N)
        return FALSE;
    if (indexU == indexV)
        return FALSE;
    return findPath(treeMap, indexU, indexV, visited);
}

int main()
{
    int indexU, indexV, checker;
    adjmat theFirstAdjmat;

    inputAdjmat(theFirstAdjmat);
    printAdjmat(theFirstAdjmat);

    printf("enter two numbers with a comma between them to check if there is a path between the first one and the second one:");
    checker = scanf("%d,%d", &indexU, &indexV);
    while ((indexU != -1) && (indexV != -1) && (checker != 0) && (checker != EOF))
    {
        printf("\n");
        if (path(theFirstAdjmat, indexU, indexV))
            printf("There is a path between %d and %d.\n", indexU, indexV);
        else
            printf("There isn't a path between %d and %d.\n", indexU, indexV);

        printf("enter two numbers with a comma between them to check if there is a path between the first one and the second one:");
        checker = scanf("%d,%d", &indexU, &indexV);
    }

    return 0;
}