#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "omp.h"

// staly seed, zeby miec taki sam random dla roznych wersji algorytmu
#define CONST_SEED 1234
// ilosc osobnikow w populacji


double horner(int coefficients[], int deg, double x){
    int c;
    double result;

    result = 0;
    for (c = 0; c < deg; c++){
        result = result * x + (double)coefficients[c];
    }
    return result;
}

int rand_int(int min, int max){
    return (rand() % (max + 1 - min)) + min;
}

double rand_float(double min, double max){
    return (((float)rand() / (float)RAND_MAX) * (max - min)) + min;
}


void do_the_job(int s, int n, int t, int max_k, int coefficients[]){
    int i, j, m, p, o, k;
    double ftmp, ftmp1, ftmp2;
    int num_threads;


    // ten sposob powoduje przepelnienie stosu dlatego robimy mallocami
    //double population[2 * n][s];
    //double fitness[2 * n];

    // alokowanie pamieci
    double **population = malloc(sizeof *population * n * 2);
    for (i = 0; i < (n * 2); i++){
        population[i] = malloc(sizeof *population[i] * s);
    }
    double *fitness = malloc(sizeof *fitness * n * 2);

    // generowanie nowej populacji
    #pragma omp parallel
    {
        int omp_i, omp_j;
        #pragma omp for
        for(omp_i = 0; omp_i < n; omp_i++){
            for(omp_j = 0; omp_j < s; omp_j++){
                population[omp_i][omp_j] = rand_float(-1, 1);
            }
        }
    }

    // wyswietlanie populacji
    //for(i = 0; i < n; i++){
    //    printf("osobnik %d (%f):\n", i + 1, fitness[i]);
    //    for(j = 0; j < s; j++){
    //        printf("%f\n", population[i][j]);
    //    }
    //}

    // petla generacji
    for (k = 0; k < max_k; ++k){
        // krzyzowanie i mutacja
        // obliczanie fitness
        #pragma omp parallel
        {
            int omp_i, omp_j, omp_p, omp_o, omp_m;
            double omp_ftmp1, omp_ftmp2, omp_ftmp;
            #pragma omp for 
            for(omp_m = 0; omp_m < n; omp_m++){
                omp_i = rand_int(0, n);
                omp_j = rand_int(0, n);
                omp_p = rand_int(0, s);
                omp_ftmp1 = 0;
                omp_ftmp2 = 0;
                for(omp_o = 0; omp_o < s; omp_o++){
                    if (rand_int(0, 1000) < t){
                        omp_ftmp = rand_float(-1, 1);
                    } else {
                        omp_ftmp = population[omp_i][omp_o];
                    }
                    if(omp_o < omp_p){
                        population[n + omp_m][omp_o] = omp_ftmp;
                    } else {
                        population[n + omp_m][omp_o] = omp_ftmp;
                    }
                    omp_ftmp1 += horner(coefficients, s, population[omp_m][omp_o]);
                    omp_ftmp2 += horner(coefficients, s, population[n + omp_m][omp_o]);
                }
                fitness[omp_m] = omp_ftmp1;
                fitness[n + omp_m] = omp_ftmp1;
            }
        }

        //  wyswietlanie populacji
        //for(i = 0; i < n; i++){
        //    printf("osobnik %d (%f):\n", i + 1, fitness[i]);
        //    for(j = 0; j < s; j++){
        //        printf("%f\n", population[i][j]);
        //    }
        //}

        // wyswietlanie fitness
        //for(i = 0; i < n; i++){
        //    printf("fitness %f:\n", fitness[i]);
        //}


        // sortowanie babelkowe - wybranie najlepszych osobnikow
        //printf("sortowanie\n");
        for (i = 0; i<(n*2); i++)
        {
            int stop = 0;
            int first = i % 2;

            #pragma omp parallel 
            {
                int omp_j, omp_m;
                double tmp_f;
                double tmp_p[s];
                #pragma omp for reduction(+:stop)
                for (omp_j=first; omp_j<(n*2)-1-i; omp_j+=2){
                    if (fitness[omp_j] > fitness[omp_j+1]){
                        stop += 1;
                        tmp_f = fitness[omp_j+1];
                        for(omp_m = 0; omp_m < s; omp_m++){
                            tmp_p[omp_m] = population[omp_j+1][omp_m];
                        }
                        fitness[omp_j+1] = fitness[omp_j];
                        for(omp_m = 0; omp_m < s; omp_m++){
                            population[omp_j+1][omp_m] = population[omp_j][omp_m];
                        }
                        fitness[omp_j] = tmp_f;
                        for(omp_m = 0; omp_m < s; omp_m++){
                            population[omp_j][omp_m] = tmp_p[omp_m];
                        }
                    }
                }
            }
            if(!stop){
                break;
            }
        }
    }

    // wyswietlanie populacji
    //for(i = 0; i < n; i++){
    //    printf("osobnik %d (%f):\n", i + 1, fitness[i]);
    //    for(j = 0; j < s; j++){
    //        printf("%f\n", population[i][j]);
    //    }
    //}

    //  wyswietlanie najlepszego osobnika
    printf("najlepszy osobnik fitness %f\n", fitness[0]);
    //for(j = 0; j < s; j++){
    //printf("%f\n", population[0][j]);
    //}


    // zwalnianie pamieci
    for (i = 0; i < (n * 2); i++){
        free(population[i]);
    }
    free(population);
    free(fitness);
}


int main(int argc, char const *argv[]){

    int s, n, t, k, i, o;


    if(argc != 6){
        fprintf(stderr, "Usage: %s s n t k o\n\ns - stopien wielomianu\nn - wielkosc populacji\nt - liczba T w przedziale 0 - 1000\nk - ilosc generacji\no - ilosc watkow\n\n", argv[0]);
        return 1;
    }

    s = atoi(argv[1]);
    n = atoi(argv[2]);
    t = atoi(argv[3]);
    k = atoi(argv[4]);
    o = atoi(argv[5]);

    int coefficients[s];


    srand(CONST_SEED);

    for(i = 0; i < s; i++){
        coefficients[i] = rand_int(-100, 100);
    }

    srand(time(NULL) + rand());

    omp_set_num_threads(o);

    do_the_job(s, n, t, k, coefficients);

    return 0;
}


