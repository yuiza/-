#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NMAX 1000

#define EPS 1.0e-10

#define N 3

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
          admin[0][2] = 1;
        }else if(i == n-1){
          admin[i][i] = 5;
          admin[i][i-1] = 1;
          admin[i][i-2] = 1;
        }else if(i == j){
          admin[i][j] = 5;
          admin[i][j-1] = 1;
          admin[i][j+1] = 1;
        }
    }
    for(j=0; j<n; j++){
      if(admin[i][j] != 1 && admin[i][j] != 5)
              admin[i][j] = 0;
    }
    
    bvec[i] = 7;
    xvec[i] = 0;
  }

    for(k=0; k<n; k++){
      for(i=0; i<n; i++){
        printf("%d ,", (int)admin[k][i]);
      }
      puts("");
    }
    // printf("xvec[%2d] = %e = %lf\n", n-1,xvec[n-1], xvec[n-1]);

    free(admin);free(bvec);free(xvec);

    return 0;
}