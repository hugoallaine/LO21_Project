// LO21 Project
// Author: Hugo Allainé - Léo Angonnet
// population.h

#ifndef POPULATION_H
#define POPULATION_H

#include "individu.h"

// Struct of a population (list of individu) with a quality (float) 
typedef struct _liste_individu {
    Individu individu;              
    float quality;
    struct _liste_individu* next;
    struct _liste_individu* prev;
} Liste_Individu;

// Population
typedef Liste_Individu* Population;

// Function prototypes
void printQuality(Population population);
void printPop(Population population);
Population initPopulation(int longPop);
Population sortPopByQuality(Population population);
Population selectBest(Population population, int tselect);
void crossPop(Population P1, int taillePop);
void deletePop(Population population);

#endif // POPULATION_H