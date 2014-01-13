#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
    double f;
    int i, j, m, p, o, k;
    double ftmp;


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
    for(i = 0; i < n; i++){
        for(j = 0; j < s; j++){
            //printf("dupa n - %d s - %d\n", i, j);
            population[i][j] = rand_float(-1, 1);
        }
    }

    // petla generacji
    for (k = 0; k < max_k; ++k){
        // krzyzowanie i mutacja
        for(m = 0; m < n; m++){
            i = rand_int(0, n);
            j = rand_int(0, n);
            p = rand_int(0, s);
            for(o = 0; o < s; o++){
                if (rand_int(0, 1000) < t){
                    ftmp = rand_float(-1, 1);
                } else {
                    ftmp = population[i][o];
                }
                if(o < p){
                    population[n + m][o] = ftmp;
                } else {
                    population[n + m][o] = ftmp;
                }
            }
        }

        // obliczanie fitness
        for(i = 0; i < (n * 2); i++){
            ftmp = 0;
            for(j = 0; j < s; j++){
                ftmp += horner(coefficients, s, population[i][j]);
            }
            fitness[i] = ftmp;
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
        double tmp_f;
        double tmp_p[s];
        for (i = 0; i<(n*2); i++)
        {
            for (j=0; j<(n*2)-1-i; j++)
            {
                if (fitness[j] > fitness[j+1])
                {
                    tmp_f = fitness[j+1];
                    for(m = 0; m < s; m++){
                        tmp_p[m] = population[j+1][m];
                    }
                    fitness[j+1] = fitness[j];
                    for(m = 0; m < s; m++){
                        population[j+1][m] = population[j][m];
                    }
                    fitness[j] = tmp_f;
                    for(m = 0; m < s; m++){
                        population[j][m] = tmp_p[m];
                    }
                }
            }
        }
    }

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

    int s, n, t, k, i;


    if(argc != 5){
        fprintf(stderr, "Usage: %s s n t k\n\ns - stopien wielomianu\nn - wielkosc populacji\nt - liczba T w przedziale 0 - 1000\nk - ilosc generacji\n\n", argv[0]);
        return 1;
    }

    s = atoi(argv[1]);
    n = atoi(argv[2]);
    t = atoi(argv[3]);
    k = atoi(argv[4]);

    int coefficients[s];

    srand(CONST_SEED);

    for(i = 0; i < s; i++){
        coefficients[i] = rand_int(-100, 100);
    }

    srand(time(NULL) + rand());

    for(i = 1; i > 0; i--){
        do_the_job(s, n, t, k, coefficients);
    }

    return 0;
}


