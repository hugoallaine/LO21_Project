// LO21 Project
// Author: Hugo Allainé - Léo Angonnet
// main.c

#include "population.h"
#include "individu.h"

int main()
{
    srand(time(0));
    int taillePop = rand() % 181 + 20;                      // 20 <= taillePop <= 200
    int tselect = rand() % 81 + 10;                         // 10% <= tselect <= 90% de taillePop
    tselect = (taillePop * tselect / 100.0);
    int nGen = rand() % 181 + 20;                           // 20 <= nGen <= 200

    //int taillePop = 10;
    //int tselect = 7;

    printf("Taille de la population: %d\n", taillePop);
    printf("tselect: %d\n", tselect);
    printf("nGen: %d\n", nGen);

    printf("Starting analysis...\n");

    Population population = initPopulation(taillePop);
    for(int i = 0; i < nGen; i++) {                         // Loop for nGen generations
        //printPop(population);
        crossPop(population, taillePop);                    // Cross the population
        //printPop(population);
        population = sortPopByQuality(population);          // Sort the population by quality
        //printPop(population);
        population = selectBest(population, tselect);       // Select the best individuals
        //printPop(population);
        //if(i == 0){
        //    exit(0);
        //}
    }

    printf("Analysis done\n");

    printf("The best individual have %d of value and %f of quality\n", convertIndivToInt(population->individu), calc_quality(convertIndivToInt(population->individu)));
    deletePop(population);                                  // Free the memory

    return 0;
}