# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include <stdbool.h>
# include <getopt.h>

int N, r, c;

int tsp(int city, int arr[r][c], int vis[r]){//get nearest city for "r", c = #columns
	int j, nearest = 999, cost = 0;
	int minimum = 999, temp;

	for(j = 0; j < c; j++){
	if((arr[city][j] != 0) && (vis[j] == 0)){
        	if(arr[city][j] < minimum){
                	 minimum = arr[j][0] + arr[city][j];
               	}
                temp = arr[city][j];
                nearest = j;
        }
	}
      	if(minimum != 999){
        	cost = cost + temp;
      	}

return nearest;
}

void mincost(int city, int arr[r][c], int completed[r], bool graph){
    int ncity, cost =0;
 
    completed[city]=1;
    if(!graph){	printf("%d--->",city);	}
    ncity=tsp(city, arr, completed);
    if(ncity==999){
        ncity=0;
        if(!graph){	printf("--->%d",ncity);	}
        cost+=arr[city][ncity];
        return;
    }
    mincost(ncity, arr, completed, graph);
}

void randMap(int map[r][c]){
	for(int i = 0; i< r;i++){//random allocate distance between cities
		for(int j = 0; j< c;j++){
		if(i < j){
			map[i][j] = rand() % 10 +1 ;
		}
		}
	}
	for(int i = 0; i< r;i++){//random allocate distance between cities
		for(int j = 0; j< c;j++){
		if(i > j){
			map[i][j] = map[j][i];
		}
		if(i == j){//no distance when same city
			map[i][j] = 0;
		}
		}
	}
}

void printMap(int map[r][c]){
	for(int i = 0; i< r;i++){
		for(int j = 0; j< c;j++){
			printf("%d\t",map[i][j]);
		}
	printf("\n");
	}
}

int recFunc(){
	r = (int)(sqrt(N)); //rand() % n;
	//if(arr[r] == 1){
	//	recFunc(arr);
	//}
	return r;
}

int getRow(){
	int arr[N]; 
	for(int i = 0; i<N; i++){
		arr[i]=1;
	}
	for(int i = 1; i<N; i++){
		if(N%i==0){
			arr[N] = N;
		}else{
			arr[N] = 1;
		}
	}

	r = recFunc(arr);
return r;
}

int getCol(){
	c = N/r;
return c;	
}


