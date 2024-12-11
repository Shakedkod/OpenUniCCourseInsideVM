#ifndef ADJMAT_H
#define ADJMAT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "constants.h"

#define N 11
typedef Bool adjmat[N][N];

void inputAdjmat(adjmat tree);
void printAdjmat(adjmat tree);

#endif