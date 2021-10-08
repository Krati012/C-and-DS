// C program to recursively construct binary tree from inorder traversal in[] and postorder traversal post[]
#include <stdio.h>
#include <stdlib.h>

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
    struct Node* node = newNode(post[*pIndex]);
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

//Helper function for generate_inorder()
void printInorder(struct Node* node, int *array)
{
	static int count = 0;
    if (node == NULL)
        return;

    printInorder(node->left, array);

 	array[count] = node->data;
 	count++;

    printInorder(node->right,array);
    return;
}

//Generates inorder array for any height 
int *generate_inorder(int height)
{
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
	//Puts element of the tree into an array in inorder traversal
	printInorder(root, array);
	//returns pointer to the array
	return array;
}

int main(){
    int in[] = {8,6,9,4,7,2,5,1,3};
	int post[] = {8,9,6,7,4,5,2,3,1};
    int n = sizeof(in)/sizeof(in[0]);

    struct Node* root = constructTree(in, post, n);

    int ht = maxDepth(root) - 1;

    printf("Height of Binary Tree is %d\n", ht);

    //Verification using random binary tree of height 20
    int in2[] = {40, 38, 41, 36, 39, 34, 37, 32, 35, 30, 33, 28, 31, 26, 29, 24,
            27, 22, 25, 20, 23, 18, 21, 16, 19, 14, 17, 12, 15, 10, 13, 8, 11,
            6, 9, 4, 7, 2, 5, 1, 3};
    int post2[] = {40, 41, 38, 39, 36, 37, 34, 35, 32, 33, 30, 31, 28, 29, 26, 27, 24,
            25, 22, 23, 20, 21, 18, 19, 16, 17, 14, 15, 12, 13, 10, 11, 8, 9, 6,
            7, 4, 5, 2, 3, 1};

    int m = sizeof(in2)/sizeof(in2[0]);
    struct Node* root2 = constructTree(in2, post2, m);

    int ht2 = maxDepth(root2) - 1;
    printf("Height of Binary Tree is %d\n", ht2);

    int h = 20;
    //scanf("Enter required height %d", h);
    int x = 2*h+ 1;
    int *p = generate_inorder(h);

    printf("Inorder array for height %d is: ", h);
    for(int i=0; i<x; i++){
        printf("%d ", *(p + i));
    }

    //Using generated inorder array & prev postorder to find height(20) of binary tree
    struct Node* root3 = constructTree(p, post2, m);

    int ht3 = maxDepth(root3) - 1;
    printf("\n Height of Binary Tree is %d\n", ht3);

    return 0;
}
