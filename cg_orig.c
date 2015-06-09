#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1.0e-10

#define N 3
#define NMAX 5

int main(void){
	int n = N;
	int k, i, j;
	double A[n][n] = {{5, 1, 1}, {1, 5, 1}, {1, 1, 5}};

	double b[n] = {7, 7, 7};

	double eps;

	double xvec[n];
	double axvec[n];//apk
	double pvec[n];
	double rvec[n];

	double beta = 0;
	double alpha = 0;

	double r =0;
	double tmp = 0;
	double apvec[n];

	for(i=0; i<n; i++){
		xvec[i] = 0;
		axvec[i] = 0;
		pvec[i] = 0;
		rvec[i] = 0;
		apvec[i]=0;
	}
	int limit = 0;

	//get axvec, r, p
	for(i=0; i<n; i++){
		tmp=0;
		for(j=0; j<n; j++){
			tmp += A[i][j] * xvec[j];
		}
		axvec[i] = tmp;
		rvec[i] = b[i] - tmp;
		pvec[i] = rvec[i];
	}


	for(limit = 0; limit < NMAX; limit++){
		eps = 0.0;

		//α(k) = ( r(k), p(k) ) / ( p(k), p(k) )

		for(i=0; i<n; i++){
			tmp=0;
			for(j=0; j<n; j++){
				tmp += A[i][j] * pvec[j];
			}
			apvec[i] = tmp;
		}

		for(i=0,tmp=0; i<n; i++){
			r += rvec[i] * pvec[i];
			tmp += pvec[i] * apvec[i];
		}
		alpha = r / tmp;

		//x(k+1) = x(k) + α * p(k)
		//r(k+1) = r(k) + r * p(k)
		for(i=0; i<n; i++){
			xvec[i] += alpha * pvec[i];
			rvec[i] -= alpha * apvec[i];
		}
		
		for(i=0; i<n; i++){
			eps += fabs(rvec[i]);
		}
		// printf("eps: %e	", eps);
		if(eps <= EPS)
			break;

		//β(k) = ( r(k+1), r(k+1) ) / ( r(k), r(k) )
		for(i=0, tmp=0; i<n; i++){	
			tmp += rvec[i] * apvec[i];
		}
		beta = -1 * tmp / r;

		for(i=0; i<n; i++){
			pvec[i] = rvec[i] + beta * pvec[i];
		}
	}

	puts("");
    for(k=0; k<n; k++){
      printf("xvec[%2d] = %e = %lf\n", k,xvec[k], xvec[k]);
    }

    return 0;

}