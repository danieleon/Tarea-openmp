#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

static long num_steps = 10000000;

double step;

void main() {
	long i, chunk=num_steps/10;
	struct timeval tv1,tv2;
	double x, pi;
	double sum = 0.0;
	gettimeofday(&tv1,NULL);
	step = 1.0/(double) num_steps;

	#pragma omp parallel for default(shared) private(i) \
	 schedule(static,chunk) reduction(+:sum)
	for (i = 0; i < num_steps; i++) {
		x = (i + 0.5)*step;
		sum = sum + 4.0/(1.0 + x*x);
	}
	pi = step * sum;
	gettimeofday(&tv2,NULL);
	printf("pi [%lf] step [%e] sum[%lf] - time %lf\n", pi, step,sum,(double)(tv2.tv_usec - tv1.tv_usec)/1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
}
