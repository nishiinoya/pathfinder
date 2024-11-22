#include "../inc/pathfinder.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void print_route(int *route, int route_length, Graph *graph) {
    for (int i = 0; i < route_length; i++) {
        printf("%s", graph->islands[route[i]]);
        if (i < route_length - 1) {
            printf(" -> ");
        }
    }
}

void print_distance(int *route, int route_length, Graph *graph) {
    int total_distance = 0;
    for (int i = 0; i < route_length - 1; i++) {
        int distance = graph->distances[route[i]][route[i + 1]];
        total_distance += distance;
        printf("%d", distance);
        if (i < route_length - 2) {
            printf(" + ");
        }
    }
    if (route_length - 1 > 1) {
        printf(" = %d\n", total_distance);
    } else {
        printf("\n");
    }
}

void print_path_block(int src, int dest, int *route, int route_length, Graph *graph) {
    printf("========================================\n");
    printf("Path: %s -> %s\n", graph->islands[src], graph->islands[dest]);
    printf("Route: ");
    print_route(route, route_length, graph);
    printf("\nDistance: ");
    print_distance(route, route_length, graph);
    printf("========================================\n");
}

int *dequeue_path(int **queue, int *queue_lengths, int *path_length, int *front) {
    int *path = queue[*front];
    *path_length = queue_lengths[*front];
    (*front)++;
    return path;
}

void enqueue_path(int **queue, int *queue_lengths, int *path, int path_length, int *rear) {
    queue[*rear] = (int *)malloc(path_length * sizeof(int));
    for (int i = 0; i < path_length; i++) {
        queue[*rear][i] = path[i];
    }
    queue_lengths[*rear] = path_length;
    (*rear)++;
}

void find_all_paths(int **prev, int dest, int src, Graph *graph) {
    int **queue = (int **)malloc(10000 * sizeof(int *));
    int *queue_lengths = (int *)malloc(10000 * sizeof(int));
    int front = 0, rear = 0;

    int *initial_path = (int *)malloc(sizeof(int));
    initial_path[0] = dest;
    enqueue_path(queue, queue_lengths, initial_path, 1, &rear);
    free(initial_path);

    while (front < rear) {
        int path_length;
        int *path = dequeue_path(queue, queue_lengths, &path_length, &front);
        int current_node = path[path_length - 1];

        if (current_node == src) {
            // Reverse the path to print it from src to dest
            int *reversed_path = (int *)malloc(path_length * sizeof(int));
            for (int i = 0; i < path_length; i++) {
                reversed_path[i] = path[path_length - i - 1];
            }
            print_path_block(reversed_path[0], reversed_path[path_length - 1], reversed_path, path_length, graph);
            free(reversed_path);
        } else {
            for (int i = 0; prev[current_node][i] != -1; i++) {
                int predecessor = prev[current_node][i];
                // Avoid cycles by checking if predecessor is already in path
                bool in_path = false;
                for (int j = 0; j < path_length; j++) {
                    if (path[j] == predecessor) {
                        in_path = true;
                        break;
                    }
                }
                if (!in_path) {
                    int *new_path = (int *)malloc((path_length + 1) * sizeof(int));
                    for (int j = 0; j < path_length; j++) {
                        new_path[j] = path[j];
                    }
                    new_path[path_length] = predecessor;
                    enqueue_path(queue, queue_lengths, new_path, path_length + 1, &rear);
                    free(new_path);
                }
            }
        }
        free(path);
    }

    // Free queue memory
    for (int i = front; i < rear; i++) {
        free(queue[i]);
    }
    free(queue);
    free(queue_lengths);
}
// Entry point to find paths for all pairs of nodes
void print_paths(Graph *graph) {
    int num_islands = graph->num_islands;
    int *dist = (int *)malloc(num_islands * sizeof(int));
    int **prev = (int **)malloc(num_islands * sizeof(int *));
    for (int i = 0; i < num_islands; i++) {
        prev[i] = (int *)malloc(num_islands * sizeof(int));
    }

    for (int src = 0; src < num_islands; src++) {
        dijkstra_for_island(graph, src, dist, prev);

        for (int dest = src + 1; dest < graph->num_islands; dest++) {
            if (dist[dest] != INT_MAX) { // Only if there's a valid path
                find_all_paths(prev, dest, src, graph);
            }
        }
    }

    free(dist);
    for (int i = 0; i < num_islands; i++) {
        free(prev[i]);
    }
    free(prev);
}