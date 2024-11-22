#include "../inc/pathfinder.h"

int min_distance(int dist[], bool visited[], int num_islands) {
    int min = INT_MAX, min_index = -1;

    for (int i = 0; i < num_islands; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra_for_island(Graph *graph, int src, int *dist, int **prev) {
    int num_islands = graph->num_islands;
    bool visited[num_islands];

    // Initialize distances and predecessor lists
    for (int i = 0; i < num_islands; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        for (int j = 0; j < num_islands; j++) {
            prev[i][j] = -1;
        }
    }
    dist[src] = 0;

    for (int count = 0; count < num_islands - 1; count++) {
        int u = min_distance(dist, visited, num_islands);
        if (u == -1) break;

        visited[u] = true;

        for (int v = 0; v < num_islands; v++) {
            if (!visited[v] && graph->distances[u][v] != INT_MAX && dist[u] != INT_MAX) {
                int alt = dist[u] + graph->distances[u][v];

                if (alt < dist[v]) {
                    dist[v] = alt;
                    // Reset predecessors for a shorter path
                    for (int j = 0; j < num_islands; j++) {
                        prev[v][j] = -1;
                    }
                    prev[v][0] = u;
                } else if (alt == dist[v]) {
                    // Add u as another predecessor if path length is the same
                    int j = 0;
                    while (prev[v][j] != -1) j++;
                    prev[v][j] = u;
                }
            }
        }
    }
}
