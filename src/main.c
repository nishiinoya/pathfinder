#include "../inc/pathfinder.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(1);
    }

    const char *filename = argv[1];
    char *buf = mx_strnew(1);
    int reading;
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        mx_printerr("error: file ");
        mx_printerr((char *)filename);
        mx_printerr(" does not exist\n");
        exit(1);
    }
    reading = read(fd, buf, 1);
    if (reading < 1) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        exit(1);
        close(fd);
    }
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
