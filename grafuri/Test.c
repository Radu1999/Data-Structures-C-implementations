#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Queue.h"

#define MAX_NODES 10

void print_matrix_graph(MatrixGraph *g) {
    /* TODO */
    for(int i = 0; i < g->nodes; i++, printf("\n")) {
        for(int j = 0; j < g->nodes; j++) {
            printf("%d ", g->matrix[i][j]); 
        }
    }
}

void print_list_graph(ListGraph *g) {
    /* TODO */
    for(int i = 0; i < g->nodes; i++, printf("\n")) {
        printf("%d: ", i);
        for(struct Node *it = g->neighbors[i]->head; it != NULL; it = it->next) {
            printf("%d ", *(int*)it->data);
        }
    }
}

void dfs_list_graph(ListGraph *lg, int node, int *color, int *t_desc, int *t_tin) {
    /* TODO */
    static int time = 0;
    time++;
    for(struct Node *it = lg->neighbors[node]->head; it != NULL; it = it->next) {
        if(!color[*(int*)it->data]) {
            color[*(int*)it->data]  = 1;
            t_desc[*(int*)it->data] = time;
            dfs_list_graph(lg, *(int*)it->data, color, t_desc, t_tin);
            time++;
        }
    }
    color[node] = 2;
    t_tin[node] = time;


}

void dfs_matrix_graph(MatrixGraph *lg, int node, int *color, int *t_desc, int *t_tin) {
    /* TODO */
    static int time = 0;
    time++;
    color[node] = 1;
    for(int j = 0; j < lg->nodes; j++) {
        if(!color[j] && lg->matrix[node][j]) {
            t_desc[j] = time;
            dfs_matrix_graph(lg, j, color, t_desc, t_tin);
            time++;
        }
    }
    color[node] = 2;
    t_tin[node] = time;
}

void bfs_list_graph(ListGraph *lg, int node, int *color, int *parent) {
    /* TODO */
    Queue q;
    init_q(&q);
    enqueue(&q, &node);
    color[node] = 1;
    int nod;
    while(!is_empty_q(&q)) {
        nod = *(int*)front(&q);
        color[nod] = 2;
        dequeue(&q);
        for(struct Node *it = lg->neighbors[nod]->head; it != NULL; it = it->next) {
            if(!color[*(int*)it->data]) {
                parent[*(int*)it->data] = nod;
                color[*(int*)it->data] = 1;
                enqueue(&q, it->data);
            }
        }
        printf("%d ", nod);

    }


}

void bfs_matrix_graph(MatrixGraph *lg, int node, int *color, int *parent) {
    /* TODO */
     Queue q;
    init_q(&q);
    enqueue(&q, &node);
    color[node] = 1;
    int nod;
    while(!is_empty_q(&q)) {
        nod = *(int*)front(&q);
        color[nod] = 2;
        dequeue(&q);
        for(int j = 0; j < lg->nodes; j++) {
            if(lg->matrix[nod][j] && !color[j]) {
                parent[j] = nod;
                color[j] = 1;
                enqueue(&q, &j);
            }
        }
        printf("%d ", nod);

    }

}

void floyd_warshall(MatrixGraph *lg) {
    /* TODO BONUS */
    for(int k = 0;  k < lg->nodes; k++) {
        for(int i = 0; i < lg->nodes; i++) {
            for(int j = 0; j < lg->nodes; j++) {
                if(lg->matrix[i][k] && lg->matrix[k][j] && (lg->matrix[i][k] + lg->matrix[k][j] < lg->matrix[i][j] || !lg->matrix[i][j])) {
                    lg->matrix[i][j] = lg->matrix[i][k] + lg->matrix[k][j];
                }
            }
        }
    }

    for(int i = 0; i < lg->nodes; i++, printf("\n")) {
        for(int j = 0; j < lg->nodes; j++) {
            printf("%d ", lg->matrix[i][j]);
        }
    }
}

int main() {
    int nodes, edges;
    int x[MAX_NODES], y[MAX_NODES];
    int color[MAX_NODES], t_dest[MAX_NODES], t_fin[MAX_NODES];
    ListGraph *lg = malloc(sizeof(ListGraph));
    MatrixGraph *mg = malloc(sizeof(MatrixGraph));

    scanf("%d %d", &nodes, &edges);

    init_list_graph(lg, nodes);
    init_matrix_graph(mg, nodes);

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_matrix_graph(mg, x[i], y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
        add_edge_matrix_graph(mg, y[i], x[i]);
        add_edge_list_graph(lg, y[i], &x[i]);
    }
    print_list_graph(lg);
    print_matrix_graph(mg);
    memset(color, 0, nodes * sizeof(int));
    memset(t_dest, 0, nodes * sizeof(int));
    int *parent = malloc(nodes * sizeof(int));
    dfs_matrix_graph(mg, 0, color, t_dest, t_fin);
    for(int i = 0; i < nodes; i++) {
        printf("%d %d\n", t_dest[i], t_fin[i]);
    }
    floyd_warshall(mg);
    clear_list_graph(lg);
    clear_matrix_graph(mg);
    free(lg);
    free(mg);
    return 0;
}