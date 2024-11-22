#include "../inc/pathfinder.h"

int main(int argc, char *argv[]) {
    check_args(argc);
    const char *filename = argv[1];
    char *buf = mx_strnew(1);
    int fd = open(filename, O_RDONLY);
    check_file(fd, filename);
    int reading = read(fd, buf, 1);
    check_read_file(reading, fd, filename);
    mx_strdel(&buf);
    char *file_content = mx_file_to_str(filename);
    Graph *graph = parse_input(file_content);
    if (!graph) {
        free(file_content);
        close(fd);
        exit(1);
    }
    print_paths(graph);
    free_graph(graph);
    free(file_content);
    close(fd);

    return 0;
}
