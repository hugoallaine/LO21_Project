// LO21 Project
// Author: Hugo Allainé - Léo Angonnet
// individu.c

#include "individu.h"

/*
Write the algorithm and the C subroutine corresponding to the following operations:
• Randomly initialize the list of bits (give an iterative version and a recursive version of this operation).
• Decode the list of bits and give the corresponding integer value.
• Cross two lists of bits, ie invert the elements of the two lists according to a given probability
(pCross) for each position in the list (random draw and comparison with the probability).
*/

// Randomly initialize the list of bits (iterative version)
Individu initRandomIter() {
    Individu individu = (Individu) malloc(sizeof(Individu));                    // Creation of the first element of the list
    individu->value = rand() % 2;                                               // Give a random value to the first element
    Individu *temp = individu;                                                  // Create a temporary pointer to the first element
    for (int i = 0; i < longIndiv; i++) {                                       // Loop to create the rest of the list
        Individu nouvelIndividu = (Individu) malloc(sizeof(Individu));          // Creation of the new element
        nouvelIndividu->value = rand() % 2;                                     // Give a random value to the new element
        nouvelIndividu->next = NULL;                                            // Set the next element to NULL
        temp->next = nouvelIndividu;                                            // Set the next element of the previous element to the new element
        temp = temp->next;                                                      // Set the temporary pointer to the new element
    }
    return individu;
}

// Randomly initialize the list of bits (recursive version)
Individu initRandomRec(Individu individu) {
    int i = 0;                                                                  // Create a counter
    return initRandomRecIn(individu, i);                                        // Call the function with the first element
}

Individu initRandomRecIn(Individu individu, int i) {
    if (i == longIndiv) {                                                       // Check if the list is full
        return individu;                                                        // Return the list
    }
    else {                                                                      // If the list is not full
        Individu nouvelIndividu = (Individu) malloc(sizeof(Individu));          // Create the new element
        nouvelIndividu->value = rand() % 2;                                     // Give a random value to the new element
        nouvelIndividu->next = NULL;                                            // Set the next element to NULL
        individu->next = nouvelIndividu;                                        // Set the next element of the previous element to the new element
        return initRandomRecIn(individu->next, i + 1);                          // Call the function again with the next element
    }
}

// Decode the list of bits and give the corresponding integer value
int convertIndivToInt(Individu individu) {
    int value = 0;                                                              // Create a variable to store the value
    int i = longIndiv-1;                                                        // Create a counter starting at the length of the list
    while (individu != NULL) {                                                  // Loop to go through the list
        value += individu->value * (1 << i);                                    // Add the value of the current element to the value
        individu = individu->next;                                              // Go to the next element
        i--;                                                                    // Decrease the counter
    }
    return value;                                                               // Return the value
}

// Cross two lists of bits (i.e invert the elements of the two lists according to a given probability)
void crossTwoLists(Individu individu1, Individu individu2) {
    Individu *temp1 = individu1;                                                // Create a temporary pointer to the first list
    Individu *temp2 = individu2;                                                // Create a temporary pointer to the second list
    while (temp1 != NULL && temp2 != NULL) {                                    // Loop to go through the lists
        if (rand() % 100 < pCross * 100) {                                      // Check if the random value is lower than the probability
            int temp = temp1->value;                                            // Create a temporary variable to store the value of the first element
            temp1->value = temp2->value;                                        // Set the value of the first element to the value of the second element
            temp2->value = temp;                                                // Set the value of the second element to the value of the first element
        }
        temp1 = temp1->next;                                                    // Go to the next element of the first list
        temp2 = temp2->next;                                                    // Go to the next element of the second list
    }
}

// Calculate the quality of an individual from its value
float quality(int value) {
    float square = 2;
    for (int i = 0; i < longIndiv; i++) {
        square += square;
    }
    float X = (value/square)*(B-A)+A;
    float quality = -(X*X);
    return quality;
}