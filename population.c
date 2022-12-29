// LO21 Project
// Author: Hugo Allainé - Léo Angonnet
// population.c

#include "population.h"

// Initialize the population with random individuals
Population initPopulation(int taillePop) {
    Population population = (Population) malloc(sizeof(Population));             // Create the first element of the list
    population->individu = initRandomIter();                                     // Create a random Individu to the first element
    population->quality = quality(population->individu);                         // Set the quality of the first element
    population->prev = NULL;                                                     // Set the previous element to NULL
    Population *temp = population;                                               // Create a temporary pointer to the first element
    for (int i = 1; i < taillePop-1; i++) {                                      // Loop to create the rest of the list
        Population newPopulation = (Population) malloc(sizeof(Population));      // Create the new element
        newPopulation->individu = initRandomIter();                              // Create a random Individu to the new element
        newPopulation->quality = quality(newPopulation->individu);               // Set the quality of the new element
        newPopulation->next = NULL;                                              // Set the next element to NULL
        temp->next = newPopulation;                                              // Set the next element of the previous element to the new element
        temp = temp->next;                                                       // Set the temporary pointer to the new element
    }
    return population;
}

void swap(Population *a, Population *b) {
    Population tmp = a;
    a->next = b->next;
    a->prev = b;
    b->prev = tmp->prev;
    b->next = tmp;
    free(tmp);
}

void quickSort(Population start, Population end) {
    Population *tmp_swap, *i, *j;
    if(start->quality > end->quality) {
        tmp_swap = start;
        i = start;
        j = end;
        while (i->quality > j->quality) {
            while(i->quality >= tmp_swap->quality && i->quality > end->quality)
                i = i->next;
            while(j->quality < tmp_swap->quality)
                j = j->prev;
            if(i->quality > j->quality) {
                swap(&i, &j);
            }
        }
        swap(&tmp_swap, &j);
        quickSort(start, j->prev);
        quickSort(j->suivant, end);
    }
}

// Sort the list by decreasing Quality of the Individuals by means of Quicksort. 
// We will use for that the Quality function defined on the abstract type Individual.
Population sortPopByQuality(Population population) {
    if (population == NULL || population->next == NULL) {                           // If the list is empty or has only one element
        return population;
    }
    Population *start = population;                                                 // Create a temporary pointer to the first element
    Population *end = population;                                                   // Create a temporary pointer to the last element
    while (end->next != NULL) {                                                     // Loop to find the last element
        end = end->next;
    }
    quickSort(start, end);                                                          // Call the quicksort function
    return population;
}

// Select the best Individuals of the Population by truncating the list and completing it by copying the
// tSelect first elements. 
Population selectBest(Population population, int tselect) {
    Population *temp1 = population;                                                 // Create a temporary pointer to the first element
    Population *temp2 = population;                                                 // Create a second temporary pointer to the first element
    for (int i = 0; i <= tselect; i++) {                                            // Loop to skip the tselect elements
        temp2 = temp2->next;
    }
    int j = 0;                                                                      // Create a count variable
    while (temp2 != NULL) {                                                         // Loop to copy the tSelect first elements
        temp2->individu = temp1->individu;                                          // Copy the tSelect elements
        temp2->quality = temp1->quality;
        if (j == tselect-1) {                                                       // If we are at the end of the tSelect elements
            temp1 = population;                                                     // Set the temporary pointer to the first element
            j = 0;                                                                  // Reset count
        } else {
            temp1 = temp1->next;                                                    // Set the temporary pointer to the next element
            j++;                                                                    // Increment count
        }
        temp2 = temp2->next;                                                        // Set the first temporary pointer to the next element
    }
    return population;
}


// Create a new Population by crossing randomly Individuals of the Population P1.
Population crossPop(Population P1, int taillePop) {
    Population P2 = (Population) malloc(sizeof(Population));                    // Initialize the new Population
    Population *temp1 = P1;                                                     // Create a temporary pointer to the first element
    Population *temp2 = P1;                                                     // Create a second temporary pointer to the first element
    Population *temp3 = P2;                                                     // Create a third temporary pointer to the first element
    int rand1;                                                                  // Create a random variable               
    int rand2;                                                                  // Create a second random variable
    for (int i = 0; i < taillePop; i++) {                                       // Loop to create the new Population with same size as the first one
        do {                                                                    
            rand1 = (rand() % taillePop);                                       // Create two random numbers   
            rand2 = (rand() % taillePop);                                                    
        } while (rand1 == rand2);                                               // If the two random numbers are the same, we create new ones
        for (int j = 0; j < rand1; j++) {                                       // Move the first temporary pointer to the Individual corresponding to the first random number                
            temp1 = temp1->next;
        }
        for (int j = 0; j < rand2; j++) {                                       // Move the second temporary pointer to the Individual corresponding to the second random number
            temp2 = temp2->next;
        }
        temp3->individu = crossTwoLists(temp1->individu, temp2->individu);              // Cross the two Individuals
        temp3->quality = quality(temp3->individu);                              // Get the quality of the new Individual          
        if (i != taillePop-1) {                                                 // If we are not at the second last element
            temp3->next = (Population) malloc(sizeof(Population));              // Create the next element
            temp3 = temp3->next;                                                // Set the third temporary pointer to the next element
        } else {
            temp3->next = NULL;                                                 // If we are at the last element, set the next element to NULL
        }
        temp1 = P1;                                                            // Reset the temporary pointers                                      
        temp2 = P1;                                 
    }
    return P2;
}