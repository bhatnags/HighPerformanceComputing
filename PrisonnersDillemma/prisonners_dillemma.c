#include <stdio.h>
#include <stdlib.h>

#define for_i for(i=0; i<siz_pop; i++)
int i;


/*Command line to be input as below*/
//  ./a.out size_population 7 no_gen 6 no_iter 5 crossover 90 mutation 1

int *createdata(int siz_pop){ // allocate memory for the game
	int *ptr;
	ptr = (int *)malloc(sizeof(int)*siz_pop);     
	if(ptr != NULL){
		for_i {
			ptr[i] = 0.0;       
		}
	} 
	return ptr; // return the pointer
}  

int *gendata(int siz_pop) { // create the game
	int *ptr = createdata(siz_pop); 
	for_i{
		ptr[i] = rand() < RAND_MAX/2 ? 1 : 0;       
	}     
	return ptr; // return the pointer 
}

int sum_arr(int arr[],int siz_pop, int j){  //input array and array size and element for which the fitness is to be calculated
	int sum = 0;
	for(j = 0; j< siz_pop; j++){
		sum += arr[j];
	}
	sum = sum - arr[j];
	return sum;
}

int main(int argc, char *argv[]){
	//size of population
	int siz_pop = atoi(argv[2]); //should be greater than equal to 2


	// no of iterations
	int no_iter = atoi(argv[6]);

	for(int iter = 0; iter < no_iter; iter++){
	
		printf("\n\nNo of iteration of the game: %d\n", iter+1);
		
		int *data_a = gendata(siz_pop);
		int *data_b = gendata(siz_pop);
		int *data_c = (int *)calloc(siz_pop, sizeof(int));
		int *data_temp = (int *)calloc(siz_pop, sizeof(int));

		/*Create the first two games*/
		printf("Game 1\n");
		for_i{
			printf("%d",data_a[i]);
		}
		printf("\nGame 2\n");
		for_i{
			printf("%d",data_b[i]);
		}
		printf("\n");

		/*Play the game*/

		//no of generations
		int no_gen = atoi(argv[4]);
		int gen=0;
		

		// crossover rate
		int crossover = atoi(argv[8]); //in percentages

		// mutation rate
		int mutation = atoi(argv[10]); //in percentages

		int sum_a; //fitness of first game
		int sum_b; //fitness of second game
		int sum_c; //fitness of third game
		
		for(gen = 0; gen<no_gen; gen++){
		printf("Game %d\n", gen+3);
			for_i{
				sum_a = sum_arr(data_a, siz_pop, i); // Get the fitness for each element in the game
				sum_b = sum_arr(data_b, siz_pop, i); // Get the fitness for each element in the game
				//printf("for pop = %d fitness_a = %d fitness_b = %d\n", i, sum_a, sum_b);

				if(sum_a > sum_b){ //if in second game the fitness score was lesser than the first game
					data_c[i] = 0;
				}else {
					data_c[i] = 1;
				}
			
			printf("%d", data_c[i]);

			int range = (rand() % (siz_pop+1)); // random crossover point 

			if(i>range){
				data_temp[i] = data_a[i];
				data_a[i] = data_b[i];
				data_b[i] = data_temp[i];
			}

			//Take the best fitness
			sum_a = sum_arr(data_a, siz_pop, 0) + data_a[0]; 
			sum_b = sum_arr(data_b, siz_pop, 0) + data_b[0];
			sum_c = sum_arr(data_c, siz_pop, 0) + data_c[0];
			
			}
			printf("\n");
			
			sum_a > sum_b ? : (*data_a = *data_b);
			*data_b = *data_c;	
		
			//mutation
			int mu_pt = (rand() % (siz_pop+1)); // random mutation point 
			data_a[mu_pt] = data_a[mu_pt] & 1; //Using bitwise operators to mutate
			data_b[mu_pt] = data_b[mu_pt] & 1; //Using bitwise operators to mutate
		}
	free(data_temp);
	}
	return 0;

}
