#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./header/init.h"

#define EPS 1.0e-10

#define N 3
#define NMAX 5

void cg(int n, double **adim, double *bvec, double *xvec){
	int i, j, k, count = 1;
   	double eps, alpha, beta, r, p, pp, rr;

	double *pvec;
	double *rvec;
	double *apvec;

	apvec = (double *)malloc(sizeof(double)*n);
	pvec  = (double *)malloc(sizeof(double)*n);
	rvec  = (double *)malloc(sizeof(double)*n);

	for(i=0; i<n; i++){
		rvec[i] = bvec[i];
		pvec[i] = rvec[i];
	}

	while(1){
		eps = 0.0;

		for(i=0; i<n; i++){
			apvec[i] = 0;
			for(j=0; j<n; j++){
				apvec[i] += adim[i][j] * pvec[j];
			}
		}

		for(i=0, r=0, p=0; i<n; i++){
			r += rvec[i] * rvec[i];
			p += pvec[i] * apvec[i];
		}
		alpha = r / p;

		for(i=0; i<n; i++){
			xvec[i] += alpha * pvec[i];
			rvec[i] -= alpha * apvec[i];
		}

		for(i=0; i<n; i++){
			eps += fabs(rvec[i]);
		}
      	
      	printf("%d %e   \n", count, eps);
		
		if(eps <= EPS){
			count++;
			break;
		}else if(isinf(eps)){
        	break;
      	}else if (isnan(eps)){
      		break;
      	}

		for(i=0, rr=0, pp=0; i<n; i++){	
			rr += rvec[i] * rvec[i];
			pp += pvec[i] * pvec[i];
		}
		beta = rr/pp;

		for(i=0; i<n; i++){
			pvec[i] = rvec[i] + beta * pvec[i];
		}
		count++;
	}

	free(pvec);free(rvec);free(apvec);
}

int main(int ac, char *av[]){

   int i,j,k;
   int n = N;
   double **admin;
   double *bvec;
   double *xvec;

   if(ac > 1){
      n = atoi(av[1]);
   }

   admin = (double **)malloc(sizeof(double*)*n);
   for(i=0; i<n; i++){
      admin[i] = (double *)malloc(sizeof(double)*n);
   }
   bvec  = (double *)malloc(sizeof(double)*n);
   xvec  = (double *)malloc(sizeof(double)*n);


   //init A[][], b[], x[]
   init(n, admin, bvec, xvec);

   cg(n, admin, bvec, xvec);


   // for(k=0; k<n; k++){
   //    printf("xvec[%2d] = %e = %lf\n", k, xvec[k], xvec[k]);
   // }
   // printf("xvec[%2d] = %e = %lf\n", n-1,xvec[n-1], xvec[n-1]);


   free(admin);free(bvec);free(xvec);

   return 0;
}