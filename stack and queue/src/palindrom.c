#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Dequeue.h"

int main() {
    struct Dequeue *dequeue;
    init_dequeue(&dequeue);
    printf("Introdu numarul:\n");
    char s[100];
    scanf("%s", s);
    for(int i = 0; i < strlen(s); i++) {
        push_back(dequeue, &s[i], sizeof(char));
    }
    struct Node* lft, *rght;
    while(dequeue_size(dequeue) > 1) {
        lft = pop_front(dequeue);
        rght = pop_back(dequeue);
        if(*(char*)lft->data != *(char *)rght->data) {
            printf("nu e palindrom\n");
            free(lft->data);
            free(lft);
            free(rght->data);
            free(rght);
            free_dequeue(&dequeue);
            return 0;
        }
        free(lft->data);
        free(lft);
        free(rght->data);
        free(rght);

    }
    free_dequeue(&dequeue);
    printf("e palindrom\n");
}