#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste simplu inlantuite, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct LinkedList *list) {
    /* TODO */
    list->head = NULL;
    list->count = 0;

}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * reprezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca n < 0, eroare.
 */
void add_nth_node(struct LinkedList *list, int n, void *new_data) {
    /* TODO */
    if(n < 0) {
        printf("n is negative");
        return ;
    }
    struct Node *nod = malloc(sizeof(struct Node));
    nod->data = new_data;
    int position;
    if(!list->count) {
        nod->next = NULL;
        list->head = nod;
    }
    else {

        if(n >= list->count) {
            n = list->count;
        }
        if(n) {
            struct Node *prev;
            position = 0;
            prev = list->head;
            while(position++ < n - 1) {
                prev = prev->next;
            }
            nod->next = prev->next;
            prev->next = nod;

        }
        else {
            nod->next = list->head;
            list->head = nod;
        }
       
    }
    list->count++;
    
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1,
 * se elimina nodul de la finalul listei. Daca n < 0, eroare.
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
struct Node* remove_nth_node(struct LinkedList *list, int n) {
    /* TODO */
    struct Node *it, *prev;
    struct Node *ans = malloc(sizeof(struct Node));
    if(n < 0 || list->count == 0) {
        return NULL;
    }
    if(list -> count == 1) {
        ans->next = list->head->next;
        ans->data = list->head->data;
        list -> head = NULL;
    }
    else {

        if(n >= list->count) {
            n = list->count - 1;
        }
        if(n) {
            int position = 0;
            it = list -> head;
            while(position++ < n) {
                prev = it;
                it = it->next;
            }
            ans->next = prev->next->next;
            ans->data = prev->next->data;
            prev -> next = it->next;
        }
        else {
            ans->next = list->head->next;
            ans->data = list->head->data;
            list->head = list ->head -> next; 
        }
    }
    list -> count--;
    return ans;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */
int get_size(struct LinkedList *list) {
    /* TODO */
    return list->count;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista si actualizeaza la NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void free_list(struct LinkedList **pp_list) {

    /* TODO */
    struct Node *it;
    struct Node *prev;
    it = (*pp_list)->head;
    while(it != NULL) {
        prev = it;
        it = it->next;
        free(prev);
    }
    free(*pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza toate valorile int stocate in nodurile din lista inlantuita separate printr-un spatiu.
 */
void print_int_linkedlist(struct LinkedList *list) {
    /* TODO */
    struct Node *it;
    it = list->head;
    while(it != NULL) {
        printf("%d ", *((int*)it->data));
        it = it->next;
    }
    printf("\n");
}
void print_char_linkedlist(struct LinkedList *list) {
    struct Node *it;
    for(it = list -> head; it != NULL; it = it->next) {
        printf("%c", *((char *)it->data));
    }
    printf("\n");
}
/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza string-uri.
 * Functia afiseaza toate string-urile stocate in nodurile din lista inlantuita, separate printr-un spatiu.
 */
void print_string_linkedlist(struct LinkedList *list) {
    /* TODO */
    struct Node *it;
    it = list ->head;
    while(it != NULL) {
        printf("%s ", ((char*)it->data));
        it = it->next;
    }
    printf("\n");
}
struct Node* find_k_back(struct Node* it, int k) {
    static int count = 0;
    struct Node *ans;
    if(it != NULL) {
        ans = it;
        ans = find_k_back(it->next, k);
        if(count++ == k) {
            ans = it;
        }
    }
    return ans;

    
}
void delete_k_back(struct LinkedList *list, int k) {
    struct Node *it = find_k_back(list->head, k);
    if(it != NULL) {
        struct Node *del = it->next;
        it->next= del->next;
        free(del);
    }
    else {
        printf("k is way too large");
    }
}
int main() {
    struct LinkedList *list1, *list2;
    int i;
    struct Node *currNode;
    list1 = malloc(sizeof(struct LinkedList));
    list2 = malloc(sizeof(struct LinkedList));
    init_list(list1);
    init_list(list2);
    char *s = "mama";
    int n = strlen(s);
    for(i = 0; i < n; i++) {
        add_nth_node(list1, 0, &s[i]);
        add_nth_node(list2, n + 1, &s[i]);
    }
    print_char_linkedlist(list1);
    print_char_linkedlist(list2);
    
}
