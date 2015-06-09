#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./header/init.h"

#define NMAX 1000
#define EPS 1.0e-10
#define N 3

void jacob(int n, double **adim, double *bvec, double *xvec){

	int i, j, k, count = 1;
	double eps;
  double *tmp;
	tmp  = (double *)malloc(sizeof(double)*n);
	for(i=0; i<n; i++){
		tmp[i] = 0;
	}

   //jacob
	while(1){

    	for(k=0; k<n; k++){
        	xvec[k] = bvec[k];
        	for(i=0; i<n; i++){
        		if(i != k)
           		 	xvec[k] -= adim[k][i] * tmp[i];
        	}   
        	xvec[k] =  xvec[k] / adim[k][k];   
    	}

    	//εチェック
    	eps = 0.0;
    	for(i=0;i<n;i++){
       		eps += fabs(tmp[i] - xvec[i]);
        	tmp[i] = xvec[i];
    	}

      printf("%d %e   \n", count, eps);

	    if(eps < EPS){
	    	count++;
	    	//printf("\nEND 	%e	", eps);
    		break;
	    }else if(isinf(eps)){
	    	//printf("\nERROR : eps infinity\n");
	    	break;
	    }
	    count++;
	}
	//jacob end
	//printf("%d\n", count);
	free(tmp);
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

  jacob(n, admin, bvec, xvec);

   	// for(k=0; k<n; k++){
    // 	printf("xvec[%2d] = %e = %lf\n", k,xvec[k], xvec[k]);
   	// }
    //printf("xvec[%2d] = %e = %lf\n", n-1,xvec[n-1], xvec[n-1]);

   	free(admin);free(bvec);free(xvec);

   	return 0;
}
