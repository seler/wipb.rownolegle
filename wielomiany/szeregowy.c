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
	double f;
	double population[10][10];
	double future_population[10][10];
    double fitness[10];
    double future_fitness[10];
	double tmp_population[2 * n][s];
	double tmp_fitness[2 * n];
	int i, j;

	create_population(&population[0][0], s, n);
	population_fitness(fitness, &population[0][0], s, n, x);

	quicksort(&population[0][0], fitness, s, 0, n - 1);

	create_population(&future_population[0][0], s, n);
	population_fitness(future_fitness, &future_population[0][0], s, n, x);

    print_population(&population[0][0], s, n);
    print_population(&population[0][0], s, n);


    for(i = 0; i < n; i++){
        printf("osobnik %d:\n", i + 1);
        print_specimen(population, s);
    }
    /*
	for(i = 0; i < n; i++){
		for(j = 0; j < s; j++){
            printf("asd: %f\n", population[i][j]);
		    //tmp_population[i][k] = p1[i][k];
		    //tmp_population[i + n][k] = p2[i][k];
		}
		tmp_fitness[i] = fitness[i];
		tmp_fitness[i + n] = future_fitness[i];
	}
    for(i = 0; i < (n * 2); i++){
        printf("%d %f\n", n, tmp_fitness[i]);
    }

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
    */
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
		srand(time(NULL));
        do_the_job(s, n, x, k);
	}

    return 0;
}


