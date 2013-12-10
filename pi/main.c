// Copyright (c) 2013 Rafał Selewońko <rafal@selewonko.com>.
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>

double get_pi(int num_threads, int k_max);


int main(int argc, char *argv[]) {
	double pi;
	pi = get_pi(atoi(argv[1]), atoi(argv[2]) * 1000000.);

	return 0;
}

double get_pi(int num_threads, int k_max){
	double pi;
	double sum[num_threads];
	int i;
	int nthreads;

	omp_set_num_threads(num_threads);

	#pragma omp parallel
	{
		double i;
		int id = omp_get_thread_num();
		int nthrds = omp_get_num_threads();
		if (id == 0) {
			nthreads = nthrds;
		}
		sum[id] = 0.0;

		for(i = id; i <= k_max; i+=nthrds)
		{
			sum[id] += 4 * (pow(-1, i)/((2 * i) + 1));
		}
	}

	pi = 0.0;
	for(i = 0; i < nthreads; i++){
		pi += sum[i];
	}
	return pi;
}
