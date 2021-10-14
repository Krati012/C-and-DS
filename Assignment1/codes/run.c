// C program to find execution time of a program height_bst.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "height.c"

int main(){

    FILE * fptr;
    fptr = fopen("./runtime.txt", "a");

    int start = 1000, end = 20000, step = 1000;

    for(int i=start; i<=end; i+=step){
        clock_t begin = clock();
        int *in2 = generate_order(i, 1);
        int *post2 = generate_order(i, 2);

        clock_t end1 = clock();
        double time_taken1 = (double)(end1 - begin)/CLOCKS_PER_SEC;

        int x = 2*i + 1;
        struct Node* root2 = constructTree(in2, post2, x);
        clock_t end2 = clock();
        double time_taken2 = (double)(end2 - begin)/CLOCKS_PER_SEC;

        fprintf(fptr, "%d", i);
        fprintf(fptr, " ");
        fprintf(fptr, "%.8f", time_taken1);
        fprintf(fptr, " ");
        fprintf(fptr, "%.8f", time_taken2);
        fprintf(fptr, "\n");

    }
    fclose(fptr);

    printf("Success\n");
    return 0;
}
