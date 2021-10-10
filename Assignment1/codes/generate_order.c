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

//Helper function for generate_inorder()
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

//Generates inorder array for any height
int *generate_inorder(int height){
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

//Generates postorder array given any height and inorder array for the same height
int *generate_postorder(int height, int *inorder){
    int *in = inorder;
    int *array = in;
    //Swapping consecutive elements in inorder array gives postorder
    for(int i=1; i < (2*height + 1); i+=2){
       swap((array+i), (array+i+1));
    }
    return array;
}

int main(){
    int h;
    printf("Enter height h: ");
    scanf("%d", &h);
    int x = 2*h+ 1;

    int *inorder = generate_inorder(h);
    printf("Inorder array for height %d is: ", h);
    for(int i=0; i<x; i++){
        printf("%d ", *(inorder + i));
    }

    int *postorder = generate_postorder(h, inorder);
    printf("\nPostorder array for height %d is: ", h);
    for(int i=0; i<x; i++){
        printf("%d ", *(postorder + i));
    }
}
