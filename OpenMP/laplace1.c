/**********************************************************************
 * Program na reseni Laplaceovy rovnice 
 *
 *  u_xx + u_yy = f(x,y)
 *  
 * s okrajovou podminkou u(x,y) = 0 
 * na oblasti ve tvaru jednotkoveho ctverce.
 *
 * Pro reseni vyuzivam metody siti a vysledne rovnice resim
 * Gauss-Seidelvou iteracni metodou. 
 *
 **********************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Prava strana Laplaceovy rovnice
// tato prava strana odpovida reseni u = ((x-1/2)**2-1/4)*((y-1/2)**2-1/4)
// a tedy u(0.5,0.5) = -1/16 = - 0.625
double f(double x, double y) {
    return 2*(y*y-y+x*x-x);
}


int main() {

    double *u;
    double *b;
    double x, y, h, uc;

    int i, j, n, iter, niter;

    n = 101;

    u = (double*) malloc(n*n*sizeof(double));
    b = (double*) malloc(n*n*sizeof(double));

    // Pocatecni hodnota reseni
#pragma omp parallel for
    for (int j=0; j<n; j++)
	for (int i=0; i<n; i++)
	    u[i+j*n] = 0;

    // Vypocet prave strany
    h = 1.0 / (n-1);
#pragma omp parallel for private(x,y)
    for (int j=0; j<n; j++) 
	for (int i=0; i<n; i++) {
	    x = i*h;
	    y = j*h;
	    b[i+j*n] = h*h*f(x,y);
	};
    
	    // 
    niter = 10000;
#pragma omp parallel 
    for (iter=1; iter<=niter; iter++) {
#pragma omp for private(i,j)   
	for (j=1; j<n-1; j++)
	    for (i=1; i<n-1; i++) {
	      if ((i+j) % 2 == 0)
		u[i+j*n] = (u[i-1 + j*n] + u[i + (j-1)*n] + 
			    u[i+1 + j*n] + u[i + (j+1)*n] - b[i+j*n])/4.0;
	    }

#pragma omp  for private(i,j)   
	for (j=1; j<n-1; j++)
	    for (i=1; i<n-1; i++) {
	      if ((i+j) % 2 == 1)
		u[i+j*n] = (u[i-1 + j*n] + u[i + (j-1)*n] + 
			    u[i+1 + j*n] + u[i + (j+1)*n] - b[i+j*n])/4.0;
	    }

	if (iter % 1000==0)
	    printf("%i u(0.5,0.5)= %lf\n", iter, u[(n-1)/2 + ((n-1)/2)*n]);
    }


}









