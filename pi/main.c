// Copyright (c) 2013 Rafał Selewońko <rafal@selewonko.com>.
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>


int main(int argc, char *argv[]) {
	double k_max;
	double pi;
	double sum[2];
	double timea, timeb;
	int i;
	int num_threads;
	int nthreads;

	pi = 0.;
	k_max = (double)atoi(argv[2]) * 1000000.;

	num_threads = atoi(argv[1]);
	omp_set_num_threads(num_threads);

	timea = clock();
	#pragma omp parallel
	{
		double i;
		int id = omp_get_thread_num();
		int nthrds = omp_get_num_threads();
		if (id == 0) {
			nthreads = nthrds;
		}

		for(i = id; i <= k_max; i+=nthrds)
		{
			sum[id] += 4 * (pow(-1, i)/((2 * i) + 1));
		}
	}
	pi = 0.0;
	for(i = 0; i < nthreads; i++){
		pi += sum[i]
	}
	timeb = clock();

	//fprintf(stdout, "%s\n", "3.141592653589793238462643383279502884197169399375");
	fprintf(stdout, "%f, %d, %1.48f\n", (double)(timeb - timea) / CLOCKS_PER_SEC, num_threads, pi);
	return 0;
}
