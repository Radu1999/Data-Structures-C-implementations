#include <stdlib.h>
#include <stdio.h>

#include "ListGraph.h"

void init_list_graph(ListGraph *graph, int nodes) {
    /* TODO */
    graph->nodes = nodes;
    graph->neighbors = malloc(nodes * sizeof(LinkedList *));
    for(int i = 0; i < nodes; i++) {
        graph->neighbors[i] = malloc(sizeof(LinkedList));
        init_list(graph->neighbors[i]);
    }
}

void add_edge_list_graph(ListGraph *graph, int src, int *dest) {
    /* TODO */
    add_nth_node(graph->neighbors[src], graph->neighbors[src]->size, dest);
}

int has_edge_list_graph(ListGraph *graph, int src, int dest) {
    /* TODO */
    for(struct Node *it = graph->neighbors[src]->head; it != NULL; it = it->next) {
        if( *(int*)it->data == dest) {
            return 1;
        }
    }
    return 0;
}

LinkedList* get_neighbours_list_graph(ListGraph *graph, int node) {
    /* TODO */
    return graph->neighbors[node];

}

void remove_edge_list_graph(ListGraph *graph, int src, int dest) {
    /* TODO */
    struct Node *prev;
    for(struct Node *it = graph->neighbors[src]->head; it != NULL; it = it->next) {
        if( *(int*)it->data == dest) {
            if(it == graph->neighbors[src]->head) {
                graph->neighbors[src]->head = it->next;
                if(it == graph->neighbors[src]->tail) {
                    graph->neighbors[src]->tail =  NULL;
                }
                free(it);
                return;
            } else {
                prev->next = it->next;
                if(it == graph->neighbors[src]->tail) {
                    graph->neighbors[src]->tail = prev;
                }
                free(it);
            }
            return;
            
        }
    }
}

void clear_list_graph(ListGraph *graph) {
    /* TODO */
    for(int i = 0; i < graph->nodes; i++) {
        free_list(&graph->neighbors[i]);
    }
    free(graph->neighbors);
}