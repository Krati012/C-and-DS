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

//Recursive function to construct binary tree of size n from inorder traversal in[] and postorder traversal post[]
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

    //Using index in in[], construct left and right subtress
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

int main(){
    int in[] = {8,6,9,4,7,2,5,1,3};
	int post[] = {8,9,6,7,4,5,2,3,1};
    int n = sizeof(in)/sizeof(in[0]);

    struct Node* root = constructTree(in, post, n);

    int ht = maxDepth(root) - 1;

    printf("Height of Binary Tree is %d\n", ht);
    return 0;
}
