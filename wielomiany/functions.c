#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// staly seed, zeby miec taki sam random dla roznych wersji algorytmu
#define CONST_SEED 1234
// ilosc osobnikow w populacji
#define CONST_N 1234


double horner(double coefficients[], int deg, int x){
    int c;
    double result;

    result = 0;
    for (c = 0; c < deg; c++){
        result = result * x + coefficients[c];
    }
    return result;
}


int horner_test(){
    // (6*5**5)+(5*5**4)+(4*5**3)+(3*5**2)+(2*5**1)+(1*5**0)
    double coefficients[6] = {6, 5, 4, 3, 2, 1};
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

void print_population(double** population, int s, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("osobnik %d:\n", i + 1);
		print_specimen(population[i], s);
	}
}

double *new_specimen(int s){
	double *specimen;
	int i;

	specimen = (double*) calloc(s, sizeof *specimen);

	for(i = 0; i < s; i++){
		specimen[i] = rand_float(-1, 1);
	}
	return specimen;
}

int new_specimen_test(){
	int i;
	double *specimen;

	specimen = new_specimen(10);
	print_specimen(specimen, 10);
	return 1;
}


double **create_population(int s, int n){
	int i;
	double **population;

	population = (double**) calloc(n, sizeof **population);

	for(i = 0; i < n; i++){
		population[i] = new_specimen(s);
	}
	return population;
}

int create_population_test(){
	double **population;
	population = create_population(10, 10);
	print_population(population, 10, 10);
}

double specimen_fitness(double* specimen, int s, int x){
	return horner(specimen, s, x);
}

int specimen_fitness_test(){
	printf("fitness: %f\n", specimen_fitness(new_specimen(10), 10, 10));
	return 1;
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

int population_fitness_test(){
	double **population;
	double *fitness;
	int i;
	population = create_population(10, 10);
	fitness = population_fitness(population, 10, 10, 10);

	for(i = 0; i < 10; i++){
		printf("population fitness: %f\n", fitness[i]);
	}

	return 1;
}

int partition(double **populacja, double *klucz, int s, int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
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
			sp = populacja[i];
			populacja[i] = populacja[j];
			populacja[j] = sp;
			i++;
			j--;
		}
		else // gdy i >= j zwracamy j jako punkt podzialu tablicy
			return j;
	}
}

void quicksort(double **population, double *fitness, int s, int p, int r) // sortowanie szybkie, r ma byc ilosc liczb - 1
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
	double **population;
	double *fitness;
	int i, f;

	population = create_population(10, 10);
	fitness = population_fitness(population, 10, 10, 10);

	quicksort(population, fitness, 10, 0, 10 - 1);

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


double **select_new_breed(double **p1, double *f1, double **p2, double *f2, int s, int n){
	double **population;
	double **tmp_population;
	double *specimen;
	double *tmp_fitness;
	int i, j, k;
	tmp_population = (double**) calloc(2 * n, sizeof **population);
	population = (double**) calloc(n, sizeof **population);
	tmp_fitness = (double*) calloc(2 * n, sizeof *tmp_fitness);

	specimen = (double*) calloc(s, sizeof *specimen);

	j = 0;
	for(i = 0; i < n; i++){
		tmp_population[j] = (double*) malloc(s * sizeof *specimen);
		for(k = 0; k < s; k++){
		    tmp_population[j][k] = p1[i][k];
		}
		tmp_fitness[j] = f1[i];
		j++;
	}
	for(i = 0; i < n; i++){
		tmp_population[j] = (double*) malloc(s * sizeof *specimen);
		for(k = 0; k < s; k++){
		    tmp_population[j][k] = p2[i][k];
		}
		tmp_fitness[j] = f2[i];
		j++;
	}

	quicksort(tmp_population, tmp_fitness, s, 0, n);

	j = 0;
	for(i = 0; i < n; i++){
		population[j] = (double*) malloc(s * sizeof *specimen);
		for(k = 0; k < s; k++){
		    population[j][k] = tmp_population[i][k];
		}
		j++;
	}
	for(i = 0; i < n; i++){
		free(tmp_population[j]);
		j++;
	}
	free(tmp_population);
	free(tmp_fitness);

	return population;
}
int select_new_breed_test(){
	double **p1;
	double **p2;
	double **p3;
	double *f1;
	double *f2;
	double *f3;
	int i;

	p1 = create_population(10, 10);
	f1 = population_fitness(p1, 10, 10, 2);
	p2 = create_population(10, 10);
	f2 = population_fitness(p2, 10, 10, 2);

	p3 = select_new_breed(p1, f1, p2, f2, 10, 10);
	f3 = population_fitness(p3, 10, 10, 2);

	for(i = 0; i < 10; i++){
		printf("population fitness: %f\n", f3[i]);
	}

	return 1;
}

void feel_free(double **p, int n){
	int i;
	for(i = 0; i < n; i++){
		free(p[i]);
	}
	free(p);
}

/*

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
