#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 256

typedef struct {
    char **islands;  // List of island names
    int **distances; // Adjacency matrix storing distances between islands
    int num_islands; // Total number of islands
} Graph;

Graph *parse_input(char *file_content);
void print_paths(Graph *graph);
void free_graph(Graph *graph);

// Dijkstra's algorithm
void dijkstra_for_island(Graph *graph, int src, int *dist, int **prev);

#endif
