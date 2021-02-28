#include "Functions.h"
#define NMAX 100

unsigned int hash(void *a) {
    /*
     * Credits: http://www.cse.yorku.ca/~oz/hash.html
     */
    unsigned char *puchar_a = (unsigned char*) a;
    unsigned long hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

    return hash;
}

int get_index(void *data, size_t size_data, int* occupied, char ** rev, int hmax) {
    int index = hash(data) % hmax;
    while(occupied[index] && strcmp(data, rev[index])) {
        index++;
        if(index >= hmax) {
            index = 0;
        }
    }
    if(!occupied[index]) {
        rev[index] = malloc(size_data);
        memcpy(rev[index], data, size_data);
        occupied[index] =  1;
    }
    
    return index;
}

int main() {
    int nodes, edges;
    ListGraph *lg = malloc(sizeof(ListGraph));
    scanf("%d %d", &nodes, &edges);
    int indexes[NMAX], nodes_index[NMAX];
    char x[NMAX], y[NMAX];
    int *occupied = calloc(NMAX, sizeof(int));
    char **rev = malloc(NMAX * sizeof(char*));
    init_list_graph(lg, nodes);
    int cnt = 0;
    for (int i = 0; i < edges; ++i) {
        scanf("%s %s", x, y);
        indexes[cnt++] = get_index(x, strlen(x) + 1, occupied, rev, nodes);
        indexes[cnt++] = get_index(y, strlen(y) + 1, occupied, rev, nodes); 
        add_edge_list_graph(lg, indexes[cnt - 2], &indexes[cnt - 1]);
    }
    for(int i = 0; i < nodes; i++) {
        nodes_index[i] = i;
    }
    topo_sort(lg, nodes_index, rev);
}
