# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include <time.h>
# include <stdbool.h>
# include <getopt.h>
# include "greedy.h"
# include "brute.h"

bool print, timing, graph, bf, dynamic;
int N, r, c;
char *filename;

int parseArguments (int argc, char *argv[]);
void printUsage ();
int countOfLinesFromFile();
void readFromFile();
    


int main(int argc, char *argv[]) {
	float timeDiffBrute, timeDiff;
	struct timeval  startTimeBrute, endTimeBrute, startTime, endTime;

	N = 16; //Random Number of cities, in case file input and num cities input both kept blank
	print=false; timing=true; graph = false, bf = false, dynamic = true;

	parseArguments (argc, argv);
	if(graph==false){	printf("Add -h in CL for help\n");	}

	FILE *fp;
	fp=fopen(filename, "r");
	
	if(fp != NULL) {
		r = countOfLinesFromFile(fp);
	}else{
		r = N;
	}
	c = N;//getCol(r);

	int map[r][c];
	int completed[r];
	for(int i = 0; i<r; i++){completed[i]=0;}
	if(fp!= NULL){
		readFromFile(fp);
	}else{
		randMap(map);
	}
	if(print){	printMap(map);	}

	/***************BRUTE FORCE METHOD****************/
	if(bf){
		gettimeofday(&startTimeBrute, NULL);
		tspBrute(map, 0);
		gettimeofday(&endTimeBrute, NULL);
		timeDiffBrute = ((endTimeBrute.tv_usec - startTimeBrute.tv_usec)+ (endTimeBrute.tv_sec - startTimeBrute.tv_sec)*1000000);

		if(graph){	printf("%d\t%.3f\n", r, timeDiffBrute);	}
		if(timing && !graph){
		printf("\nTime taken in running a map size of %d \n\tBruteMethod = %.3fmsec\n", N, timeDiffBrute);
	}	
	}
	/****************DYNAMIC PROGRAMMING****************/
	if(dynamic){
		gettimeofday(&startTime, NULL);
		mincost(0, map, completed, graph);
		gettimeofday(&endTime, NULL);
		timeDiff = ((endTime.tv_usec - startTime.tv_usec)+ (endTime.tv_sec - startTime.tv_sec)*1000000);
		if(graph){	printf("%d\t%.3f\n", r, timeDiff);	}
	if(timing && !graph){
		printf("\nTime taken in running a map size of %d \n\tGreedy Algorithm = %.3fmsec\n", N, timeDiff);
	}	
	}	
	
return 0;

}

int countOfLinesFromFile(FILE *fp){
	fp = fopen(filename, "r");
	int ch, number_of_lines = 0;
	do{
	    ch = fgetc(fp);
	    if(ch == '\n')
	        number_of_lines++;
	}while (ch != EOF);
	if(ch != '\n' && number_of_lines != 0)
	    number_of_lines++;
	fclose(fp);
	return number_of_lines;	
}

void readFromFile(FILE *fp){
	int** map = malloc(r*sizeof(int));
	for(int i = 0; i< r; i++){
		map[i] =malloc(c*sizeof(int));
	}
	for(int i = 0; i< r; i++){
		for(int j = 0; j< c; j++){
			if(!fscanf(fp, "%d", &map[i][j]))
				break;
		}		
	}
	fclose(fp);
}

int parseArguments (int argc, char *argv[]) {
	int c_opt;

	while ((c_opt = getopt (argc, argv, "n:f:bdgtph:")) != -1) {
		switch(c_opt) {
			case 'n':
				N = atoi(optarg); break;
			case 'f':
				filename = argv[optind]; break;
			case 'b':
				bf = true; break;
			case 'd':
				dynamic = false; break;
			case 'g':
				graph = true; break;
			case 't':
				timing = true; break;
			case 'p':
				print = true; break;
			case 'h':
				printUsage(); exit(0); break;
			default:
				fprintf(stderr, "Invalid option given\n");
				printUsage();
				return -1;
		}
	}
	return 0;
}
void printUsage () {
	printf("Travelling Salesman Problem\n");
	printf("by: Saumya Bhatnagar <bhatnags@tcd.ie>\n");
	printf("This program will solve TSP by Brute Force Method\n");
	printf("usage:\n");
	printf("      -n	( will set the number of cities)\n");
	printf("      -f	( will get the name of the file to be used)\n");
	printf("      -b	( will run the Brute force method)\n");
	printf("      -d	( will turn off the dynamic programming method)\n");
	printf("      -g	( will get the data for the graph)\n");
	printf("      -p	( will print the map\n");
	printf("      -t	( will output the amount of time taken\n");
	printf("      -h	( will show this usage\n");
	printf("     \n");
}

