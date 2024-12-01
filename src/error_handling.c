#include "../inc/pathfinder.h"

void check_args(int argc) {
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(1);
    }
}
void check_file(int fd, const char *filename) {
    if (fd < 0) {
        mx_printerr("error: file ");
        mx_printerr((char *)filename);
        mx_printerr(" does not exist\n");
        exit(1);
        close(fd);
    }
}
void check_read_file(int reading, int fd, const char *filename) {
    if (reading < 1) {
        mx_printerr("error: file ");
        mx_printerr((char *)filename);
        mx_printerr(" is empty\n");
        exit(1);
        close(fd);
    }
}
int check_first_line(char **lines) {
    if (!lines || !lines[0]) {
        mx_printerr("error: line 1 is not valid\n");
        mx_del_strarr(&lines);
        return -1;
    }
    if (lines[0][0] == '0' && lines[0][1] != '\0') {
        mx_printerr("error: line 1 is not valid\n");
        mx_del_strarr(&lines);
        return -1;
    }
    for (int i = 0; lines[0][i] != '\0'; i++) {
        if (!mx_isdigit(lines[0][i])) {
            mx_printerr("error: line 1 is not valid\n");
            mx_del_strarr(&lines);
            return -1;
        }
    }

    // Parse the number of islands
    int num_islands = mx_atoi(lines[0]);
    if (num_islands <= 0) {
        mx_printerr("error: line 1 is not valid\n");
        mx_del_strarr(&lines);
        return -1;
    }

    return num_islands;
}
void handle_error(char *message, int line_num, Graph *graph, char **lines) {
    mx_printerr(message);
    if (line_num > 0) {
        mx_printerr("line ");
        mx_printint(line_num);
        mx_printerr(" is not valid\n");
    } else {
        mx_printerr("\n");
    }
    if (graph)
        free_graph(graph);
    if (lines)
        mx_del_strarr(&lines);
}

int validate_island_names(char *island1, char *island2, int line_num, Graph *graph, char **lines) {
    for (int i = 0; island1[i] != '\0'; i++) {
        if (!mx_isalpha(island1[i])) {
            handle_error("error: ", line_num, graph, lines);
            return -1;
        }
    }
    for (int i = 0; island2[i] != '\0'; i++) {
        if (!mx_isalpha(island2[i])) {
            handle_error("error: ", line_num, graph, lines);
            return -1;
        }
    }
    return 0;
}
int validate_bridge_length(int length, int line_num, Graph *graph, char **lines) {
    if (length <= 0) {
        handle_error("error: ", line_num, graph, lines);
        return -1;
    }
    return 0;
}
int check_duplicate_bridges(Graph *graph, int index1, int index2, char **lines) {
    if (graph->distances[index1][index2] != INT_MAX) {
        handle_error("error: duplicate bridges", 0, graph, lines);
        return -1;
    }
    return 0;
}
int check_total_bridge_length(long long total_length, Graph *graph, char **lines) {
    if (total_length > INT_MAX) {
        handle_error("error: sum of bridges lengths is too big", 0, graph, lines);
        return -1;
    }
    return 0;
}
int validate_different_islands(int index1, int index2, int line_num, Graph *graph, char **lines) {
    if (index1 == index2) {
        handle_error("error: ", line_num, graph, lines);
        return -1;
    }
    return 0;
}
Graph *handle_invalid_island_count(Graph *graph, char **lines) {
    mx_printerr("error: invalid number of islands\n");
    free_graph(graph);
    mx_del_strarr(&lines);
    return NULL;
}
