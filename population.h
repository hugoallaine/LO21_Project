// LO21 Project
// Author: Hugo Allainé - Léo Angonnet
// population.h

#ifndef POPULATION_H
#define POPULATION_H

#include "individu.h"

typedef struct _liste_individu {
    Individu individu;
    float quality;
    struct _liste_individu* next;
} Liste_Individu;

typedef Liste_Individu* Population;

#endif // POPULATION_H