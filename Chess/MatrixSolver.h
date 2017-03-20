#include <armadillo>
#define ARMA_DONT_PRINT_ERRORS
using namespace arma;

/*
	Matrix Solver uses the Armadillo library.
	See armadillo folder for license.
*/


// returns inv(M'*M)*(M'*Y)
double* getWeights(int** M, int* Y, int n, int m) {

	mat matM(n, m);
	mat matY(n, 1);

	for (int i = 0; i < n; ++i) {
		matY(i, 0) = Y[i];
		for (int j = 0; j < m; ++j) {
			int t = M[i][j];
			matM(i, j) = t;
		}
	}

	// calculate weights
	mat W = (arma::inv(arma::trans(matM)*matM)) * (arma::trans(matM)*matY);


	double *weights = new double[m];
	
	for (int i = 0; i < m; ++i) {
		//weights[i] = W(i, 0);
	}

	return weights;
}
