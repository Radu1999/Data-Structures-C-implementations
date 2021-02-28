#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
void dfs_connected_comps(ListGraph *, int *, int *, LinkedList *);
void connected_components(ListGraph *, int *);
void dfs_topo_sort(ListGraph *, int *, int *, LinkedList *);
void topo_sort(ListGraph *, int *, char **);
void print_road(int, int*);
int min_path(ListGraph *, int *, int, int);
int check_bipartite(ListGraph *, int *, int *);
void get_Hamiltonian(ListGraph *, int *);