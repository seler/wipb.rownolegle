#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// staly seed, zeby miec taki sam random dla roznych wersji algorytmu
#define CONST_SEED 1234
// ilosc osobnikow w populacji
#define CONST_N 1234
/*
Zaimplementować szeregową i przynajmniej jedną równoległą wersję algorytmu.  Sporządzić wykresy 
przyspieszenia (speedup) i wydajności (efficiency) zmieniając liczbę procesów od 1 do 10, dla:
S = 4, 16, 64, 256, 512, 1024, oraz 
N = (1024*1024)/S - S + 10. 
Dla każdej wartości S należy przeprowadzić 10 tur obliczeń, przy czym tura wersji szeregowej 
powinna trwać ok. minuty.
*/


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

double** new_population(int s, int n){
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

double specimen_fitness(double* specimen, int s, int x){
	return horner(specimen, s - 1, x);
}


int main(int argc, char const *argv[]){
    srand(CONST_SEED);
	// dlugosc osobnika
	int s;
	// wielkosc populacji
	int n;
	// wartosc dla ktorej obliczamy fitness
	int x;
	// licznik do petli
	int i;
	// wskaznik na populacje
	double **population;

	//S = 4, 16, 64, 256, 512, 1024
	s = 4;
	n = ((1024 * 1024) / s) - s + 10;
	x = 2;
	population = new_population(s, n);
	//print_population(population, s, n);
	for(i = 0; i < n; i++){
		//printf("fitness: %f\n", specimen_fitness(population[i], s, x));
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
