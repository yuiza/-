#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1.0e-10

#define N 3
#define NMAX 5

void cg(int n, double **adim, double *bvec, double *xvec){
	int i, j, k, count = 0;
   	double eps, tmp, alpha, beta, r = 0;

	double *axvec;
	double *pvec;
	double *rvec;
	double *apvec;

	apvec = (double *)malloc(sizeof(double)*n);
	axvec = (double *)malloc(sizeof(double)*n);
	pvec  = (double *)malloc(sizeof(double)*n);
	rvec  = (double *)malloc(sizeof(double)*n);

	for(i=0; i<n; i++){
		axvec[i] 	= 0;
		pvec[i] 	= 0;
		rvec[i] 	= 0;
		apvec[i] 	= 0;
	}

	//get axvec, r, p
	for(i=0; i<n; i++){
		tmp=0;
		for(j=0; j<n; j++){
			tmp += adim[i][j] * xvec[j];
		}
		axvec[i] = tmp;
		rvec[i] = bvec[i] - tmp;
		pvec[i] = rvec[i];
	}

	while(1){
		eps = 0.0;

		//α(k) = ( r(k), p(k) ) / ( p(k), p(k) )
		for(i=0; i<n; i++){
			tmp = 0;
			for(j=0; j<n; j++){
				tmp += adim[i][j] * pvec[j];
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
		printf("%e   ", eps);
		if(eps <= EPS){
			count++;
			break;
		}

		//β(k) = ( r(k+1), r(k+1) ) / ( r(k), r(k) )
		for(i=0, tmp=0; i<n; i++){	
			tmp += rvec[i] * apvec[i];
		}
		beta = -1 * tmp / r;

		for(i=0; i<n; i++){
			pvec[i] = rvec[i] + beta * pvec[i];
		}
		count++;
	}

	printf("%d\n", count);

	free(axvec);free(pvec);free(rvec);free(apvec);
}

int main(int ac, char *av[]){

   int i,j,k;
   int n = N;
   double **admin;
   double *bvec;
   double *xvec;

   if(ac > 1){
      n = atoi(av[1]);
      printf("n=%d\n", n);
   }

   admin = (double **)malloc(sizeof(double*)*n);
   for(i=0; i<n; i++){
      admin[i] = (double *)malloc(sizeof(double)*n);
   }
   bvec  = (double *)malloc(sizeof(double)*n);
   xvec  = (double *)malloc(sizeof(double)*n);

   for(i=0; i<n; i++){
      for(j=0; j<n; j++){
         if(j == i)  admin[i][j] = 5;
         else     admin[i][j] = 1;
      }
      bvec[i] = 7;
      xvec[i] = 0;
   }

   cg(n, admin, bvec, xvec);

   puts("");
   for(k=0; k<n; k++){
      printf("xvec[%2d] = %e = %lf\n", k,　xvec[k], xvec[k]);
   }

   free(admin);free(bvec);free(xvec);

   return 0;
}