#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int *seive(int limit){
  int i, j;
  int *primes;
  primes = calloc(limit, sizeof(int));
  for(i = 2; i< limit; i++){
    primes[i]=1;
  }
  for(i = 2; i< limit; i++){
    if(primes[i]){
      for(j=i; i*j< limit; j++){
	primes[i* j] = 0;
      }
    }
  }
return primes;
}

void print_primes(int *primes, int limit){
  int i,j;
  printf("Prime numbers within the given range are \n");
  for(i = 2; i< limit; i++){
    if(primes[i]){
      printf("%d   ", i);
    }
  }
}

int *seivePar(int limit){
  int i, j;
  int *primesPar;
  primesPar = calloc(limit, sizeof(int));

  #pragma omp for
    for(i = 2; i< limit; i++){
      primesPar[i]=1;
    }
    #pragma omp for
     for(i = 2; i< limit; i++){
      if(primesPar[i]){
        for(j=i; i*j< limit; j++){
	  primesPar[i*j] = 0;
        }
      }
     }
return primesPar;
}


