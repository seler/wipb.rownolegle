#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "functions.h"

void display(char *name, int value){
	if(!value){
		fprintf(stderr, "%s failed\n", name);
	}
}

int main(int argc, char const *argv[]){
    srand(time(NULL));

	display("horner", horner_test());

	display("rand_float", rand_float_test());

	display("rand_int", rand_int_test());

	display("new_specimen", new_specimen_test());

	display("create_population", create_population_test());

	display("specimen_fitness", specimen_fitness_test());

	display("population_fitness", population_fitness_test());

	display("quicksort", quicksort_test());

	//display("select_new_breed", select_new_breed_test());
	/*

	display("cross_specimens", cross_specimens_test());

	display("mutate_population",mutate_population_test());




	*/

    return 0;
}


