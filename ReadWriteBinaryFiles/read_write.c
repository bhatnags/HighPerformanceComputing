/*
*
* Assignment 6
*
* Doubly Linked List
*
* Author : Saumya Bhatnagar
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct ListNode {
    char* word;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
    ListNode *tail;
} List;

struct NODE{
int roll_no;
char name[30];
};


List* read_textfile(char* fileName){ 
    FILE* file = fopen(fileName, "r");
    assert(file != NULL);

    List* list = malloc(sizeof(List)); // Allocating memory
    assert(list != NULL); //Creating empty list
    list->head = NULL;
    list->tail = NULL;

    char c;
    int word_size = 1;
    char* word = malloc(word_size);
    int word_count = 0;

    while ((c = fgetc(file)) != EOF){
        assert(!ferror(file));
        while (c != ' ' && c != EOF){
            if (word_count == word_size){
                word_size += 1;
                word = realloc(word, word_size);
                assert(word != NULL);
            }

            word[word_count++] = c;

            c = fgetc(file);
            assert(!ferror(file));
        }

        word = realloc(word, word_size + 1);
        word[word_size] = '\0';

        ListNode *node = malloc(sizeof(ListNode));
        assert(node != NULL);
        node->next = NULL;
        node->word = word;

        if (list->head == NULL){
            list->head = node;
            list->tail = node;
        }
        else{
            list->tail->next = node;
            list->tail = node;
        }

        if (c == EOF)
            break;

        word_count = 0;
        word_size = 1;
        word = malloc(word_size);
	}

    free(word);

    assert(!ferror(file));

    return list;
}

void write_binfile(List l, char* filename){
	ListNode *n;
	n = (ListNode*)malloc(sizeof(ListNode)); //Dynamic memory allocation
	FILE *f1; 
	f1 = fopen(filename,"w");
	fwrite(&n, sizeof(n), 1, f1); /* write struct s to file */
}


void read_binfile(List l, char* filename){
	ListNode *n;
	FILE *f1; 
	f1 = fopen(filename,"rb");
	while(fread(&n, sizeof(n), 1, f1))
	{
	printf("\nData : %s",n->word);
	}
}
