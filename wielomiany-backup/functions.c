#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// staly seed, zeby miec taki sam random dla roznych wersji algorytmu
#define CONST_SEED 1234
// ilosc osobnikow w populacji
#define CONST_N 1234


void feel_free(double **p, int n){
	int i;
	for(i = 0; i < n; i++){
		free(p[i]);
	}
	free(p);
}

double horner(int coefficients[], int deg, double x){
    int c;
    double result;

    result = 0;
    for (c = 0; c < deg; c++){
        result = result * x + (double)coefficients[c];
    }
    return result;
}


int horner_test(){
    // (6*5**5)+(5*5**4)+(4*5**3)+(3*5**2)+(2*5**1)+(1*5**0)
    int coefficients[6] = {6, 5, 4, 3, 2, 1};
    return 22461 == horner(coefficients, 6, 5);
}

double rand_float(double min, double max){
    return (((float)rand() / (float)RAND_MAX) * (max - min)) + min;
}

int rand_float_test(){
	int result;
	double value;
	value = rand_float(-10, 10);
	if(value >= -10 && value <= 10){
		result = 1;
	} else {
		result = 0;
	}
	return result;
}


int rand_int(int min, int max){
	return (rand() % (max + 1 - min)) + min;
}

int rand_int_test(){
	int result;
	int value;
	value = rand_int(-10, 10);
	if(value >= -10 && value <= 10){
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

void print_specimen(double* specimen, int s){
	int i;
	for(i = 0; i < s; i++){
		printf("%f\n", specimen[i]);
	}
}

void print_population(double* population, int s, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("osobnik %d:\n", i + 1);
		print_specimen(&population[i], s);
	}
}

void new_specimen(double *specimen, int s){
	int i;

	for(i = 0; i < s; i++){
		specimen[i] = rand_float(-1, 1);
	}
}

int new_specimen_test(){
	int i;
	double specimen[10];

	new_specimen(specimen, 10);
	print_specimen(specimen, 10);
	return 1;
}


void create_population(double* population, int s, int n){
	int i;

	for(i = 0; i < n; i++){
		new_specimen(&population[i], s);
	}
}

int create_population_test(){
	double population[10][10];
	create_population(&population[0][0], 10, 10);
	print_population(&population[0][0], 10, 10);
    return 1;
}

double specimen_fitness(double *specimen, int s, int x){
	//return horner(specimen, s, x);
}

int specimen_fitness_test(){
	double specimen[10];
	new_specimen(specimen, 10);
	//printf("fitness: %f\n", specimen_fitness(specimen, 10, 2));
	return 1;
}

void population_fitness(double *fitness, double *population, int s, int n, int x){
    int i;

	for(i = 0; i < n; i++){
		fitness[i] = specimen_fitness(&population[i], s, x);
	}
}

int population_fitness_test(){
    /*
	double population[10][10];
    double fitness[10];
	int i;

	create_population(&population[0][0], 10, 10);
	population_fitness(fitness, &population[0][0], 10, 10, 2);

	for(i = 0; i < 10; i++){
		printf("population fitness: %f\n", fitness[i]);
	}
    */

	return 1;
}

int partition(double *populacja, double *klucz, int s, int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
{
	int i, j;
	double k, w;
	double *sp;
	sp = (double*) malloc(s * sizeof *sp);

	i = p;
   	j = r; // i, j - indeksy w tabeli
	k = klucz[p];

	while (1) // petla nieskonczona - wychodzimy z niej tylko przez return j
	{
		while (klucz[j] > k) // dopoki elementy sa wieksze od x 
			j--;
		while (klucz[i] < k) // dopoki elementy sa mniejsze od x
			i++;
		if (i < j) // zamieniamy miejscami gdy i < j
		{
			w = klucz[i];
			klucz[i] = klucz[j];
			klucz[j] = w;
			*sp = populacja[i];
			populacja[i] = populacja[j];
			populacja[j] = *sp;
			i++;
			j--;
		}
		else // gdy i >= j zwracamy j jako punkt podzialu tablicy
			return j;
	}
    free(sp);
}

void quicksort(double *population, double *fitness, int s, int p, int r) // sortowanie szybkie, r ma byc ilosc liczb - 1
{
	int q;
	if (p < r) 
	{	
		q = partition(population, fitness, s, p,r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
		quicksort(population, fitness, s, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
		quicksort(population, fitness, s, q+1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
	}
}

int quicksort_test(){
	double f;
	double population[10][10];
    double fitness[10];
	int i;

	create_population(&population[0][0], 10, 10);
	population_fitness(fitness, &population[0][0], 10, 10, 2);

	quicksort(&population[0][0], fitness, 10, 0, 10 - 1);

	f = fitness[0];
	printf("quicksort population fitness: %f\n", fitness[0]);
	for(i = 1; i < 10; i++){
		printf("quicksort population fitness: %f\n", fitness[i]);
		if(f > fitness[i]){
			return 0;
		}
		f = fitness[i];
	}
	return 1;
}


void select_new_breed(double *p1, double *f1, double *p2, double *f2, int s, int n){
	double tmp_population[2 * n][s];
	double tmp_fitness[2 * n];
	int i, j, k;

    print_population(p1, s, n);


	for(i = 0; i < n; i++){
		for(k = 0; k < s; k++){
            //printf("%f", p1[i][k]);
		    //tmp_population[i][k] = p1[i][k];
		    //tmp_population[i + n][k] = p2[i][k];
		}
		tmp_fitness[i] = f1[i];
		tmp_fitness[i + n] = f2[i];
		j++;
	}

/*
	j = 0;
	for(i = 0; i < n; i++){
		for(k = 0; k < s; k++){
		    tmp_population[j][k] = p1[i][k];
		}
		tmp_fitness[j] = f1[i];
		j++;
	}
	for(i = 0; i < n; i++){
		for(k = 0; k < s; k++){
		    tmp_population[j][k] = p2[i][k];
		}
		tmp_fitness[j] = f2[i];
		j++;
	}

	quicksort(&tmp_population[0][0], tmp_fitness, s, 0, n - 1);

	j = 0;
	for(i = 0; i < n; i++){
		for(k = 0; k < s; k++){
		    p1[j][k] = tmp_population[i][k];
		}
		j++;
	}

*/
}

/*
int select_new_breed_test(){
	int i, s, n;
    s = 10;
    n = 10;
	double p1[s][n];
	double p2[s][n];
    double f1[n];
    double f2[n];

	create_population(&p1[0][0], s, n);
	population_fitness(f1, &p1[0][0], s, n, 2);
	create_population(&p2[0][0], s, n);
	population_fitness(f2, &p2[0][0], s, n, 2);

	//quicksort(&p1[0][0], f1, n, 0, n - 1);
    
	for(i = 0; i < 10; i++){
		printf("population fitness: %f\n", f1[i]);
	}

	select_new_breed(&p1[0][0], f1, &p1[0][0], f1, s, n);

	for(i = 0; i < 10; i++){
		printf("population fitness: %f\n", f1[i]);
	}

	return 1;
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





int cross_specimens_test(){}
int mutate_population_test(){}
*/
