#include <stdio.h>

#define N 3


int main(){

	double a[N][N] = { {2, 1, -1}, {3, 2, 4}, {5, -3, 1} };

	int n = N;

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			printf("%g\t", a[i][j]);
		}
		puts("");
	}

///////////////////////////////////
//	LU

	for(int k=0; k<n-1; k++){
		double w = 1.0 / a[k][k];

		for(int j=k+1; j<n; j++){
			a[j][k] = w * a[j][k];
			
			for(int i=k+1; i<n; i++){
				a[i][j] = a[i][j] - a[j][k] * a[k][j];
			}
		}
	}
//
//////////////////////////////////


	printf("************\n");

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			printf("%g\t", a[i][j]);
		}
		puts("");
	}

	return 0;
}