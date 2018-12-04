#include<stdio.h>
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

List* read_textfile(char* fileName);
void write_binfile(List l, char* filename);
void read_binfile(List l, char* filename);

int main(){
char *fname = "binary.dat";
List l;
write_binfile(l, fname);
read_binfile(l, fname);
}
