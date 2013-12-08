// Copyright (c) 2013 Rafał Selewońko <rafal@selewonko.com>.
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int main(int argc, char *argv[]) {
	double k_max;
	double pi;
	double i;
	double timea, timeb;
	int num_threads;

	pi = 0.;
	k_max = (double)atoi(argv[2]) * 1000000.;

	num_threads = atoi(argv[1]);
	omp_set_num_threads(num_threads);

	timea = clock();
	#pragma omp parallel
	{
		int ID = omp_get_thread_num();

		for(i = 0.0; i <= k_max; i++)
		{
			pi += 4 * (pow(-1, i)/((2 * i) + 1));
		}
	}
	timeb = clock();

	//fprintf(stdout, "%s\n", "3.141592653589793238462643383279502884197169399375");
	fprintf(stdout, "%f, %d, %1.48f\n", (double)(timeb - timea) / CLOCKS_PER_SEC, num_threads, pi);
	return 0;
}
