//gauss.c
//

#include <stdio.h>
#include <stdlib.h>

#include "./header/init.h"
#include "./header/timer.h"

#define NMAX 100
#define N 3

void gauss(int n, double **adim, double *bvec, double *xvec){


	double alpha = 0, sum = 0;
	int i, k, j;

   double ts = dgettime();

	for(k=0; k<n; ++k){
		//特異性の判定 [k][k]が0では計算できないため
		// if(adim[k][k] == 0.0){
		// 	printf("adim[%2d][%2d] = 0.0 ?\n", k, k);
		// 	//exit(1);
		// 	break;
		// }

    
		//前進消去過程
		for(i=k+1; i<n; ++i){
			alpha =- adim[i][k] / adim[k][k];
			for(j=k+1; j<n; j++){
				adim[i][j] += alpha * adim[k][j];
			}
			bvec[i] += alpha*bvec[k];
		}
	}

	//後退代入過程
	for(k=n-1; k>=0; k--){
		for(j=k+1, sum = bvec[k]; j<n; ++j){
			sum -= adim[k][j] * xvec[j];
		}
		xvec[k] = sum/adim[k][k];
	}
   
   double te = dgettime();

   printf("%d %f\n", n, te-ts);

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

  //init A[][], b[], x[]
   init(n, admin, bvec, xvec);

   gauss(n, admin, bvec, xvec);

   // for(k=0; k<n; k++){
   //    printf("xvec[%2d] = %e = %lf\n", k,xvec[k], xvec[k]);
   // }
   //printf("xvec[%2d] = %e = %lf\n", n-1,xvec[n-1], xvec[n-1]);


   free(admin);free(bvec);free(xvec);

   return 0;
}