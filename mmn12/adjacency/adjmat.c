#include "adjmat.h"
#include "constants.h"

void inputAdjmat(adjmat tree)
{
    int i, j;
    char *currentLine = malloc(sizeof(char)*(N+2));
    if (currentLine == NULL)
    {
        printf("There is not enough space on your computer for the input.");
        exit(1);
    }

    printf("Please enter a line of 0 & 1 without any spaces between them. For each line you need to enter %d characters.\n if a character is not 0 or 1, it will be inserted as 0.\n", N);

    for (i = 0; i < N; i++)
    {
        printf("line %d: ", (i + 1));

        if (fgets(currentLine, N+2, stdin) == NULL)
        {
            printf("There was a problem with the input.");
            exit(1);
        }

        for (j = 0; j < N; j++)
        {
            if (currentLine[j] == '1')
                tree[i][j] = TRUE;
            else
                tree[i][j] = FALSE;
        }
    }

    free(currentLine);
    printf("\n");
}

void printAdjmat(adjmat tree)
{
    int i, j;

    for (i = 0; i < (N*3 + 2); i++) printf("-");
    printf("\n");

    for (i = 0; i < N; i++)
    {
        printf("|");
        for (j = 0; j < N; j++)
        {
            if (tree[i][j])
                printf(" 1 ");
            else
                printf(" 0 ");
        }
        printf("|\n");
    }

    for (i = 0; i < (N*3 + 2); i++) printf("-");
    printf("\n");
}