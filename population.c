// LO21 Project
// Author: Hugo Allainé - Léo Angonnet
// population.c

#include "population.h"

void printQuality(Population population) {
    Population temp = population;
    while (temp != NULL) {
        printf("%f,%f\n", calc_quality(convertIndivToInt(temp->individu)),temp->quality);
        temp = temp->next;
    }
}

void printPop(Population population) {
    Population temp = population;
    while (temp != NULL) {
        printIndiv(temp->individu);
        printf("Value: %d\n", convertIndivToInt(temp->individu));
        printf("Quality: %f\n", temp->quality);
        temp = temp->next;
    }
    printf("Fin PrintPop\n");
}

// Initialize the population with random individuals
Population initPopulation(int taillePop) {
    Population population = (Population) malloc(sizeof(Liste_Individu));                    // Create the first element of the list
    population->individu = initRandomIter();                                                // Create a random Individu to the first element
    population->quality = calc_quality(convertIndivToInt(population->individu));            // Set the quality of the first element
    population->prev = NULL;                                                                // Set the previous element to NULL
    Population temp = population;                                                           // Create a temporary pointer to the first element
    for (int i = 1; i < taillePop; i++) {                                                   // Loop to create the rest of the list
        Population newPopulation = (Population) malloc(sizeof(Liste_Individu));             // Create the new element
        newPopulation->individu = initRandomIter();                                         // Create a random Individu to the new element
        newPopulation->quality = calc_quality(convertIndivToInt(newPopulation->individu));  // Set the quality of the new element
        newPopulation->next = NULL;                                                         // Set the next element to NULL                                                      
        newPopulation->prev = temp;                                                         // Set the previous element to the previous element
        temp->next = newPopulation;                                                         // Set the next element of the previous element to the new element
        temp = temp->next;                                                                  // Set the temporary pointer to the new element
    }
    return population;
}

/* A utility function to swap two elements */
void swap(Population a, Population b) {
    Individu tmp = a->individu;
    a->individu = b->individu;
    b->individu = tmp;
    float tmp2 = a->quality;
    a->quality = b->quality;
    b->quality = tmp2;
}

/* Considers last element as pivot, places the
pivot element at its correct position in sorted array,
and places all smaller (smaller than pivot) to left
of pivot and all greater elements to right of pivot */
Population partition(Population l, Population h)
{
	// set pivot as h element
	float x = h->quality;

	// similar to i = l-1 for array implementation
	Population i = l->prev;

	// Similar to "for (int j = l; j <= h- 1; j++)"
	for (Population j = l; j != h; j = j->next)
	{
		if (j->quality >= x)
		{
			// Similar to i++ for array
			i = (i == NULL) ? l : i->next;

			swap(i, j);
		}
	}
	i = (i == NULL) ? l : i->next; // Similar to i++
	swap(i, h);
	return i;
}

/* A recursive implementation of quicksort for linked list */
void quickSort(Population l, Population h)
{
	if (h != NULL && l != h && l != h->next)
	{
		Population p = partition(l, h);
		quickSort(l, p->prev);
		quickSort(p->next, h);
	}
}

// Sort the list by decreasing Quality of the Individuals by means of Quicksort. 
// We will use for that the Quality function defined on the abstract type Individual.
Population sortPopByQuality(Population population) {
    if (population == NULL || population->next == NULL) {                           // If the list is empty or has only one element
        return population;
    }
    Population start = population;                                                 // Create a temporary pointer to the first element
    Population end = population;                                                   // Create a temporary pointer to the last element
    while (end->next != NULL) {                                                     // Loop to find the last element
        end = end->next;
    }
    quickSort(start, end);                                                          // Call the quicksort function
    return population;
}

// Select the best Individuals of the Population by truncating the list and completing it by copying the
// tSelect first elements. 
Population selectBest(Population population, int tselect) {
    Population temp1 = population;                                                  // Create a temporary pointer to the first element
    Population temp2 = population;                                                  // Create a second temporary pointer to the first element
    for (int i = 0; i < tselect; i++) {                                            // Loop to skip the tselect elements
        if (temp2->next == NULL) {                                                  // If we are at the end of the list
            return population;
        }
        temp2 = temp2->next;
    }
    while (temp2 != NULL) {                                                         // Loop to copy the tSelect first elements
        temp2->individu = temp1->individu;                                          // Copy the tSelect elements
        temp2->quality = temp1->quality;

        temp1 = temp1->next;                                                        // Set the temporary pointer to the next element
        temp2 = temp2->next;                                                        // Set the first temporary pointer to the next element
    }
    return population;
}

// Create a new Population by crossing randomly Individuals of the Population P1.
void crossPop(Population P1, int taillePop) {
    Population temp1 = P1;                                                      // Create a temporary pointer to the first element
    Population temp2 = P1;                                                      // Create a second temporary pointer to the first element
    int rand1;                                                                  // Create a random variable               
    int rand2;                                                                  // Create a second random variable
    for (int i = 0; i < taillePop; i++) {                                       // Loop to create the new Population with same size as the first one
        do {                                                                    
            rand1 = (rand() % taillePop);                                       // Create two random numbers   
            rand2 = (rand() % taillePop);
        } while (rand1 == rand2);                                               // If the two random numbers are the same, we create new ones
        for (int j = 0; j < rand1; j++) {                                       // Move the first temporary pointer to the Individu corresponding to the first random number                
            temp1 = temp1->next;
        }
        for (int j = 0; j < rand2; j++) {                                       // Move the second temporary pointer to the Individu corresponding to the second random number
            temp2 = temp2->next;
        }
        crossTwoLists(temp1->individu, temp2->individu);                        // Cross the two Individu
        temp1->quality = calc_quality(convertIndivToInt(temp1->individu));           // Get the quality of the new Individu1
        temp2->quality = calc_quality(convertIndivToInt(temp2->individu));           // Get the quality of the new Individu2       
        temp1 = P1;                                                             // Reset the temporary pointers                                      
        temp2 = P1;                                 
    }
}

void deletePop(Population population) {
    Population temp = population;                                               // Create a temporary pointer to the first element
    while (temp != NULL) {                                                      // Loop to delete the list
        temp = temp->next;                                                      // Set the temporary pointer to the next element
        free(population);                                                       // Delete the previous element
        population = temp;                                                      // Set the previous element to the temporary pointer
    }
}