#include <stdio.h>
#include <stdlib.h>
#include "serial.h"
//<unistd.h>

void print_matrix(float **g, int n){
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<(n+1); j++){
            printf("%f   ",g[i][j]);
        }
    printf("\n");
    }
}

void print_array(float *g, int n){
    int i;
    for(i=0; i<n; i++){
        printf("x%d=%f\n",i+1, g[i]);
    }
}

float **random_matrix( int n){
    int i, j, m;
    float *tmp, **A;
    m=n+1;
//    printf("Allocating random matrix\n");
    A = calloc(n, sizeof(float *));
    tmp = calloc(n*m, sizeof(float));
    for(i = 0; i< n; i++){
	A[i] = &tmp[m*i];
    }
    
    for(i=0; i<n; i++){
        for(j=0; j<m; j++){
            A[i][j]=rand()%100;
        }
    }
//    if(n<7){
//      printf("Matrix for testing of the method is\n");
//      print_matrix(A, n);
//    }
return A;
}

void gaussElimSerial(float **g, int n){
//    printf("Generation of upper triangular matrix\n");
    int i, j, k;
    float c;
    for(j=0; j<n; j++){
        for(i=0; i<n; i++){
            if(i>j){
                c=g[i][j]/g[j][j];
                for(k=0; k<n+1; k++){
                    g[i][k]=g[i][k]-c*g[j][k];
                }
            }
        }
    }
//    printf("Printing Upper triangular matrix\n");
//    print_matrix(g, n);
}

float *backSubsSerial(float **g, int n){
    int i, j;
    float sum=0.0, *x;
    x=calloc(n, sizeof(float));
    x[n-1]=g[n-1][n]/g[n-1][n-1];
//    printf("Starting Backward substitution\n");
    for(i=n-2; i>=0; i--){
        sum=0;
        for(j=i; j<n; j++){
            sum=sum+g[i][j]*x[j];
        }
        x[i]=(g[i][n]-sum)/g[i][i];
    }
return x;
}
