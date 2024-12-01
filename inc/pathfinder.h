#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"

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

// Error handling
void handle_error(char *message, int line_num, Graph *graph, char **lines);
void check_args(int argc);
void check_file(int fd, const char *filename);
void check_read_file(int reading, int fd, const char *filename);
int check_first_line(char **lines);
int validate_island_names(char *island1, char *island2, int line_num, Graph *graph, char **lines);
int validate_bridge_length(int length, int line_num, Graph *graph, char **lines);
int validate_different_islands(int index1, int index2, int line_num, Graph *graph, char **lines);
int check_duplicate_bridges(Graph *graph, int index1, int index2, char **lines);
int check_total_bridge_length(long long total_bridge_length, Graph *graph, char **lines);
Graph *handle_invalid_island_count(Graph *graph, char **lines);
#endif
