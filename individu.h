// LO21 Project
// Author: Hugo Allainé - Léo Angonnet
// individu.h

#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define longIndiv 8
#define A -1
#define B 1
#define pCross 0.5

typedef unsigned char Bit;

/* Bits list
 */
typedef struct _bits{
    Bit value;
    struct _bits* next;
} Bits;

/* Individu
 */
typedef Bits* Individu;

// Function prototypes
void printIndiv(Individu individu);
Individu initRandomIter();
Individu initRandomRec();
int convertIndivToInt(Individu individu);
void crossTwoLists(Individu individu1, Individu individu2);
float quality(int value);

#endif // INDIVIDU_H