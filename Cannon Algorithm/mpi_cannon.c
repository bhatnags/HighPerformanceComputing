#include<stdio.h>
#include<mpi.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

int* create_matrix_arr(int n){
	int *mat = calloc(n*n, sizeof(int));
	return mat;
}

void populate_matrix_arr(int *arr, int n){
	int i; 
	for(i = 0; i < n*n; i++){
		arr[i] = rand() % 10 + 1;
	}
}

int mat_comp(int *a, int *b, int n){//function for matrix comparison
	int i = 0;
	for(i = 0; i < n*n; i++){
		if(a[i] != b[i]){
			return 0;
		} 
	}
	return 1;
}

matmul(int n, int *a, int *b, int *c){
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
				c[i][j] += a[i][j] * b[i][j];
}

void init_align(*A, *B, int N, int bloc_no, int bloc_sz){
int step;
int r = N; int c = N; //row and column of the main matrix
int i,j;
int n;//size or bloc matrix
int row, col; //row and column of bloc matrix
n = N/ bloc_sz;
col = (N/ bloc_sz)-1;
row = (N/ bloc_sz)-1;
	for(step = 0; step < r * c; step++){//shift left acc to the column number - initial alignment
		a[i][j] = A[r%bloc_sz][c%bloc_sz]
		for(i = 0; i< row; i++){
			for(j = 0; j< col; j++){
				if(j<i){
				a[i][j] = a[i][j-i+n]
				}else{
				a[i][j] = a[i][j-i]
				}
			}
		}
	}
	for(step = 0; step < r * c; step++){//shift one column left - next alignment
		b[i][j] = B[r%bloc_sz][c%bloc_sz]
		for(j = 0; j< col; j++){ //shift up acc to the row number - initial alignment
			for(i = 0; i< row; i++){
				if(i<j){
				a[i][j] = a[i-j+n][j]
				}else{
				a[i][j] = a[i-j][j]
				}
			}
		}
	}
}

void next_align(*A, *B, int N, int bloc_no, int bloc_sz){
int step;
int r = N; int c = N; //row and column of the main matrix
int i,j;
int n;//size or bloc matrix
int row, col; //row and column of bloc matrix
n = N/ bloc_sz;
col = (N/ bloc_sz)-1;
row = (N/ bloc_sz)-1;
	for(step = 0; step < r * c; step++){//shift one column left - next alignment
		a[i][j] = A[r%bloc_sz][c%bloc_sz]
		for(i = 0; i< row; i++){
			for(j = 0; j< col; j++){
				if (j == 0) 
					col_zero = a[i][0];
				if (j < (col - 1))
					a[i][j] = a[i][j+1];
				else
					a[i][j] = col_zero;
			}
		}
	}
	for(step = 0; step < r * c; step++){//shift one column left - next alignment
		b[i][j] = B[r%bloc_sz][c%bloc_sz]
		for(j = 0; j< col; j++){ //shift one row up - next alignment
			for(i = 0; i< row; i++){
				if (i == 0)
					row_zero = b[0][j];
				if (i < (row - 1))
					b[i][j] = b[i+1][j];
				else
					b[i][j] = row_zero;
			}
		}
	}
}




int main(int argc, char *argv[]){
	int N; //Size of matrix, assuming square matrix of size N*N
	int myid,nproc;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Status status;

	int bloc_no = N/sqrt(nproc);
	int bloc_sz = N/bloc_no;
	
	int send_a[block_sz * block_sz], recv_a[block_sz * block_sz];
    int send_b[block_sz * block_sz], recv_b[block_sz * block_sz];

	int dest, source;

	if(rank==0){
		int *A = create_matrix_arr(N);
		populate_matrix_arr(&A[0], N);
		int *B = create_matrix_arr(N);
		populate_matrix_arr(&B[0], N);
		int *C = create_matrix_arr(N);
		
		MPI_Barrier(MPI_COMM_WORLD);
		init_align(*A, *B, int N, int bloc_no, int bloc_sz);
		
		MPI_Sendrecv(send_a, block_sz*block_sz, MPI_FLOAT, dest, 1, recv_a, block_sz*block_sz, MPI_FLOAT, source, 1, MPI_Comm , &status); 
		MPI_Sendrecv(send_b, block_sz*block_sz, MPI_FLOAT, dest, 1, recv_b, block_sz*block_sz, MPI_FLOAT, source, 1, MPI_Comm, &status); 
		C += A*B;
		MPI_Barrier(MPI_COMM_WORLD);

		for(int loop = 0; loop < bloc_no; loop++){
			next_align(*A, *B, int N, int bloc_no, int bloc_sz);
			MPI_Sendrecv(send_a, block_sz*block_sz, MPI_FLOAT, dest, 1, recv_a, block_sz*block_sz, MPI_FLOAT, source, 1, MPI_Comm , &status); 
			MPI_Sendrecv(send_b, block_sz*block_sz, MPI_FLOAT, dest, 1, recv_b, block_sz*block_sz, MPI_FLOAT, source, 1, MPI_Comm, &status); 
			C += A*B;
			MPI_Barrier(MPI_COMM_WORLD);
		}
	}

	if(rank == 0){// Serial multiplication to check the results
		int *chk_c = create_matrix_arr(N);
		matmul(N, A, B, chk_c);
		int comp = mat_comp(&chk_c[0], &c[0], N); //matrix elements comparison
		if(comp){
			printf("\nBoth the matrices are same!\n");
		}
	}

	MPI_Finalize();
	return 0;
}