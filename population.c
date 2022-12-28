// LO21 Project
// Author: Hugo Allainé - Léo Angonnet
// population.c

#include "population.h"

// Initialize the population with random individuals
Population initPopulation(int longPop) {
    Population population = (Population) malloc(sizeof(Population));             // Create the first element of the list
    population->individu = initRandomIter();                                     // Create a random Individu to the first element
    Population *temp = population;                                               // Create a temporary pointer to the first element
    for (int i = 1; i < longPop; i++) {                                          // Loop to create the rest of the list
        Population newPopulation = (Population) malloc(sizeof(Population));      // Create the new element
        newPopulation->individu = initRandomIter();                              // Create a random Individu to the new element
        newPopulation->next = NULL;                                              // Set the next element to NULL
        temp->next = newPopulation;                                              // Set the next element of the previous element to the new element
        temp = temp->next;                                                       // Set the temporary pointer to the new element
    }
    return population;
}