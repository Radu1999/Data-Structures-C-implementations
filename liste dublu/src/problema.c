#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    void *data;
    struct Node *next, *prev;
};

struct CircularDoublyLinkedList {
    struct Node *tail;
    int count;
};
void init_list(struct CircularDoublyLinkedList *list) {

    list->tail = NULL;
    list->count = 0;
}
struct Node* make_node(void *data, int size_of_data) {
    struct Node *it = malloc(sizeof(struct Node));
    it->data = malloc(size_of_data);
    memcpy(it->data, data, size_of_data);
    it->next = NULL;
    it->prev = NULL;
    return it;
}
void add_nth_node(struct CircularDoublyLinkedList *list, int n, void *new_data, int size_of_data) {
    if(list == NULL) {
        return;
    }
    struct Node *it = make_node(new_data, size_of_data);
    struct Node *st;
    int pos = 0;
    if(list->count == 0) {
        it->next = it;
        it->prev = it;
        list -> tail = it;
    }
    else {
        if(n >= list->count) {
            n = list->count;
        }
        st = list->tail->next;
        while(pos++ < n) {
            st = st->next;
        }
        it->prev = st -> prev;
        it->next = st;
        st->prev->next = it;
        st->prev = it;
        if(n == list->count) {
            list->tail = it;
        }
       
        
    }
    list->count++;
}
void metamorph(struct CircularDoublyLinkedList *list) {

    struct Node *it = list->tail->next, *new_data, *aux;
    int x;
    while(it != list->tail) {
        x = *(int*)it->data + *(int*)it->next->data;
        new_data = make_node(&x, sizeof(int));
        aux = it;
        it = it->next;
        aux->next = new_data;
        new_data->next = it;
        it->prev = new_data;
        new_data->prev = aux;
        list->count++;
    }

}
void print_int_list(struct CircularDoublyLinkedList *list) {
    struct Node *it = list->tail->next;
    for(int i = 0; i < list->count; i++) {
        printf("%d ", *((int*)it->data));
        it = it ->next;
    }
    printf("\n");
}
void free_list(struct CircularDoublyLinkedList **pp_list) {
    struct Node *it;
    it = (*pp_list)->tail->next;
    for(int i = 0; i < (*pp_list)->count - 1; i++) {
        it = it->next;
        free(it->prev->data);
        free(it->prev);
    }
    free(it->data);
    free(it);
    free(*pp_list);
}
int main() {
    struct CircularDoublyLinkedList *list = malloc(sizeof(struct CircularDoublyLinkedList));
    init_list(list);
    int numbers[] = {1, 2, 5, 6, 7, 9}, i;
    for(i = 0; i < 6; i++) {
        add_nth_node(list, list->count, &numbers[i], sizeof(int));
    }
    metamorph(list);
    metamorph(list);
    print_int_list(list);
    free_list(&list);
}