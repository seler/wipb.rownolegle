#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// staly seed, zeby miec taki sam random dla roznych wersji algorytmu
#define CONST_SEED 1234
// ilosc osobnikow w populacji
#define CONST_N 1234


double horner(double coefficients[], int deg, int x);
int horner_test();

double rand_float(double min, double max){
    return (((float)rand() / (float)RAND_MAX) * (max - min)) + min;
}

int rand_int(int min, int max){
	return (rand() % (max + 1 - min)) + min;
}

double* new_specimen(int s){
	// s - długość osobnika
	int i;
	double *specimen;
	specimen = (double*) malloc(s * sizeof *specimen);

	for(i = 0; i < s; i++){
		specimen[i] = rand_float(-1, 1);
	}
	return specimen;
}

double* cross_specimens(double *s1, double *s2, int s){
	int i;
	double *specimen;
	specimen = (double*) malloc(s * sizeof *specimen);

	for(i = 0; i < s; i++){
		specimen[i] = rand_float(-1, 1);
	}
	return specimen;
}

void print_specimen(double* specimen, int s){
	int i;
	for(i = 0; i < s; i++){
		printf("%f\n", specimen[i]);
	}
}

void print_population(double** population, int s, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("osobnik %d:\n", i + 1);
		print_specimen(population[i], s);
	}
}

double** create_population(int s, int n){
	int i;
	// wskaznik na populacje
	double **population;
	// wskaznik na osobnika
	double *specimen;
	population = (double**) malloc(n * sizeof **population);

	for(i = 0; i < n; i++){
		specimen = new_specimen(s);
		population[i] = specimen;
	}
	return population;
}

double** mutate_population(double **old_population, int s, int n){
	int i;
	// wskaznik na populacje
	double **population;
	// wskaznik na osobnika
	double *specimen;
	double *s1;
	double *s2;
	population = (double**) malloc(n * sizeof **population);

	for(i = 0; i < n; i++){
        s1 = old_population[rand_int(0, s)];
        s2 = old_population[rand_int(0, s)];
		specimen = cross_specimens(s1, s2, s);
		population[i] = specimen;
	}
	return population;
}

double specimen_fitness(double* specimen, int s, int x){
	return horner(specimen, s - 1, x);
}

double *population_fitness(double **population, int s, int n, int x){
    int i;
	double *fitness;

	fitness = (double*) malloc(n * sizeof *fitness);

	for(i = 0; i < n; i++){
		fitness[i] = specimen_fitness(population[i], s, x);
	}
    return fitness;
}

void do_the_job(int s, int n, int x, int k){
	int i;
	double **population;
	double **tmp_population;
	double **new_population;
	double *fitness;
	double *tmp_fitness;

	new_population = (double**) malloc(n * sizeof **new_population);

	population = create_population(s, n);
    fitness = population_fitness(population, s, n, x);

	//print_population(population, s, n);
    // printf("fitness: %f\n", fitness[i]);
	for(i = 0; i < k; i++){
        // 1. zmutowana populacja na podstawie poprzedniej
	    tmp_population = mutate_population(population, s, n);
        // 2. oblicz fitness
        tmp_fitness = population_fitness(tmp_population, s, n, x);
        // 3. umieść w nowej populacji najlepsze osobniki z starej i zmutowanej populacji
	}
	// printf("fitness: %f\n", specimen_fitness(population[i], s, x));
}


int main(int argc, char const *argv[]){
    srand(CONST_SEED);

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
	// wskaznik na populacje
	double **population;

    // for s in 4 16 64 256 512 1024
	s = atoi(argv[1]);
	//n = ((1024 * 1024) / s) - s + 10;
	n = atoi(argv[2]);
	//x = 2;
	x = atoi(argv[3]);
	k = atoi(argv[4]);

	for(i = 10; i > 0; i--){
        do_the_job(s, n, x, k);
	}

    return 0;
}


double horner(double coefficients[], int deg, int x){
    int c;
    double result;

    result = 0;
    for (c = 0; c <= deg; c++){
        result = result * x + coefficients[c];
    }
    return result;
}


int horner_test(){
    // (6*5**5)+(5*5**4)+(4*5**3)+(3*5**2)+(2*5**1)+(1*5**0)
    double coefficients[6] = {6, 5, 4, 3, 2, 1};
    return 22461 != horner(coefficients, 5, 5);
}
