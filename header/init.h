#include <stdio.h>
#include <stdlib.h>

void init(int n, double **admin, double *bvec, double *xvec){
	int i,j;
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
}