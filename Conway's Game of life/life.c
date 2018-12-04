#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
/*
A function to show the blocks in case the condition is true
*/
void blocks(void *w, int width, int length){
	int (*grid)[width] = w;
	printf("\033[H"); //Repositioning to the head of the page
	for (int y = 0; y < length; y++) {
		for (int x = 0; x < width; x++) printf(grid[y][x] ? "\033[07m  \033[m" : "  "); //if true creating two colored spaces, else only two spaces
		printf("\033[E"); //Repositioning to end
	}
	fflush(stdout); //to avoid delay in printing 
}

/*
A function to count the number of adjacent live cells,
and simultaneously if the live cells' count is 3 then it lives,
and if count is 2, then it dies unless it is already alive
*/ 
void deadoralive(void *w, int width, int length){
	unsigned (*grid)[width] = w;
	unsigned new[length][width];
 
	for (int y = 0; y < length; y++) for (int x = 0; x < width; x++) {
		int count = 0;
		//Checking adjacent array values
		for (int y1 = y - 1; y1 <= y + 1; y1++)
			for (int x1 = x - 1; x1 <= x + 1; x1++)
				if (grid[(y1 + length) % length][(x1 + width) % width])
					 count++;
 
		if (grid[y][x]) count--;
		new[y][x] = (count == 3 || (count == 2 && grid[y][x]));
	}
	for (int y = 0; y < length; y++)
		for (int x = 0; x < width; x++) grid[y][x] = new[y][x];
}

//Creating the game evolution 
void game(int width, int length){
	unsigned grid[length][width];
	for (int x = 0; x < width; x++) 
	for (int y = 0; y < length; y++)
		grid[y][x] = rand() < RAND_MAX / 10 ? 1 : 0; //Defining random grid
	while (1) {
		blocks(grid, width, length);
		deadoralive(grid, width, length);
		usleep(200000);
	}
}
 
int main(int c, char **v){
	int width = 0, length = 0;
	if (c > 1) width = atoi(v[1]);
	if (c > 2) length = atoi(v[2]);
    //Periodic boundaries
	if (width <= 0) width = 40;
	if (length <= 0) length = 40;
	game(width, length);
}
