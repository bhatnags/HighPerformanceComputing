struct Node{//store the data, height and pointers to the two child nodes
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};
 
struct Node *node_create(int data);//allocates memory for the new node and stores the data, giving pointers to child branches as NULL
int max(int a, int b);// A utility function to get maximum of two integers
int height(struct Node *N);// Find the height of an AVL node 
int balanceFactor(struct Node *N);// Get Balance factor of node N 
struct Node *rightRotate(struct Node *x);//rotate the child to the right
struct Node *leftRotate(struct Node *x);//rotate the child to the left`
struct Node* balance_tree(int bf, int balance_right, int balance_left, struct Node* N, struct Node* R, struct Node* L);//balance the tree using balance factor
struct Node* insert(struct Node* node, int data);//insert the data
struct Node* balance(struct Node* node);//balance the tree node 
struct Node * minValue(struct Node* node);//to get min data value of the tree
struct Node* delete(struct Node* root, int data); //delete the data by recursively searching
void DFS(struct Node *root);//print the data using DFS

