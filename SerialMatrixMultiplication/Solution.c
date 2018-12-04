


/*************************************Serial Matrix multiplication********************************************/


/**********************-----------------------------------------------------------*************************************/
/*************************There is no best algorithm for matrix multiplication***************************************/
/*********************It varies depending on the architecture of the target platform*************************************/
/********************---------------------------------------------------------------**********************************/


/********************Some commonly used algorithms basis their use cases are explained below********************************/
/*******************************************************************************************************************/


/*				Smaller matrices: Naive Algorithm might be best. 
							Recursively computing 8 products 
							Summing up the N squared values, gives cubic running time O(n^3)

				Larger matrices: Schonhage-Strassen algorithm, based on Fast Fourier Transform, 
							Computes seven products. Just a reduction in one product reduces the order &
							gives O(N^2.8)

				Other algorithms include:
				
				Coppersmith Winograd - gives better asymptotic running time than the Strassen algorithm O(N^2.376)
							
				
				Algorithm given by Stothers: improvement to the Coppersmith Winograd algorithm, 
							gives O(n^2.73….) time algorithm
				Algorithm given by Virginia Williams : further improvement to the Coppersmith Winograd algorithm, 
							gives O(n^2.73….) time algorithm



*/



/*******************************************************************************************************************/
/*****************************************-------------------------------********************************************/
/****************************************|     Using Naive method       |***************************************/
/*****************************************-------------------------------********************************************/
/*******************************************************************************************************************/


#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <sys/time.h>

/*~~~~~~~~~~~~~~Storing the time spent in a file for every multiplication computation~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
    typedef struct
    {
      int size;
      int time;
    } time_spent;

      time_spent a[1];
*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


double **read_matrix(int rows, int cols);
void print_matrix(int rows, int cols, double **mat);
void free_matrix(int rows, double **mat);


double **random_matrix(int rows, int cols)
{
	double **mat = (double **) malloc(sizeof(double *)*rows);
	int i=0,j=0;
	for(i=0; i<rows; i++)
	mat[i] = (double *) malloc(sizeof(double)*cols); // Allocate array, store pointer 

	for(i=0; i<rows; i++)
		{
		for(j=0; j<cols; j++)
		{
		mat[i][j] = ((rand() % 4)-2); //Using rand() from stdlib.h
		}
	}
return mat;
}

void print_matrix(int rows, int cols, double **mat)
{
	int i=0,j=0;
	for(i=0; i<rows; i++)
		 /* Iterate of each row */
		{   
		for(j=0; j<cols; j++){  /* In each row, go over each col element  */
		printf("%lf ",mat[i][j]); /* Print each row element */
		}
	printf("\n");
	}
}

void free_matrix(int rows, double **mat)
{
	int i=0;
	for(i=0;i<rows;i++)    
		free(mat[i]);
		free(mat);
}

double **mat_mul(double **a, double **b, double **c, int l, int m, int n) 
{
int i, j, k, sum;
c = (double**)malloc(sizeof(double*)*l);

for (i = 0; i < l; i++) { 
c[i] = malloc(sizeof(double)*n); 
for (j = 0; j < n; j++) { 
// Initialize the element to zero. 
c[i][j] = 0; 
for (k = 0; k < m; k++) { 
// Accumulate the result 
c[i][j] += a[i][k] * b[k][j]; } } }  //print_matrix(l,n,c);

return c;
}

int main(){


	double **matrix_A, **matrix_B, **matrix_C;
	int l,m,n; //  int rows, cols.
	time_t t; // Getting current time for seed initialization.
	srand((unsigned) time(&t)); //Intializes random number generator. Initializing the seed.




/* First matrix */
  printf("Considering the matrices of sizes (l x m) & (m x n), giving output matrix as (l x n). Enter the values of l, m & n: ");
  scanf("%d %d %d",&l,&m, &n);
  matrix_A = random_matrix(l,m); 
  matrix_B = random_matrix(m,n); 
  printf("Matrix A\n");  /* Print the first matrix */
  print_matrix(l,m,matrix_A);

/*Second matrix*/
  printf("Matrix B\n");  /* Print the second matrix */
  print_matrix(m,n,matrix_B);


  printf("Matrix C\n");  /* Print the resultant matrix */

/*Computing the multiplication time*/
  struct timeval start, end;
  gettimeofday(&start, NULL); // Using gettimeofday function to calculate the time taken by matrix multiplication

  matrix_C = mat_mul(matrix_A, matrix_B, matrix_C, l, m, n);
  print_matrix(l,n,matrix_C);

  gettimeofday(&end, NULL);
  double elapsed = (end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec)/1000000.0);
  printf("The time taken for computation(in microseconds) is: %ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
          - (start.tv_sec * 1000000 + start.tv_usec)));
  int matrixSize = l*m*n;



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~Read file and print the content ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
   FILE *fp;
   FILE *fp2;
   int count = 1;
   fp = fopen("time_spent.txt","r");
   float d;
   double f;
   char ch;
   int linecount = 0;
   if ( fp )
   {
	//Repeat until End Of File character is reached.	
	   while ((ch=getc(fp)) != EOF) {
		  // Increment line count if new line character
		   if (ch == '\n') { ++linecount; }
		   


	   }
    }
   else
      {
         printf("Failed to open the file\n");
        }

    printf("Lines : %d \n", linecount);

   getchar();
   for(int i = 0; i < linecount; i++)
   {
    for (int j = 0 ; j < 2; j++)
    {
      fscanf(fp,"%lf %ld",&f,&d);
      printf("values : %.15f %.15d ",f,d);
      fp2 = fopen("time_spent.txt","r+");
      fprintf(fp2, "%f ", f);
    }
   fprintf(fp2, "\n");
   }
   fp2 = fopen("time_spent.txt","r+");
   for (int i=0; i<1; ++i)
         fprintf(fp2, "%d %f ", matrixSize, elapsed);
   fclose(fp);
   fclose(fp2);
*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



  printf("%lf\n",elapsed);
/* Free the matrix */
  free_matrix(l, matrix_A);
  free_matrix(m, matrix_B);
  free_matrix(l, matrix_C);
  return 0;
 }


