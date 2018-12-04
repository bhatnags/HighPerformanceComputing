/*Please take consecutive numbers as the nodes*/
/*Please start with node 0*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define for_l for(l=0; l<128; l++)
#define for_m for(m=0; m<128; m++)
#define for_i for(i=0; i<l; i++)
#define for_j for(j=0; j<l; j++)

#define l_size sizeof(line)

typedef struct node{
    struct node *next;
    char vertex;
}node;

int visited[50],G[25][25];

int fd(char *filename){
    FILE *file = fopen ( filename, "r" );
    int l, m, k;                                                //array coordinates
    char arra[128][128];                                    //create the data array
    char line[128];                                            //assume maximum line size 

    for_l
        for_m
            arra[l][m] = '\0';
    for_l
        line[l] = '\0';

    if ( file != NULL ){                                    //read a non empty file
    l=0;
    while ( fgets ( line, l_size, file ) != NULL ){    //read a line 
		strcpy(arra[l], line);                                    //copy the read line from above code in the array
		char *token;
		const char delim[2] = ";" ;
		token = strtok(arra[l], delim);
		while(token != NULL){    
			if(l != atoi(token)){
				printf("node %d%s\n", l, token);
			}
			k = atoi(token);
			G[l][k]=1;
			token = strtok(NULL, delim);
		}
		l++;
    }
    printf("adjacency mat\n");
	
    int i,j;
    for_i {
        for_j {
            printf("%d",G[i][j]);
	}
	printf("\n");
    }
//    char src[50];
//    char dest[50]=0;
//    for(int m=0;m<7;m++){
//		for(int k=0;k<7;k++){
//    if(G[m][k]==1)
//    itoa(k,src,10);
//    strcpy(dest,src);
//		}
//		printf("\n");
  //  }
//    printf("mat test%s",dest);

    fclose ( file );
    }else{
    perror ( filename ); 
    }
    return 0;
}

void DFS(int i){
	printf(" %d",i);			//Print
	visited[i]=1;                      	//initiate the first node
	for(int j=0;j<7;j++){ 
		if(G[i][j]==1&&visited[j]==0){
		DFS(j);				//Recursion
		} 
	}
}

void main (int argc, char *argv[]){
	fd(argv[1]);
	for(int i=0;i<7;i++)
	visited[i]=0;
	printf("the graph nodes are:\n");
	DFS(0);
}
