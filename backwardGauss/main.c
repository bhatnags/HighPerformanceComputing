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
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include "serial.h"
#include "openmp.h"

int main(int argc, char *argv[]){

    //Clearing the terminal
    system("clear");


    //Get the size of the system of linear euqations
    int size=0; //Number of linear equations

    //Flag to print results
    int printResults = 0;

    printf("\n");
    //Get the number of threads
    int MAXTHREADS = 4;
    if(argc < 3){
	printf("Please provide the number of linear equations in command line\n./backGauss -n 100\n");
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

    if(printResults == 1){
    //Printing configurations
      printf("\nThe size of matrix is");
    }
    printf("%d  ", size);
    if(printResults == 1){
      printf("The Number of threads are");
    }
    printf("%d  ", MAXTHREADS);



    //Varialble declaration
//    int tid=0, chunk, start, end;
    //Time variable declaration
    struct timeval  startTimeSerial, endTimeSerial, startTimePar, endTimePar;
    double diffTimePar, diffTimeSer;
    //Matrix and solution variable declarations
    float **A, *solution, **AP, *solutionP;

    //Creating random matrix
    A = random_matrix(size);
    AP = copy_matrix(A, size);
    
    //Serial process starts
    gettimeofday(&startTimeSerial, NULL);
      //Gauss Elimination starts
      gaussElimSerial(A, size);
      //Backward Substitution starts
      solution=backSubsSerial(A, size);
    gettimeofday(&endTimeSerial, NULL);
    //printf("Results noted");
    //Serial process ends
    //Get the time taken in using serial method
    diffTimeSer = ((double)(endTimeSerial.tv_usec - startTimeSerial.tv_usec)/1000+ (double)(endTimeSerial.tv_sec - startTimeSerial.tv_sec)*1000 );


    //Parallel process starts
    gettimeofday(&startTimePar, NULL);
    //startTimePar = omp_get_wtime();
    //  chunk = size/MAXTHREADS;
      omp_set_num_threads(MAXTHREADS);
    
     // #pragma omp parallel shared(A,solution,chunk)private(tid,start,end)
    //  tid = omp_get_thread_num();
    //  start = tid*chunk;
    //  end= start + chunk;
      //printf("Thread %d created with start and end : %d to %d\n", tid, start, end);
      //Gauss Elimination starts
      gaussElimParallel(AP,size);
      //Backward Substitution starts
      solutionP=backSubsParallel(AP,size);
    gettimeofday(&endTimePar, NULL);
    //endTimePar = omp_get_wtime();
    //printf("Results noted");
    //Parallel process ends
    //Get the time taken using Openmp
    diffTimePar = ((double)(endTimePar.tv_usec - startTimePar.tv_usec)/1000 + (double)(endTimePar.tv_sec - startTimePar.tv_sec)*1000 );

    //Print the solution
    //Using Serial
    if(printResults == 1){
    printf("\n\nUsing Serial\n");
    printf("The solution obtained is: \n");
    print_array(solution,size);
    //Print the time taken
    printf("The total time taken:");
    }
    printf("%lf ", diffTimeSer);
    //Using Parallel
    if(printResults == 1){
    printf("\n\nUsing Parallel OpenMP\n");
    printf("The solution obtained is: \n");
    print_array(solutionP,size);
    //Print the time taken
    printf("The total time taken:");
    }
    printf("%lf\n", diffTimePar);
    if(printResults == 1){
    printf("The time is in milliseconds\n");}    
return(0);
}
