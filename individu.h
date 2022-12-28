// LO21 Project
// Author: Hugo Allainé - Léo Angonnet
// individu.h

#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define longIndiv 8
#define A -1
#define B 1
#define pCross 0.5

typedef unsigned char Bit;

/* Liste de bits
 */
typedef struct _bits{
    Bit value;
    struct _bits* next;
} Bits;

/* Individu
 */
typedef Bits* Individu;

#endif // INDIVIDU_H