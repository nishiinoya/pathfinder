#include "../inc/pathfinder.h"

void print_graph(Graph *graph) {
    mx_printstr("Number of islands: ");
    mx_printint(graph->num_islands);
    mx_printstr("\nIslands and their connections:\n");

    for (int i = 0; i < graph->num_islands; i++) {
        mx_printstr("Island: ");
        mx_printstr(graph->islands[i]);
        mx_printstr("\n");
        for (int j = 0; j < graph->num_islands; j++) {
            if (graph->distances[i][j] != INT_MAX && i != j) {
                mx_printstr("  -> ");
                mx_printstr(graph->islands[j]);
                mx_printstr(": ");
                mx_printint(graph->distances[i][j]);
                mx_printstr("\n");
            }
        }
    }
}

// Helper function to find the index of an island, or add it if not present
int get_island_index(Graph *graph, const char *island_name, int *island_count) {
    for (int i = 0; i < *island_count; i++) {
        if (mx_strcmp(graph->islands[i], island_name) == 0) {
            return i;
        }
    }
    // If the island is not found, add it
    graph->islands[*island_count] = mx_strdup(island_name);
    return (*island_count)++;
}

// Function to free graph memory in case of an error
void free_graph(Graph *graph) {
    if (graph) {
        for (int i = 0; i < graph->num_islands; i++) {
            free(graph->islands[i]);
            free(graph->distances[i]);
        }
        free(graph->islands);
        free(graph->distances);
        free(graph);
    }
}
Graph *parse_input(char *file_content) {
    char **lines = mx_strsplit(file_content, '\n');
    if (!lines || !lines[0]) {
        mx_printerr("error: line 1 is not valid\n");
        mx_del_strarr(&lines);
        return NULL;
    }

    for (int i = 0; lines[0][i] != '\0'; i++) {
        if (!mx_isdigit(lines[0][i]) && lines[0][i] != 0) {
            mx_printerr("error: line 1 is not valid\n");
            mx_del_strarr(&lines);
            return NULL;
        }
    }

    // Parse the number of islands
    int num_islands = mx_atoi(lines[0]);
    if (num_islands <= 1) {
        mx_printerr("error: line 1 is not valid\n");
        mx_del_strarr(&lines);
        return NULL;
    }

    // Create and initialize the graph
    Graph *graph = malloc(sizeof(Graph));
    graph->num_islands = num_islands;
    graph->islands = malloc(sizeof(char *) * num_islands);
    graph->distances = malloc(sizeof(int *) * num_islands);

    for (int i = 0; i < num_islands; i++) {
        graph->distances[i] = malloc(sizeof(int) * num_islands);
        for (int j = 0; j < num_islands; j++) {
            graph->distances[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    int island_count = 0;
    long long total_bridge_length = 0;
    int line_num = 2;

    // Parse each bridge definition line
    for (int i = 1; lines[i]; i++) {
        char *line = lines[i];
        char island1[64], island2[64];
        int length;

        // Parse the line
        int dash_idx = mx_get_char_index(line, '-');
        int comma_idx = mx_get_char_index(line, ',');
        if (dash_idx < 0 || comma_idx < 0 || dash_idx >= comma_idx) {
            mx_printerr("error: line ");
            mx_printint(line_num);
            mx_printerr(" is not valid\n");
            free_graph(graph);
            mx_del_strarr(&lines);
            return NULL;
        }

        mx_strncpy(island1, line, dash_idx);
        island1[dash_idx] = '\0';
        mx_strncpy(island2, line + dash_idx + 1, comma_idx - dash_idx - 1);
        island2[comma_idx - dash_idx - 1] = '\0';
        length = mx_atoi(line + comma_idx + 1);

        if (length <= 0) {
            mx_printerr("error: line ");
            mx_printint(line_num);
            mx_printerr(" is not valid\n");
            free_graph(graph);
            mx_del_strarr(&lines);
            return NULL;
        }

        // Get or add islands
        int index1 = get_island_index(graph, island1, &island_count);
        int index2 = get_island_index(graph, island2, &island_count);

        if (index1 == index2) {
            mx_printerr("error: line ");
            mx_printint(line_num);
            mx_printerr(" is not valid (same island)\n");
            free_graph(graph);
            mx_del_strarr(&lines);
            return NULL;
        }
        if (graph->distances[index1][index2] != INT_MAX) {
            mx_printerr("error: duplicate bridges\n");
            free_graph(graph);
            mx_del_strarr(&lines);
            return NULL;
        }

        graph->distances[index1][index2] = length;
        graph->distances[index2][index1] = length;

        total_bridge_length += length;
        if (total_bridge_length > INT_MAX) {
            mx_printerr("error: sum of bridges lengths is too big\n");
            free_graph(graph);
            mx_del_strarr(&lines);
            return NULL;
        }

        line_num++;
    }

    // Validate the number of unique islands
    if (island_count != num_islands) {
        mx_printerr("error: invalid number of islands\n");
        free_graph(graph);
        mx_del_strarr(&lines);
        return NULL;
    }

    mx_del_strarr(&lines);
    return graph;
}
