#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

void init_stack(struct Stack *stack) {
    stack->list = malloc(sizeof(struct LinkedList));
    if (stack->list == NULL) {
        perror("Not enough memory to initialize the stack!");
        return;
    }

    init_list(stack->list);
}

int get_size_stack(struct Stack *stack) {
    /* TODO */
    return stack->list->size;
}

int is_empty_stack(struct Stack *stack) {
    /* TODO */
    if(stack->list->size) {
        return 0;
    }
    return 1;
}

void* peek_stack(struct Stack *stack) {
    /* TODO */
    if(stack->list->head == NULL) {
        return NULL;
    }
    return(stack->list->head->data);
}

void* pop_stack(struct Stack *stack) {
    /* TODO */
    return remove_nth_node(stack->list, 0);
}

void push_stack(struct Stack *stack, void *new_data) {
    /* TODO */
    add_nth_node(stack->list, 0, new_data);
}

void clear_stack(struct Stack *stack) {
    /* TODO */
    while(!is_empty_stack(stack)) {
        pop_stack(stack);
    }

}

void purge_stack(struct Stack *stack) {
    /* TODO */
    clear_stack(stack);
    free_list(&stack->list);
}