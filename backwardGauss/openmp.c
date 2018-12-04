//=============================================================================================
// Name        		: main.c
// Author      		: Saumya Bhatnagar
// Version     		:	22-03-2018
// Creation date	:	19-03-2018
// Description		: This program is for solving dense system of linear quations. It is the openmp imlementation of the Gaussian elimination with backward substitution 
//=============================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "openmp.h"
#include "serial.h"


float **copy_matrix(float **A, int n){
    int i, j, m;
    float *tmp, **AP;
    m=n+1;
//    printf("Copying the augmented matrix for parallel processing\n");
    AP = calloc(n, sizeof(float *));
    tmp = calloc(n*m, sizeof(float));
    for(i = 0; i< n; i++){
	AP[i] = &tmp[m*i];
    }
    for(i=0; i<n; i++){
        for(j=0; j<m; j++){
            AP[i][j]=A[i][j];
        }
    }
//    printf("Matrix for testing of the openmp method is\n");
//    print_matrix(AP, n);
return AP;
}

void gaussElimParallel(float **g, int n){
//    printf("Generation of upper triangular matrix\n");
    int i, j, k;
    float ratio;
    for(j=0; j<n; j++){
//       #pragma omp private(ratio)schedule(runtime)shared(i,j,k)
       for(i=0; i<n; i++){
           if(i>j){
                ratio=g[i][j]/g[j][j];
		//pivot row found, the further modification is done simultaneously
 #pragma omp parallel for
		for(k=0; k<n+1; k++){
                    g[i][k]=g[i][k]-ratio*g[j][k];
                  }
            }
        }
    }
//    printf("Printing Upper triangular matrix\n");
//    print_matrix(g, n);
}

float *backSubsParallel(float **g, int n){//, int s, int e){
    int i, j;
    float sum=0.0, *x;
    x=calloc(n, sizeof(float));
    x[n-1]=g[n-1][n]/g[n-1][n-1];//computed one at a time
//    printf("Starting Backward substitution");
    for(i=n-2; i>=0; i--){
      sum=0;
 //     #pragma omp parallel for
      for(j=i; j<n; j++){
         sum=sum+g[i][j]*x[j];
      }
      x[i]=(g[i][n]-sum)/g[i][i];
    }
return x;
}


