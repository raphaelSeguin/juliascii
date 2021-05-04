#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <ascii_gradient.h>

#define M_PI 3.14159265358979323846

#define MAX_ITER 40
#define X_MIN -1.5
#define X_MAX 1.5
#define Y_MIN -1.5
#define Y_MAX 1.5
#define X_DEF 220
#define Y_DEF 60

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
	while( 	iterSpot.real > -1.0 &&
			iterSpot.real < 1.0 &&
			iterSpot.imag > -1.0 &&
			iterSpot.imag < 1.0 &&
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
	float angle = 0.;
	float moment = 0.02;
	float r = 0.05;
		
	if (argc < 3) {
		usage();
		return 1;
	}
	float c_real = atof(argv[1]);
	float c_imag = atof(argv[2]);
		
	while(1) {
		//system("clear");	
		
		c_spot = makeComplex(c_real + sin(angle) * r, c_imag + cos(angle) * r);
		
		printf("\e[1;1H\e[2J");
		
		for (y = Y_MIN; y < Y_MAX; y += y_step) {
			for (x = X_MIN; x <= X_MAX; x += x_step) {	
				spot = makeComplex(x, y);
				tone = (int)(MAX_ITER - iterCountJulia(spot, c_spot, MAX_ITER)) * 10 / MAX_ITER ;
				printf("%c", asciiGradient10[tone]);					
			}
			printf("\n");
		}
		angle = angle + moment > M_PI ? angle + moment - M_PI : angle + moment;
	}
	return 1;
}


