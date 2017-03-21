#include <armadillo>
using namespace arma;

/*
	Matrix Solver uses the Armadillo library.
	See armadillo folder for license.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// returns inv(M'*M)*(M'*Y)
double* getWeights(int** M, int* Y, int n, int m) {
	srand(time(NULL));

	mat matM(n, m);
	mat matY(n, 1);

	for (int i = 0; i < n; ++i) {
		matY(i, 0) = Y[i];
		for (int j = 0; j < m; ++j) {
			int t = M[i][j];
			t = rand() % 10000;
			matM(i, j) = t;
		}
	}

	mat W = (arma::inv(arma::trans(matM)*matM)) * (arma::trans(matM)*matY);

	double *weights = new double[m];
	
	for (int i = 0; i < m; ++i) {
		//weights[i] = rand()%5;
		weights[i] = W[i];
	}

	return weights;
}
