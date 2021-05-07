#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <ascii_gradient.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define TWO_PI 6.283185307179586

#define MAX_ITER 80
#define X_MIN -1.5
#define X_MAX 1.5
#define Y_MIN -1.5
#define Y_MAX 1.5
#define X_DEF 120
#define Y_DEF 40
#define SLEEP_TIME 0.05

typedef struct {
	double real;
	double imag;
} complex;

complex makeComplex (double real, double imag) {
	complex result;
	result.real = real;
	result.imag = imag;
	return result;
}

complex multiplyComplex (complex a, complex b) {
	complex result;
	//(a + ib) * (c + id) = ac + iad + ibc - bd
	result.real = a.real * b.real - a.imag * b.imag;
	result.imag = a.real * b.imag + a.imag * b.real;
	return result;
}
// next = Z^2-C
int iterCountJulia(complex init, complex c, int max) {
	int count = 0;
	complex iterSpot;
	complex tempSpot;

	iterSpot.real = init.real;
	iterSpot.imag = init.imag;
	while( 	iterSpot.real > -2.0 &&
			iterSpot.real < 2.0 &&
			iterSpot.imag > -2.0 &&
			iterSpot.imag < 2.0 &&
			count < max
	) {
		tempSpot = multiplyComplex(iterSpot, iterSpot);
		iterSpot.real = tempSpot.real - c.real;
		iterSpot.imag = tempSpot.imag - c.imag;
		count += 1;
	}
	return count;
}

void usage() {
	printf("\n\nUsage:\t\tjulia <real> <imag>\n\n");
}

int main(int argc, char ** argv) {
	complex spot;
	complex c_spot;
	double x_step = (X_MAX - X_MIN) / (X_DEF - 1.);
	double y_step = (Y_MAX - Y_MIN) / (Y_DEF - 1.);
	double x, y;
	int tone;
	int frameCount = 0;
	float angle = 0.;
	float moment = 0.02;
	float r = 0.05;
	clock_t last = 0.;
	clock_t now = 0.;

	const float I_MAX_ITER = 1. / MAX_ITER;

	if (argc < 3) {
		usage();
		return 1;
	}
	float c_real = atof(argv[1]);
	float c_imag = atof(argv[2]);
	

	while(1) {
		now = clock();
		c_spot = makeComplex(c_real + sin(angle) * r, c_imag + cos(angle) * r);
		//printf("\e[1;1H\e[2J");
		system("sleep SLEEP_TIME");
		system("clear");
		printf("frameCount:%10i\tframeRate:%10f\tlast:%10f\tnow:%10f\n", ++frameCount, 1000. / (now - last), last, now);
		printf("real:%5f\timag:%5f\n", c_real, c_imag);
		printf("angle:%3f\tmoment:%3f\tr:%3f", angle, moment, r);  
		for (y = Y_MIN; y <= Y_MAX; y += y_step) {
			for (x = X_MIN; x <= X_MAX; x += x_step) {	
				spot = makeComplex(x, y);
				tone = (int)(iterCountJulia(spot, c_spot, MAX_ITER) * I_MAX_ITER * 9.) ;
				//printf("%i", tone);
				printf("%c", asciiGradient10[tone]);					
				//if (y == Y_MIN || y == Y_MAX ||  x == X_MIN || x == X_MAX) printf("%s", "X");
			}
			printf("\n");
		}
		angle = angle + moment > TWO_PI ? angle + moment - TWO_PI : angle + moment;
		last = clock();
	}
	return 1;
}


