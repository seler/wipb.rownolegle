// Copyright (c) 2013 Rafał Selewońko <rafal@selewonko.com>.
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>

double get_pi(int num_threads, int k_max);


int main(int argc, char *argv[]) {
	double pi;
	pi = get_pi(atoi(argv[1]), atoi(argv[2]) * 1000000.);

	//fprintf(stdout, "%s\n", "3.141592653589793238462643383279502884197169399375");
	//fprintf(stdout, "%1.48f\n", pi);
	return 0;
}

double get_pi(int num_threads, int k_max){
	double i;
	double pi;
	pi = 0.;
	for(i = 0; i <= k_max; i++){
		pi += 4 * (pow(-1, i)/((2 * i) + 1));
	}

	return pi;
}
