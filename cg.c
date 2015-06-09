#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1.0e-10

#define N 3
#define NMAX 5

void cg(int n, double **adim, double *bvec, double *xvec){
	int i, j, k, count = 1;
   	double eps, tmp, alpha, beta, r = 0, p = 0;

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
	}
	for(i=0; i<n; i++){
		pvec[i] = bvec[i] - axvec[i];
		rvec[i] = pvec[i];
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

		tmp = 0;
		for(i=0; i<n; i++){
			r += rvec[i] * pvec[i];
			p += pvec[i] * apvec[i];
		}
		alpha = r / p;

		//x(k+1) = x(k) + α * p(k)
		//r(k+1) = r(k) + r * p(k)
		for(i=0; i<n; i++){
			xvec[i] += alpha * pvec[i];
			rvec[i] += -1 * alpha * apvec[i];
		}

		for(i=0; i<n; i++){
			eps += fabs(rvec[i]);
			// printf("%e   ", fabs(rvec[i]));
		}
      printf("%d %e   \n", count, eps);
		if(eps < EPS){
			count++;
			printf("\nEND 	%e	", eps);
			break;
		}else if(isinf(eps)){
         // printf("\nERROR : eps infinity\n");
         break;
      	}else if (isnan(eps)){
      		break;
      	}
		//β(k) = ( r(k+1), r(k+1) ) / ( r(k), r(k) )
		tmp = 0;
		for(i=0; i<n; i++){	
			tmp += rvec[i] * apvec[i];
		}
		beta = -1 * tmp / p;

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
      //printf("n=%d\n", n);
   }

   admin = (double **)malloc(sizeof(double*)*n);
   for(i=0; i<n; i++){
      admin[i] = (double *)malloc(sizeof(double)*n);
   }
   bvec  = (double *)malloc(sizeof(double)*n);
   xvec  = (double *)malloc(sizeof(double)*n);

   for(i=0; i<n; i++){
      for(j=0; j<n; j++){
        if(i==0){
          admin[0][0] = 5;
          admin[0][1] = 1;
          // admin[0][2] = 1;
        }else if(i == n-1){
          admin[i][i] = 5;
          admin[i][i-1] = 1;
          // admin[i][i-2] = 1;
        }else if(i == j){
          admin[i][j] = 5;
          admin[i][j-1] = 1;
          admin[i][j+1] = 1;
        }else{
          if(admin[i][j] != 1 && admin[i][j] != 5)
              admin[i][j] = 0;
        }
      }
      if(i == 0 || i == n-1) bvec[i] = 6;
      else 					 bvec[i] = 7;
      	xvec[i] = 0;
  }

   cg(n, admin, bvec, xvec);


   for(k=0; k<n; k++){
      printf("xvec[%2d] = %e = %lf\n", k, xvec[k], xvec[k]);
   }
   printf("xvec[%2d] = %e = %lf\n", n-1,xvec[n-1], xvec[n-1]);

   free(admin);free(bvec);free(xvec);

   return 0;
}