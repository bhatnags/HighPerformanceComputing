# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include <stdbool.h>
# include <getopt.h>

int N, r, c;

void copy(int a[N], int b[N]){
	for(int i = 0; i<N; i++){
		b[N] = a[N];
	}
}


void swap(int a, int b){
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}



//Recursively checks the cost
void tspBrute(int map[r][c], int i){
	
	int min = 999;
	int route[N], cities[N];
	if (i == N) {
		int len;
		for(int count=1; count<=N; count++){
			len += map[i-1][i%N];// = route_len(cities);
		}
		if (len < min) {
			copy(cities, route);
			min = len;
		}
		return;
	}

	for (int j = i; j < N; j++) {
		swap(cities[i], cities[j]);
		tspBrute(map, i+1);
		swap(cities[i], cities[j]);
	}
}

