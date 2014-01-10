#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

double horner(double coefficients[], int deg, int x);
int horner_test();

double rand_float(double min, double max);
int rand_float_test();

int rand_int(int min, int max);
int rand_int_test();

double *new_specimen(int s);
int new_specimen_test();

double **create_population(int s, int n);
int create_population_test();

double specimen_fitness(double* specimen, int s, int x);
int specimen_fitness_test();

double *population_fitness(double **population, int s, int n, int x);
int population_fitness_test();

void quicksort(double **population, double *fitness, int s, int p, int r);
int quicksort_test();

double **select_new_breed(double **p1, double *f1, double **p2, double *f2, int s, int n);
int select_new_breed_test();

void feel_free(double **p, int n);

/*
double* cross_specimens(double *s1, double *s2, int s);
int cross_specimens_test();

void print_specimen(double* specimen, int s);

void print_population(double** population, int s, int n);

double** mutate_population(double **old_population, int s, int n);
int mutate_population_test();

int partition(double **populacja, double *klucz, int s, int p, int r);

void do_the_job(int s, int n, int x, int k);
*/
