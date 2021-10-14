// C program to recursively construct binary tree from inorder traversal in[] and postorder traversal post[]
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node{
    int data;
    struct Node *left, *right;
};

//Utility function to create a new node
struct Node* newNode(int data){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return (node);
}

//Function to find index of value in arr[start....end]
int search(int arr[], int strt, int end, int value){
    int i;
    for(i=strt; i<=end; i++){
        if(arr[i] == value)
            break;
    }
    return i;
}

//Recursive function to construct binary tree of size n from in[] and post[]
struct Node* construct(int in[], int post[], int inStrt, int inEnd, int* pIndex){
    //Base case
    if(inStrt > inEnd)
        return NULL;

    //Pick current node from post[] using postIndex and decrement postIndex
    struct Node* node = newNode(*(post + *pIndex));
    (*pIndex)--;

    //If this node has no children, return node
    if(inStrt == inEnd)
        return node;

    //Else find index of this node in in[]
    int iIndex = search(in, inStrt, inEnd, node->data);

    //Using index in in[], construct left and right subtrees
    node->right = construct(in, post, iIndex+1, inEnd, pIndex);
    node->left = construct(in, post, inStrt, iIndex-1, pIndex);

    return node;
}

//Initialize index of root and call contruct()
struct Node* constructTree(int in[], int post[], int n){
    int pIndex = n-1;
    return construct(in, post, 0, n-1, &pIndex);
}

//Find depth of a binary tree
int maxDepth(struct Node* node){
    //Base case
    if(node == NULL)
        return 0;

    //Find maximum depth in right and left subtree of the node
    int lDepth = maxDepth(node->left);
    int rDepth = maxDepth(node->right);

    if (lDepth > rDepth)
        return lDepth+1;
    else
        return rDepth+1;
}

//Swap function to swap variable values pointed by xp and yp
void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//Helper function for inorder array for generate_order()
void printInorder(struct Node* node, int *array){
	static int count = 0;
    if (node == NULL)
        return;

    printInorder(node->left, array);

 	array[count] = node->data;
 	count++;

    printInorder(node->right,array);
    return;
}

//Helper function for postorder array for generate_order()
void printPostorder(struct Node* node, int *array){
    static int count = 0;
    if (node == NULL)
        return;

    printPostorder(node->left, array);
    printPostorder(node->right,array);

 	array[count] = node->data;
 	count++;

    return;
}

//Generates traversal array for any height
//Use iop = 1 for inorder, iop = 2 for postorder
int *generate_order(int height, int iop){
	//allocate space as for ht h, number of elements in array : 2*ht + 1
	int *array = (int *)malloc((2*height + 1)*sizeof(int));

	struct Node *root = (struct Node *)malloc(sizeof(struct Node));
	root->data = 1;
	struct Node *temp = root;
	for(int i = 0; i < height; i++)
	{
		temp->left = (struct Node *)malloc(sizeof(struct Node));
		temp->right = (struct Node *)malloc(sizeof(struct Node));

		temp->left->data = 2*(i+1);
		temp->right->data = 2*(i+1) + 1;
		temp->right->left = NULL;
		temp->right->right = NULL;
		temp = temp->left;
	}
	temp->left = NULL;
	temp->right = NULL;
	//Puts element of the tree into an array
    if(iop == 1){
        printInorder(root, array);      //iop = 1 for inorder traversal
    }
	else{
        printPostorder(root, array);    //iop = 2 for postorder traversal
	}
	//returns pointer to the array
	return array;
}
