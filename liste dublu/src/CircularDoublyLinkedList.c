#include <stdio.h>
#include <stdlib.h>

#include "CircularDoublyLinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct CircularDoublyLinkedList *list) {
    list->tail = NULL;
    list->count = 0;
    /* TODO */
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Daca n >= nr_noduri, atunci se intoarce nodul de pe pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe
 * lista si am trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem afla pozitia dorita fara sa
 * simulam intreaga parcurgere?
 * Daca n < 0, eroare.
 */
struct Node* get_nth_node(struct CircularDoublyLinkedList *list, int n) {
    struct Node *it;
    int pos = 0;
    if(list == NULL || list -> count == 0) {
        return NULL;
    }
    else {
        it = list->tail->next;
        while(pos++ < n) {
            it = it ->next;
        }
        return it;
    }

    return NULL;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * reprezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0).
 * Cand indexam pozitiile nu "ciclam" pe lista circulara ca la get, ci consideram nodurile in ordinea de la head la
 * ultimul (adica acel nod care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci adaugam nodul
 * nou la finalul listei. Daca n < 0, eroare.
 */
void add_nth_node(struct CircularDoublyLinkedList *list, int n, void *new_data) {
    struct Node *it, *st;
    int pos = 0;
    if(list == NULL) {
        return;
    }
    it = malloc(sizeof(struct Node));
    it->data = new_data;
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
    /* TODO */
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
struct Node* remove_nth_node(struct CircularDoublyLinkedList *list, int n) {
    /* TODO */
    struct Node* st;
    int pos = 0;
    if(list == NULL || list->count == 0) {
        return NULL;
    }
    if(n >= list->count) {
        n = list->count - 1;
    }
    st = list->tail->next;
    while(pos++ < n) {
        st = st->next;
    }
    if(st == list->tail) {
        list->tail = st->prev;
    }
    st->prev->next = st->next;
    st->next->prev = st->prev;
    list->count--;
    return st;
    return NULL;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */
int get_size(struct CircularDoublyLinkedList *list) {
    /* TODO */
    return list->count;
    return -1;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista.
 */
void free_list(struct CircularDoublyLinkedList **pp_list) {
    /* TODO */
    struct Node *it;
    int i;
    it = (*pp_list)->tail->next;
    for( i = 0; i < (*pp_list)->count; i++) {
        it = it->next;
        free(it->prev);
    }
    free(*pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza toate valorile int stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_int_list(struct CircularDoublyLinkedList *list) {
    /* TODO */
    struct Node *it = list->tail->next;
    int i;
    for( i = 0; i < list->count; i++) {
        printf("%d ", *((int*)it->data));
        it = it ->next;
    }
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza string-uri.
 * Functia afiseaza toate string-urile stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_string_list(struct CircularDoublyLinkedList *list) {
    /* TODO */
    struct Node *it = list->tail->next;
    int i;
    for (i = 0; i < list->count; i++)
    {
        printf("%s ", (char*)it->data);
        it = it->next;
    }
    

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la stanga in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_left_circular(struct Node *start) {
    /* TODO */
    struct Node* copy = start;
    printf("%d ", *((int*)start->data));
    start = start->prev;
    while(start != copy) {
        printf("%d ", *((int*)start->data));
        start = start->prev;
    }
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_right_circular(struct Node *start) {
    /* TODO */
    struct Node* copy = start;
    printf("%d ", *((int*)start->data));
    start = start->next;
    while(start != copy) {
        printf("%d ", *((int*)start->data));
        start = start->next;
    }
    printf("\n");
}
