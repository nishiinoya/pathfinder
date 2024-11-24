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
    // Prevent adding more islands than allowed
    if (*island_count > graph->num_islands) {
        return -1;
    }
    // Check if the island already exists
    for (int i = 0; i < *island_count; i++) {
        if (mx_strcmp(graph->islands[i], island_name) == 0) {
            return i;
        }
    }

    // Add the island
    graph->islands[*island_count] = mx_strdup(island_name);
    int index = (*island_count)++;
    return index;
}

// Function to free graph memory
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
    int num_islands = check_first_line(lines);
    if (num_islands == -1) {
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
        if (mx_strlen(lines[i]) == 0) {
            handle_error("error: ", i + 1, graph, lines);
            return NULL;
        }
        char *line = lines[i];
        char island1[64], island2[64];
        int length;

        //Debugging

        // printf("Debug: num_islands = %d\n", num_islands);
        // printf("Debug: line_num = %d\n", line_num);
        // printf("Debug: Parsing line: %s\n", lines[i]);
        
        if (island_count > num_islands) {
            return handle_invalid_island_count(graph, lines);
        }
        // Validate line format
        if (validate_line_format(line, line_num, graph, lines) == -1)
            return NULL;

        // Parse islands and bridge length
        int dash_idx = mx_get_char_index(line, '-');
        int comma_idx = mx_get_char_index(line, ',');
        if (dash_idx == comma_idx || dash_idx > comma_idx)
        {
            handle_error("error: ", line_num, graph, lines);
            return NULL;
        }
        
        mx_strncpy(island1, line, dash_idx);
        island1[dash_idx] = '\0';
        mx_strncpy(island2, line + dash_idx + 1, comma_idx - dash_idx - 1);
        island2[comma_idx - dash_idx - 1] = '\0';
        length = mx_atoi(line + comma_idx + 1);

        // Validate islands and bridge length
        if (validate_island_names(island1, island2, line_num, graph, lines) == -1)
            return NULL;
        if (validate_bridge_length(length, line_num, graph, lines) == -1)
            return NULL;

        // Get or add islands
        int index1 = get_island_index(graph, island1, &island_count);
        int index2 = get_island_index(graph, island2, &island_count);
        if (index1 == -1 || index2 == -1) {
            handle_invalid_island_count(graph, lines);
            return NULL;
        }
        // Check if the same island is connected to itself
        if (validate_different_islands(index1, index2, line_num, graph, lines) == -1)
            return NULL;

        // Check for duplicate bridges
        if (check_duplicate_bridges(graph, index1, index2, lines) == -1)
            return NULL;

        graph->distances[index1][index2] = length;
        graph->distances[index2][index1] = length;

        // Check total bridge length
        total_bridge_length += length;
        if (check_total_bridge_length(total_bridge_length, graph, lines) == -1)
            return NULL;
        // Validate number of unique islands dynamically
        line_num++;
    }

    // Validate the number of unique islands
    if (island_count != num_islands) {
        return handle_invalid_island_count(graph, lines);
    }

    mx_del_strarr(&lines);
    return graph;
}
