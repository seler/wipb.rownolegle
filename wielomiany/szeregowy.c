#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "functions.h"

// staly seed, zeby miec taki sam random dla roznych wersji algorytmu
#define CONST_SEED 1234
// ilosc osobnikow w populacji
#define CONST_N 1234



void do_the_job(int s, int n, int x, int k){
	int i, j;
	double **population;
	double **tmp_population;
	double **new_population;
	double *fitness;
	double *tmp_fitness;


	population = create_population(s, n);

	//print_population(population, s, n);
    fitness = population_fitness(population, s, n, x);
    //printf("fitness: %f\n", fitness[0]);

	for(i = 0; i < k; i++){
        // 1. zmutowana populacja na podstawie poprzedniej
	    tmp_population = create_population(s, n);
		//print_population(tmp_population, s, n);
        // 2. oblicz fitness
        tmp_fitness = population_fitness(tmp_population, s, n, x);
		//printf("tmp fitness: %f\n", tmp_fitness[0]);
        // 3. umieść w nowej populacji najlepsze osobniki z starej i zmutowanej populacji
		new_population = select_new_breed(tmp_population, tmp_fitness, population, fitness, s, n);
		feel_free(population, s);
		population = new_population;
		//free(new_population);
		feel_free(tmp_population, s);
		free(tmp_fitness);
	}
	/* 
	printf("ibce:\n");
	for(j = 0; j < s; j++){
		printf("%f ", horner(population[j], s, x));
		printf("%f ", horner(tmp_population[j], s, x));
		printf("%f\n", horner(population[j], s, x));
	}
	printf("fitness: %f\n", specimen_fitness(population[0], s, x));
	*/
}


int main(int argc, char const *argv[]){

	// dlugosc osobnika
	int s;
	// wielkosc populacji
	int n;
	// wartosc dla ktorej obliczamy fitness
	int x;
	// ilosc generacji
	int k;
	// licznik do petli
	int i;

    // for s in 4 16 64 256 512 1024
	s = atoi(argv[1]);
	//n = ((1024 * 1024) / s) - s + 10;
	n = atoi(argv[2]);
	//x = 2;
	x = atoi(argv[3]);
	k = atoi(argv[4]);

	for(i = 10; i > 0; i--){
		srand(CONST_SEED);
        do_the_job(s, n, x, k);
	}

    return 0;
}


