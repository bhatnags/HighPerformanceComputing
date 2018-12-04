/*
* Assignment on Linked list
*
* Author : Saumya Bhatnagar
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cell_struct{
struct Cell_struct* next;
struct Cell_struct* prev;
char* word;
}
Cell;

typedef struct{
struct Cell_struct* head;
struct Cell_struct* tail;
}
List;

List append(char* word, List l){
	Cell *n; 
	n = (Cell*)malloc(sizeof(Cell)); //Dynamic memory allocation
	n->next = NULL; // setting up the next of the cell
	n->prev = l.tail; // appending it in the end of the list
	l.tail->next = n; // putting the next of the list on n
	n->word = word; // feeding data
	return l;	
}

void print_list(List l){
	while(l.tail != NULL){
		/*Accessing the word on the address contained by tail*/
		printf("%s\n", l.tail -> word);
		/*Updating the pointer tail of list to access next cell*/
		l.tail = l.tail -> next;
	}	
}

void free_list(List l){
	Cell *n; 
	while(l.tail != NULL){
	    n->prev = l.tail->next;
	    free(l.tail->word); //first free the data
	    free(l.tail); //free the list
	    l.tail=n->next;//make next as the list to loop freeing 
	}
}

List insert_before(char* find, char* new_word, List l){
	while(l.tail->word != find) {//navigate through list
		if(l.tail->next == NULL) {//if it is last node
			return l;
		} else {           
			l.tail = l.tail->next; //move to next link
		}
	}
	Cell * cell = (Cell*)malloc(sizeof(Cell)); //create a link
	cell->word = new_word; //insert the data
	if(l.tail->word == find){ //word found
		cell->next = l.tail->prev;  //insert before
		cell->prev = l.tail->next; //link
	}
	return l; 
}

List insert_after (char* find, char* new_word, List l){
	while(l.tail->word != find) {//navigate through list
		if(l.tail->next == NULL) {//if it is last node
			return l;
		} else {           
			l.tail = l.tail->next; //move to next link
		}
	}
	Cell * cell = (Cell*)malloc(sizeof(Cell)); //create a link
	cell->word = new_word; //insert the data
	if(l.tail->word == find){//word found
		cell->prev = l.tail->next;  // insert after
		cell->next = l.tail->prev; //link
	}
	return l; 
}

List reverse(List l){
	while(l.tail->next == NULL){ //if it is the last node
		/*Accessing the word on the address contained by tail*/
		printf("%s\n", l.tail -> word);
		/*Updating the pointer tail of list to access prev cell, traversing in reverse direction*/
		l.tail = l.tail -> prev;
	}	
}


int main(){
List append(char* word, List l);
void print_list(List l);
void free_list(List l);
List insert_before(char* find, char* new_word, List l);
List insert_after (char* find, char* new_word, List l);
List reverse(List l);
}
