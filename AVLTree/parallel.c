#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "avltree.h" 

static pthread_mutex_t my_lock;

static pthread_t balanceTreeThread;
static pthread_t deleteTreeThread;
static pthread_t insertTreeThread;

static struct Node *node;

static void *balanceTree(void *arg){
	  pthread_mutex_lock(&my_lock);
	  node = balance(node);
	  printf("The tree is balanced\n");
	  DFS(node);
	  pthread_mutex_unlock(&my_lock);
	return NULL;
}

static void *deleteTree(void *arg){
	   pthread_mutex_lock(&my_lock);
	   if(node != NULL){
		int data = rand()%50;
		delete(node, data);
		printf("Deleted data %d\n ", data);
		DFS(node);
	   }
	   pthread_mutex_unlock(&my_lock);
	return NULL;
}

static void *insertTree(void *arg){
	   pthread_mutex_lock(&my_lock);
	   int data = rand()%50;
	   insert(node, data);
	   printf("Inserted data %d\n ", data);
	   DFS(node);
	   pthread_mutex_unlock(&my_lock);
	return NULL;
}

int main(void){
	printf("Inserting random keys:\n");
	pthread_create(&insertTreeThread, NULL, insertTree, NULL);
	pthread_create(&insertTreeThread, NULL, insertTree, NULL);
	pthread_create(&insertTreeThread, NULL, insertTree, NULL);
	pthread_create(&insertTreeThread, NULL, insertTree, NULL);
	pthread_create(&deleteTreeThread, NULL, deleteTree, NULL);
	pthread_create(&balanceTreeThread, NULL, balanceTree, NULL);
	DFS(root);
return 0;
}
