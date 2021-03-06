// C program to generate inorder and postorder array of random binary tree from given height h
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *left, *right;
};

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

int main(){
    int h;
    printf("Enter height h: ");
    scanf("%d", &h);
    int x = 2*h+ 1;

    int *inorder = generate_order(h, 1);
    printf("Inorder array for height %d is: ", h);
    for(int i=0; i<x; i++){
        printf("%d ", *(inorder + i));
    }

    int *postorder = generate_order(h, 2);
    printf("\nPostorder array for height %d is: ", h);
    for(int i=0; i<x; i++){
        printf("%d ", *(postorder + i));
    }
}
