// LO21 Project
// Author: Hugo Allainé - Léo Angonnet
// bits.h

#ifndef INDIVIDU_H
#define INDIVIDU_H

#define longIndiv 8
#define A -1
#define B 1

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