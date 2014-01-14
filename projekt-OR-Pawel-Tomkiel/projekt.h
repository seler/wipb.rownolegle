//#define N 5 //ilość osobników w populacji
//#define S 3 //długość osobnika
#define K_MAX 10 //maksymalna ilość tworzonych populacji
#define P_MUT 0.5 //prawdopodobieństwo progowe mutacji

#define SALT 12756483 //stała sól do randoma

extern int k;
extern int N;
extern int S;
extern int* wielomian;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "osobnik.h"
#include "populacja.h"


