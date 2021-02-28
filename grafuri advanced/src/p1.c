#include "Functions.h"

int main() {
    int nodes, edges;
    ListGraph *lg = malloc(sizeof(ListGraph));
    scanf("%d %d", &nodes, &edges);
    int nodes_index[100], x[100], y[100];
    init_list_graph(lg, nodes);
    for (int i = 0; i < nodes; ++i) {
        nodes_index[i] = i;
    }
    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
        add_edge_list_graph(lg, y[i], &x[i]);
    }
    connected_components(lg, nodes_index);
    free(lg);
    
}