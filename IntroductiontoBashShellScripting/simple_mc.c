#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000000

double f(double x) {
	return (1.0 - x) / sqrt(x);
}

int main(int argc, char *argv[]) {
	long seed;
	int i;
	double sigma_f, f_ave, f2_ave, f_u;

	const double ANSWER = 4.0/3.0;

	if (argc == 2)
		seed = atol(argv[1]);
	else
		seed = 12345;

	srand48(seed);

	f_ave = 0.0;
	f2_ave = 0.0;

	for (i=0; i<N; i++) {
		f_u = f(drand48());
		f_ave  += f_u;
		f2_ave += f_u * f_u; // square average
	}

	f_ave /= (double) N; // sample mean
	sigma_f = sqrt((f2_ave/(double)N - f_ave*f_ave) / (double)N);

	printf("N=%d I= %f +/- %f (in range of answer %f ? %c)\n", N, f_ave, sigma_f, ANSWER, (fabs(f_ave - ANSWER) < sigma_f) ? 'y' : 'n');

	return 0;
}

