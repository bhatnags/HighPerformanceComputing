//=============================================================================================
// Name        		: main.c
// Author      		: Saumya Bhatnagar
// Version     		:	24-03-2018
// Creation date	:	20-03-2018
// Description		: This program is for getting primes using seive of Eratothenes. The program compares thr serial implementation with the parallel openmp version 
//=============================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include "functions.h"
 
int main(int argc, char *argv[]){

    //Clearing the terminal
    system("clear");

    //Limit of Number to which primes are to be calculated
    int size=1000; //Default set to 1000

    //Flag to print the prime numbers
    int printResults = 0;

    //Get the number of threads
    int MAXTHREADS = 4;
    if(argc < 3){
	printf("Please provide the number upto which primes are to be calculated in command line\n./backGauss -n 100\n");
        exit(1);
    }
    int option; //for getopt
    while((option = getopt(argc, argv, "ntp"))!= -1){
	switch(option){
	  case 'n':
	    size = atoi(argv[optind]);
	    break;
	  case 't':
	    MAXTHREADS = atoi(argv[optind]);
	    break;
	  case 'p':
	    printResults = 1;
	    break;
        }
    }


    //Printing configurations
    printf("\n");
    if(printResults==1){
      printf("\nThe calculation size(limit of numbers) is:");
    }
    printf("%d  ", size);
    
    if(printResults==1){
      printf("\nThe number of threads are:");
    }
    printf("%d  ", MAXTHREADS);


    //Variable declaration
    int tid=0, chunk, start, end;
    //Time variable declaration
    struct timeval startTimeSerial, endTimeSerial, startTimePar, endTimePar;
    double diffTimePar, diffTimeSer;
    //Variable declarations for storiing prime numbers
    int *primes, *primesPar;
    

    //Serial process starts
    gettimeofday(&startTimeSerial, NULL);
     primes = seive(size);
    gettimeofday(&endTimeSerial, NULL);
    //printf("Results noted");
    //Serial process ends
    //Get the time taken in using serial method
    diffTimeSer = ((double)(endTimeSerial.tv_usec - startTimeSerial.tv_usec)+ (double)(endTimeSerial.tv_sec - startTimeSerial.tv_sec)*1000000 );


    //Parallel process starts
    //startTimePar = omp_get_wtime();
    gettimeofday(&startTimePar, NULL);
     // chunk = size/MAXTHREADS;
      omp_set_num_threads(MAXTHREADS);
    
     // #pragma omp parallel shared(primes, chunk)private(tid,start,end)
     // tid = omp_get_thread_num();
     // start = tid*chunk;
     // end= start + chunk;
      //printf("Thread %d created with start and end : %d to %d\n", tid, start, end);
       primesPar = seivePar(size);
    //endTimePar = omp_get_wtime();
    gettimeofday(&endTimePar, NULL);
    //printf("Results noted");
    //Parallel process ends
    //Get the time taken using Openmp
    diffTimePar = ((double)(endTimePar.tv_usec - startTimePar.tv_usec) + (double)(endTimePar.tv_sec - startTimePar.tv_sec)*1000000);

    //Print the solution
    //Using Serial
    if(printResults==1){
    printf("\n\nUsing Serial\n");
    printf("The solution obtained is: \n");
     print_primes(primes, size);
    
    //Print the time taken
    printf("The total time taken: ");
    }
    printf("%lf ", diffTimeSer);
    //Using Parallel
    if(printResults==1){
    printf("\n\nUsing Parallel OpenMP\n");
    printf("The solution obtained is: \n");
       print_primes(primesPar, size);
   
    //Print the time taken
    printf("The total time taken: ");
    }
    printf(" %0.6lf\n", diffTimePar);

    return(0);
}

