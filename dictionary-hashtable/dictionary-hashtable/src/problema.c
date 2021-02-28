#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hashtable.h"

struct InfoCar {
    char *proprietar;
    char *status;
};

struct InfoProp {
    char *mat;
    char *status;
};
void modified_put(struct Hashtable *ht, void *key, size_t key_size_bytes, void *value) {
    
    int index = ht->hash_function(key) % ht->hmax;
    for(struct Node *it = ht->buckets[index].head; it != NULL; it = it->next) {
        if(!ht->compare_function(((struct InfoProp*)((struct info*)it->data)->value)->mat, ((struct InfoProp*)value)->mat)) {
            ((struct info*)it->data)->value = value;
            return;
        }
    }
    struct info* new_entry = malloc(sizeof(struct info));
    new_entry->key = malloc(key_size_bytes);
    memcpy(new_entry->key, key, key_size_bytes);
    new_entry->value = value;
    add_nth_node(&ht->buckets[index], ht->buckets[index].size, new_entry);
    ht->size++;

}
struct Node* modified_remove(struct LinkedList *list, struct Node *it, struct Node *prev) {
    if(it == list->head) {
        list->head = list->head->next;
        prev->next = list->head;
        free(((struct InfoCar*)((struct info*)it->data)->value)->proprietar);
        free(((struct InfoCar*)((struct info*)it->data)->value)->status);
        free(((struct info*)it->data)->value);
        free(((struct info*)it->data)->key);
        free(it->data);
        free(it);
        list->size--;
        return prev;
    } else{
        prev->next = it->next;
        free(((struct InfoCar*)((struct info*)it->data)->value)->proprietar);
        free(((struct InfoCar*)((struct info*)it->data)->value)->status);
        free(((struct info*)it->data)->value);
        free(((struct info*)it->data)->key);
        free(it->data);
        free(it);
        list->size--;
        return prev;

    }    

}
struct Node* modified_remove2(struct LinkedList *list, struct Node *it, struct Node *prev) {
    if(it == list->head) {
        list->head = list->head->next;
        prev->next = list->head;
        free(((struct InfoProp*)((struct info*)it->data)->value)->mat);
        free(((struct InfoProp*)((struct info*)it->data)->value)->status);
        free(((struct info*)it->data)->value);
        free(((struct info*)it->data)->key);
        free(it->data);
        free(it);
        list->size--;
        return prev;
    } else{
        prev->next = it->next;
        free(((struct InfoProp*)((struct info*)it->data)->value)->mat);
        free(((struct InfoProp*)((struct info*)it->data)->value)->status);
        free(((struct info*)it->data)->value);
        free(((struct info*)it->data)->key);
        free(it->data);
        free(it);
        list->size--;
        return prev;

    }    

}
int main() {
    printf("Apasa 1 pentru a adauga masini.\nApasa 2 pentru a cauta o masina.\nApasa 3 pentru a afisa masinile unui proprietar.\nApasa 4 sa elimini toate masinile care au fost deja reparate.\nApasa 0 pentru help\nApasa 6 pentru a iesi\n");
    struct Hashtable *masini = malloc(sizeof(struct Hashtable));
    struct Hashtable  *proprietari = malloc(sizeof(struct Hashtable));
    init_ht(masini, 100, hash_function_string, compare_function_strings);
    init_ht(proprietari, 100, hash_function_string, compare_function_strings);
    struct InfoCar* info;
    struct InfoProp* proprietar;
    char mat[50], prop[50], status[50];
    char *nr_inm;
    int index;
    while(1) {
        int command;
        scanf("%d", &command);
        if(command == 1) {
            info = malloc(sizeof(struct InfoCar));
            proprietar = malloc(sizeof(struct InfoProp));
            printf("Nr inmatriculare:");
            scanf("%s", mat);
            proprietar->mat = malloc(strlen(mat) * sizeof(char));
            memcpy(proprietar->mat, mat, strlen(mat));
            printf("Proprietar:");
            scanf("%s", prop);
            info->proprietar = malloc(strlen(prop) * sizeof(char));
            memcpy(info->proprietar, prop, strlen(prop));
            printf("Status:");
            scanf("%s", status);
            info->status = malloc(strlen(status) * sizeof(char));
            proprietar->status = malloc(strlen(status) * sizeof(char));
            memcpy(info->status, status, strlen(status));
            memcpy(proprietar->status, status, strlen(status));
            put(masini, proprietar->mat, strlen(proprietar->mat), info);
            modified_put(proprietari, info->proprietar, strlen(info->proprietar), proprietar);
        }
        else if(command == 6) {
            break;
        }
        else if(command == 2) {
            printf("Inmatriculare:");
            scanf("%s", mat);
            info = get(masini, mat);
            if(info == NULL) {
                printf("no entry\n");
            }
            else
            printf("Masina: %s\nProprietar: %s\nStatus: %s\n", mat, info->proprietar, info->status);
        }
        else if(command == 3) {
            printf("Proprietar:");
            scanf("%s", prop);
            index = proprietari->hash_function(prop) % proprietari->hmax;
            int ok = 0;
            for(struct Node *it = proprietari->buckets[index].head; it != NULL; it = it->next) {
                printf("%s ", ((struct InfoProp*)((struct info*)it->data)->value)->mat);
                ok = 1;
            }
            if(!ok) {
                printf("no entry");
            }
            printf("\n");
        }
        else if(command == 4) {
            for(int i = 0; i < masini->hmax; i++) {
                struct Node *prev = masini->buckets[i].head;
                for(struct Node *it = masini->buckets[i].head; it != NULL; it = it -> next) {
                    if(!strcmp(((struct InfoCar*)((struct info*)it->data)->value)->status, "reparata")) {
                        it = modified_remove(&masini->buckets[i], it, prev);
                        masini->size--;
                    }
                    prev = it;
                }
            }
            for(int i = 0; i < proprietari->hmax; i++) {
                struct Node *prev = proprietari->buckets[i].head;
                for(struct Node *it = proprietari->buckets[i].head; it != NULL; it = it -> next) {
                    if(!strcmp(((struct InfoProp*)((struct info*)it->data)->value)->status, "reparata")) {
                        it = modified_remove2(&proprietari->buckets[i], it, prev);
                        proprietari->size--;
                    }
                    prev = it;
                }
            }
          

        } else if(command == 0) {
            printf("Apasa 1 pentru a adauga masini.\nApasa 2 pentru a cauta o masina.\nApasa 3 pentru a afisa masinile unui proprietar.\nApasa 4 sa elimini toate masinile care au fost deja reparate.\nApasa 0 pentru help\nApasa 6 pentru a iesi\n");
        }
         

    }
    free_ht(masini);
    free_ht(proprietari);
}