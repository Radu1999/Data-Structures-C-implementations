#ifndef __DEQUEUE_H__
#define __DEQUEUE_H__

struct Node {
    void *data;
    struct Node *next, *prev;
};

struct LinkedList {
    struct Node *head, *tail;
    int size;
};

struct Dequeue {
    struct LinkedList* list;
};

void init_list(struct LinkedList** list) {
    *list = malloc(sizeof(struct LinkedList));
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->size = 0;
    
}
void init_dequeue(struct Dequeue** dequeue) {
    *dequeue = malloc(sizeof(struct Dequeue));
    init_list(&((*dequeue)->list));
}

void push_front(struct Dequeue* dequeue, void *data, size_t size_data) {

    struct Node *it = malloc(sizeof(struct Node));
    it->data = malloc(size_data);
    memcpy(it->data, data, size_data);
    it->prev = NULL;

    if(dequeue->list->head == NULL) {
        dequeue->list->head = it;
        dequeue->list->tail = it;
        it->next = NULL;
    } else {
        it->next = dequeue->list->head;
        dequeue->list->head->prev = it;
        dequeue->list->head = it;
    }
    dequeue->list->size++;


}

void push_back(struct Dequeue* dequeue, void *data, size_t size_data) {
    struct Node *it = malloc(sizeof(struct Node));
    it->data = malloc(size_data);
    memcpy(it->data, data, size_data);
    it->next = NULL;

    if(dequeue->list->tail == NULL) {
        dequeue->list->head = it;
        dequeue->list->tail = it;
        it->prev = NULL;
    } else {
        dequeue->list->tail->next = it;
        it->prev = dequeue->list->tail;
        dequeue->list->tail = it;
    }
    dequeue->list->size++;
}

struct Node *pop_front(struct Dequeue* dequeue) {
    struct Node *it = dequeue->list->head;
    dequeue->list->head = it->next;
    if(dequeue->list->head != NULL) {
        dequeue->list->head->prev = NULL;
    }
    dequeue->list->size--;
    return it;
    
}

struct Node *pop_back(struct Dequeue* dequeue) {
    struct Node *it = dequeue->list->tail;
    dequeue->list->tail = it->prev;
    if(dequeue->list->tail != NULL) {
        dequeue->list->tail->next = NULL;
    }
    dequeue->list->size--;
    return it;

}

int is_empty(struct Dequeue* dequeue) {
    if(dequeue->list->size == 0) {
        return 1;
    }
    return 0;
}

int dequeue_size(struct Dequeue* dequeue) {
    return dequeue->list->size;
}

void free_dequeue(struct Dequeue** dequeue) {
    struct Node *it = (*dequeue)->list->tail;
    while(it != NULL) {
        struct Node *prev = it;
        it = it->prev;
        free(prev->data);
        free(prev);
    }
    free((*dequeue)->list);
    free((*dequeue));
}
#endif