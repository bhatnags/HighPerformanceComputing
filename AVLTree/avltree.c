#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "avltree.h" 
 
struct Node *node_create(int data){//allocates memory for the new node and stores the data, giving pointers to child branches as NULL
	struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
	node->data   = data;
	node->left   = NULL;//left branch node pointer initialized with NULL
	node->right  = NULL;
	node->height = 1; 
	return(node);
}

int max(int a, int b){// To get maximum of two integers
	return (a > b)? a : b;
}

int height(struct Node *N){// Find the height of an AVL node
	if (N == NULL)
		return 0;
	return N->height;
}

int balanceFactor(struct Node *N){// Get Balance factor of node N
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
struct Node *rightRotate(struct Node *x){
	struct Node *newNode = x->left;
	struct Node *tmp = newNode->right;
	newNode->right = x;
	x->left = tmp;
	x->height = ((height(x->left)> height(x->right)) ? height(x->left) : height(x->right))  + 1;
	newNode->height = ((height(newNode->left)> height(newNode->right)) ? height(newNode->left) : height(newNode->right))+1;
	return newNode;
}

struct Node *leftRotate(struct Node *x){
	struct Node *newNode = x->right;
	struct Node *tmp = newNode->left;
	newNode->left = x;
	x->right = tmp;
	x->height = ((height(x->left)> height(x->right)) ? height(x->left) : height(x->right))  + 1;
	newNode->height = ((height(newNode->left)> height(newNode->right)) ? height(newNode->left) : height(newNode->right))+1;
	return newNode;
} 
 
struct Node* balance_tree(int bf, int balance_right, int balance_left, struct Node* N, struct Node* R, struct Node* L){
	if (bf > 1 && balance_left > 0)    // Left Left Case
		return rightRotate(N);
	if (bf > 1 && balance_left < 0) {   // Left Right Case
		L =  leftRotate(L);
		return rightRotate(N);
	}
	if (bf < -1 && balance_right < 0)    // Right Right Case
		return leftRotate(N); 
	if (bf < -1 && balance_right > 0)    {    // Right Left Case
		R = rightRotate(R);
		return leftRotate(N);
	}
return N;
}

struct Node* insert(struct Node* node, int data){
	if (node == NULL)    //BST 
		return(node_create(data));

	if (data < node->data)
		node->left  = insert(node->left, data);
	else if (data > node->data)
		node->right = insert(node->right, data);
	else // Equal data
		return node;

	node->height = 1 + max(height(node->left), height(node->right));    //add 1 to depth 

	int bf = balanceFactor(node);	//For self Balance
	if(abs(bf)>1){
		node = balance_tree(bf, balanceFactor(node->right), balanceFactor(node->left), node, node->right, node->left);
	}
return node;
}

struct Node* balance(struct Node* node){
	if (node == NULL)
		return(node);
	int bf = balanceFactor(node);
	if(abs(bf)>1){
	node = balance_tree(bf, balanceFactor(node->right), balanceFactor(node->left), node, node->right, node->left);
	}
return node;
} 

struct Node * minValue(struct Node* node){//to get min data value of the tree
	struct Node* current = node;
	while (current->left != NULL)
		current = current->left; 
	return current;
}
 
struct Node* delete(struct Node* root, int data){ //delete the data by recursively searching
	if (root == NULL)    // BST
		return root;

	if ( data < root->data )    // lies in left subtree
		root->left = delete(root->left, data);
	else if( data > root->data )    // lies in right subtree
		root->right = delete(root->right, data);
	else{    // node to be deleted
		if((root->left == NULL) || (root->right == NULL)){        // node with either left or right node
			struct Node *tmp = root->left ? root->left : root->right; 
			if (tmp == NULL){            // No adjacent node
				tmp = root;
				root = NULL;
			}else{ // One adjacent node
				*root = *tmp; // Copy the contents of the non-empty node
				free(tmp);
			}
		}else{// node with two adjacent nodes
			struct Node* tmp = minValue(root->right); 
			root->data = tmp->data;            // get the successor's data to this node 
			root->right = delete(root->right, tmp->data);            // Delete the successor
		}
	}

	root->height = 1 + max(height(root->left),height(root->right));

	int bf = balanceFactor(root);
	if(abs(bf)>1){
		root = balance_tree(bf, balanceFactor(root->right), balanceFactor(root->left), root, root->right, root->left);
	}
return root;
}
 
void DFS(struct Node *root){
	if(root != NULL)    {
		printf("%d ", root->data);
		DFS(root->left);
		DFS(root->right);
	}
}
 /*
void createArray(struct Node *root){
	if(root != NULL)    {
		printf("%d ", root->data);
		DFS(root->left);
		DFS(root->right);
	}
}*/
 
/*
int randNode(Node *root, int count){
	if(!root){
	  return 0;
	}
	if(count == chi)

}*/
