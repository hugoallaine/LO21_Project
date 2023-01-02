// LO21 Project
// Author: Hugo Allainé - Léo Angonnet
// individu.h

#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define longIndiv 8     // 8 ou 16 selon le mode
#define A -1            // -1 ou 0.1 selon le mode
#define B 1             // 1 ou 5 selon le mode
#define pCross 0.5
//#define useF2 1         // Commenter pour utiliser f1

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
float calc_quality(int value);

#endif // INDIVIDU_H