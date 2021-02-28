/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - <resume_or_paste_the_task_here>
 */

#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

int check(b_node_t *node) {
    
    if(node->left != NULL && check(node->left)) {
        return 1;
    }
    if(node->right != NULL && check(node->right)) {
        return 1;
    }

    if((node->left != NULL && *node->data < *node->left->data) || (node->right != NULL && *node->data > *node->right->data)) {
        return 1;
    }
    return 0;
}

int main(void)
{
    b_tree_t *binary_tree;
    binary_tree = b_tree_create();

    int i, N;
    scanf("%d", &N);
    int *data = malloc(N * sizeof(int));
    for (i = 0; i < N; ++i) {
        scanf("%d", &data[i]);
        b_tree_insert(binary_tree, data[i]);
    }
    if(!check(binary_tree->root)) {
        printf("True");
    } else {
        printf("False");
    }


    return 0;
}