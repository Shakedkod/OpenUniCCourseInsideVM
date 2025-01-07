#ifndef ADJMAT_H
#define ADJMAT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "constants.h"

#define N 11
typedef Bool adjmat[N][N];

/* this function gets input from the user and fills the adjmat given accordingly */
void inputAdjmat(adjmat tree);

/* this function prints an adjmat given */
void printAdjmat(adjmat tree);

#endif