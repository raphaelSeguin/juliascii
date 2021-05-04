#include <stdio.h>
#include <stdlib.h>
#include <ascii_gradient.h>

#define MAX_ITER 20
#define X_MIN -0.5
#define X_MAX 1.5
#define Y_MIN -1.0
#define Y_MAX 1.0
#define X_DEF 220
#define Y_DEF 50

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
int iterCount(complex init, int max) {
	int count = 0;
	complex iterSpot;
	complex tempSpot;

	iterSpot.real = init.real;
	iterSpot.imag = init.imag;
	while( 	iterSpot.real > -1.0 &&
			iterSpot.real < 1.0 &&
			iterSpot.imag > -1.0 &&
			iterSpot.imag < 1.0 &&
			count < max
	) {
		tempSpot = multiplyComplex(iterSpot, iterSpot);
		iterSpot.real = tempSpot.real - init.real;
		iterSpot.imag = tempSpot.imag - init.imag;
		count += 1;
	}
	return count;
}

int main(int argc, char ** argv) {
	complex spot;
	double x_step = (X_MAX - X_MIN) / (X_DEF - 1.);
	double y_step = (Y_MAX - Y_MIN) / (Y_DEF - 1.);
	double x, y;
	int tone;
	
	system("clear");

	for (y = Y_MIN; y < Y_MAX; y += y_step) {
		for (x = X_MIN; x <= X_MAX; x += x_step) {	
			spot = makeComplex(x, y);
			tone = (int)(MAX_ITER - iterCount(spot, MAX_ITER)) * 10 / MAX_ITER ;
			printf("%c", asciiGradient10[tone]);					
		}
		printf("\n");
	}
	return 1;
}


