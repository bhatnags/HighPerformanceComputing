//=============================================================================================
// Name        		: main.c
// Author      		: Saumya Bhatnagar
// Version     		:	01-03-2018
// Creation date	:	19-02-2018
// Copyright		: No Copyrights
// Description		: This program will use store data using BST(Binary Search Tree) => data(left) < data(root) < data(right)
//						For ordering I'm using an AVL tree(a self-balancing BST where the difference between heights of subtree branches is not more than 1.
//=============================================================================================

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "avltree.h"
 
 
/* Drier program to test above function*/
int main(){
	struct Node *root = NULL;
	root = insert(root, 55);
	root = insert(root, 77);
	root = insert(root, 4);
	root = insert(root, 0);
	root = insert(root, -15);
	root = insert(root, 5);
	root = insert(root, -1);
	balance(root);

	printf("DFS traversal of the AVL tree is \n");
	DFS(root);
	
	int data = -15;
	root = delete(root, data);
	balance(root);

	printf("\nDFS traversal of the AVL tree after deletion of %d is \n", data);
	DFS(root);
	printf("\n");
	
return 0;
}
