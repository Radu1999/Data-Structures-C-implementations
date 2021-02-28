#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"

#define MAX_NODES 100
#define MX_road 999999


void dfs_connected_comps(ListGraph *lg, int *node, int *visited, LinkedList *component) {
    /* TODO */
    for(struct Node *it = lg->neighbors[*node]->head; it != NULL; it = it->next) {
        if(!visited[*(int*)it->data]) {
            visited[*(int*)it->data] = 1;
            add_nth_node(component, component->size, it->data);
            dfs_connected_comps(lg, (int *)it->data, visited, component);
            
        }
    }
}

void connected_components(ListGraph *lg, int *nodes_index) {
    /* TODO */
    LinkedList *component = malloc(lg->nodes * sizeof(LinkedList));
    init_list(component);
    int conex = 0;
    int *visited= calloc(lg->nodes, sizeof(int));
    for(int i = 0; i < lg->nodes; i++) {
        if(!visited[nodes_index[i]]) {
            visited[nodes_index[i]] = 1;
            add_nth_node(&component[conex], component[i].size, &nodes_index[i]);
            dfs_connected_comps(lg, &nodes_index[i], visited, &component[conex++]);
        }
    }
    printf("%d\n", conex);
    for(int i = 0; i < conex; i++) {
        while(component[i].size) {
            struct Node *it = remove_nth_node(&component[i], 0);
            printf("%d ", *(int*)it->data);
            free(it);
        }
        printf("\n");
    }
    free(component);
}

void dfs_topo_sort(ListGraph *lg, int *node, int *visited, LinkedList *result) {
    /* TODO */
    visited[*node]  = 1;
    for(struct Node *it = lg->neighbors[*node]->head; it != NULL; it = it->next) {
        if(!visited[*(int*)it->data]) {
            visited[*(int*)it->data]  = 1;
            dfs_topo_sort(lg, it->data, visited, result);
        }
    }
    add_nth_node(result, result->size, node);

    


}

void topo_sort(ListGraph *lg, int *nodes_index, char ** rev) {
    /* TODO */
    LinkedList *result = malloc(sizeof(LinkedList));
    int* visited = calloc(lg->nodes, sizeof(int));
    struct Node *it;
    for(int i = 0; i < lg->nodes; i++) {
        if(!visited[nodes_index[i]]) {
            dfs_topo_sort(lg, &nodes_index[i], visited, result);
        }
    }
    printf("Sortate topologic nordurile sunt:\n");
    while(result->size > 0) {
        it = remove_nth_node(result, result->size);
        printf("%s\n", rev[*(int*)it->data]);
        free(it);
    }
    free(result);
}

void print_road(int n, int*p) {

    if(p[n] == -1) {
        printf("%d ", n);
    } else {
        print_road(p[n], p);
        printf("%d ", n);
    }
    
}

void min_path(ListGraph *lg, int *nodes_index, int src, int dest) {
    /* TODO */
    int *visited = calloc(lg->nodes, sizeof(int));
    int *d = calloc(lg->nodes, sizeof(int));
    int *p = calloc(lg->nodes, sizeof(int));
    Queue queue;
    init_q(&queue);
    enqueue(&queue, &nodes_index[src]);
    visited[nodes_index[src]] = 1;
    p[nodes_index[src]] = -1;
    while(!is_empty_q(&queue)) {
        int nd = *(int*)front(&queue);
        dequeue(&queue);
        for(struct Node *it = lg->neighbors[nd]->head; it != NULL; it = it->next) {
            if(!visited[*(int*)it->data]) {
                p[*(int*)it->data] = nd;
                d[*(int*)it->data] = d[nd] + 1;
                visited[*(int*)it->data] = 1;
                enqueue(&queue, (int*)it->data);
            }
            
        }
    }
    free(d);
    free(visited);
    print_road(nodes_index[dest], p);
    printf("\n");

}

void check_bipartite(ListGraph *lg, int *nodes_index, int *color) {
    /* TODO */
    Queue q;
    init_q(&q);
    LinkedList a, b;
    init_list(&a);
    init_list(&b);
    enqueue(&q, &nodes_index[0]);
    for(int i = 0; i < lg->nodes; i++) {
        color[i] = 0;
    }
    color[nodes_index[0]] = 1;
    add_nth_node(&a, a.size, &nodes_index[0]);
    while(!is_empty_q(&q)) {
        int nd = *(int*)front(&q);
        dequeue(&q);
        for(struct Node *it = lg->neighbors[nd]->head; it != NULL; it = it->next) {
            if(!color[*(int*)it->data]) {
                if(color[nd] == 1) {
                   color[*(int*)it->data] = 2;
                   add_nth_node(&b, b.size, (int*)it->data);

                } else {
                   color[*(int*)it->data] = 1;
                   add_nth_node(&a, a.size, (int*)it->data);
                }
                enqueue(&q, (int*)it->data);
            } else if(color[*(int*)it->data] == color[nd]){
                printf("Not bipartit");
                return;
            }
        }
    }
    while(a.size) {
        struct Node *it = remove_nth_node(&a, 0);
        printf("%d ", *(int*)it->data);
        free(it);
    }
    printf("\n");
    while(b.size) {
        struct Node *it = remove_nth_node(&b, 0);
        printf("%d ", *(int*)it->data);
        free(it);
    }
    

    
}

int not_in(LinkedList *list, int n) {
    for(struct Node *it = list->head; it != NULL; it = it->next) {
        if(*(int*)it->data == n) {
            return 0;
        }
    }
    return 1;
}

void build(LinkedList *lant, int nr, ListGraph *lg, int *nodes_index) {
    if(nr == lg->nodes) {
        int start = *(int*)lant->head->data;
        int end = *(int*)lant->tail->data;
        for(struct Node *it = lg->neighbors[end]->head; it != NULL; it = it->next) {
            if(*(int*)it->data == start) {
                for(struct Node *p = lant->head; p != NULL; p = p->next) {
                    printf("%d ", *(int*)p->data);
                }
                printf("%d\n", *(int*)lant->head->data);
                return;
            }
        }
    } else {
            int end = *(int*)lant->tail->data;
            for(struct Node *pz = lg->neighbors[end]->head; pz != NULL; pz = pz->next) {
                if(not_in(lant, *(int*)pz->data)) {
                    add_nth_node(lant, lant->size, pz->data);
                    build(lant, nr + 1, lg, nodes_index);
                    struct Node *rm = remove_nth_node(lant, lant->size);
                }
            }
    }
}


void get_Hamiltonian(ListGraph *lg, int * nodes_index) {
    int count;
    LinkedList lant;
    init_list(&lant);
    int *visited = calloc(lg->nodes, sizeof(int));
    add_nth_node(&lant, 0, &nodes_index[0]);
    build(&lant, 1, lg, nodes_index);
     
}

