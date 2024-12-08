#include "../inc/pathfinder.h"

struct d_arr {
    int *data;
    int cap, size;
};
struct d_arr2d {
    struct d_arr **data;
    int cap, size;
};
struct d_arr *new_d_arr(int n) {
    struct d_arr *ans = (struct d_arr *)malloc(sizeof(struct d_arr));
    ans->data = (int *)malloc(n * sizeof(int));
    ans->cap = n;
    ans->size = 0;
    return ans;
}
void custom_free(struct d_arr *x) {
    //    printf("freeing     ");
    free(x->data);
    free(x);
    //    printf("finished");
}
struct d_arr2d *new_d_arr2d(int n) {
    struct d_arr2d *ans = (struct d_arr2d *)malloc(sizeof(struct d_arr2d));
    ans->data = (struct d_arr **)malloc(n * sizeof(struct d_arr *));
    ans->cap = n;
    ans->size = 0;
    return ans;
}
void custom_free2d(struct d_arr2d *x) {
    //    printf("freeing 2d   ");
    for (int i = 0; i < x->size; i++) {
        custom_free(x->data[i]);
    }
    free(x->data);
    free(x);
    //    printf("finished\n");
}

void add_el(struct d_arr *a, int x) {
    //    printf("add    ");
    if (a->size >= a->cap) {
        a->cap *= 2;
        int *new_data = (int *)malloc(a->cap * sizeof(int));
        for (int i = 0; i < a->size; i++) {
            new_data[i] = a->data[i];
        }
        free(a->data);
        a->data = new_data;
    }
    a->data[a->size++] = x;
    //    printf("finished\n");
}

void add_el2d(struct d_arr2d *a, struct d_arr *x) {
    //    printf("add 2d ");
    //    if(a->size==1) {
    //        printf("-----adding second-----\n");
    //        printf("x: %d / %d\n", x->size, x->cap);
    //        for(int i=0;i<x->size;i++){
    //            printf("%d ", x->data[i]);
    //        }
    //        printf("\n");
    //    }
    if (a->size >= a->cap) {
        a->cap *= 2;
        struct d_arr **new_data = (struct d_arr **)malloc(a->cap * sizeof(struct d_arr *));
        for (int i = 0; i < a->size; i++) {
            new_data[i] = a->data[i];
        }
        free(a->data);
        a->data = new_data;
    }
    a->data[a->size++] = x;
    //    if(a->size==2) {
    //        for(int i=0;i<a->data[1]->size;i++){
    //            printf("%d ", a->data[1]->data[i]);
    //        }
    //        printf("\n");
    //
    //        printf("-----finished-----\n");
    //    }
}

void bubble_sort_paths(struct d_arr2d *a) {
    //    printf("inside bubble sort\n");
    //    printf("%d / %d\n",a->size, a->cap);
    //    printf("sub0: %d / %d\n", a->data[0]->size, a->data[0]->cap);
    //    for(int i=0;i<a->data[0]->size;i++){printf("%d ", a->data[0]->data[i]);}
    //    if(a->size>=2) {
    //        printf("\nsub1: %d / %d\n", a->data[1]->size, a->data[1]->cap);
    //        for(int i=0;i<a->data[1]->size;i++){printf("%d ", a->data[1]->data[i]);}
    //        printf("\n");
    //    }
    if (a->size <= 1)
        return;
    for (int k = a->size; k > 1; k--) {
        for (int i = 0; i < k - 1; i++) {
            bool correct_order = 1;
            int *x = a->data[i]->data;
            int x_len = a->data[i]->size;
            int *y = a->data[i + 1]->data;
            int y_len = a->data[i + 1]->size;
            for (int j = 0; j < x_len && j < y_len; j++) {
                if (x[j] > y[j]) {
                    correct_order = 0;
                    break;
                } else if (x[j] < y[j]) {
                    break;
                }
            }
            // swap
            if (!correct_order) {
                struct d_arr *r = a->data[i];
                a->data[i] = a->data[i + 1];
                a->data[i + 1] = r;
            }
        }
    }
    //    printf("calling rec\n");
}

void print_route(int *route, int route_length, Graph *graph) {
    for (int i = 0; i < route_length; i++) {
        mx_printstr(graph->islands[route[i]]);
        if (i < route_length - 1) {
            mx_printstr(" -> ");
        }
    }
}

void print_distance(int *route, int route_length, Graph *graph) {
    int total_distance = 0;
    for (int i = 0; i < route_length - 1; i++) {
        int distance = graph->distances[route[i]][route[i + 1]];
        total_distance += distance;
        mx_printint(distance);
        if (i < route_length - 2) {
            mx_printstr(" + ");
        }
    }
    if (route_length - 1 > 1) {
        mx_printstr(" = ");
        mx_printint(total_distance);
        mx_printchar('\n');
    } else {
        mx_printchar('\n');
    }
}
void print_path_block(int src, int dest, int *route, int route_length, Graph *graph) {
    mx_printstr("========================================\n");
    mx_printstr("Path: ");
    mx_printstr(graph->islands[src]);
    mx_printstr(" -> ");
    mx_printstr(graph->islands[dest]);
    mx_printstr("\nRoute: ");
    print_route(route, route_length, graph);
    mx_printchar('\n');
    mx_printstr("Distance: ");
    print_distance(route, route_length, graph);
    mx_printstr("========================================\n");
}

static struct d_arr *dequeue_path(struct d_arr2d *queue, int *front) {
    //    printf("start\n");
    struct d_arr *path = queue->data[*front];
    (*front)++;
    //    printf("end\n");
    return path;
}

void find_all_paths(int **prev, int dest, int src, Graph *graph) {
    struct d_arr2d *queue = new_d_arr2d(4);

    int front = 0, rear = 0;
    {
        struct d_arr *initial_path = new_d_arr(4);
        add_el(initial_path, dest);
        add_el2d(queue, initial_path);
        rear++;
    }
    // storing all valid paths
    struct d_arr2d *paths_ok = new_d_arr2d(4);
    while (front < rear) {
        //        printf("check1\n");
        struct d_arr *path = dequeue_path(queue, &front);
        //        printf("check1.5\n");
        int current_node = path->data[path->size - 1];

        //        printf("check2\n");
        if (current_node == src) {
            struct d_arr *reversed_path = new_d_arr(path->size);
            for (int i = 0; i < path->size; i++)
                add_el(reversed_path, path->data[path->size - i - 1]);
            // instead I want to save it to sort
            //            printf("reversed started\n");
            add_el2d(paths_ok, reversed_path);
            //            printf("reversed ended\n");
        } else {

            for (int i = 0; prev[current_node][i] != -1; i++) {
                int predecessor = prev[current_node][i];
                bool in_path = false;
                for (int j = 0; j < path->size; j++) {
                    if (path->data[j] == predecessor) {
                        in_path = true;
                        break;
                    }
                }
                if (!in_path) {
                    struct d_arr *new_path = new_d_arr(path->size + 1);
                    //                    int *new_path = (int *)malloc((path_length + 1) * sizeof(int));

                    for (int j = 0; j < path->size; j++) {
                        add_el(new_path, path->data[j]);
                    }

                    add_el(new_path, predecessor);
                    add_el2d(queue, new_path);
                    rear++;
                }
            }
        }
        //        printf("check3\n");
    }
    // sort the paths
    bubble_sort_paths(paths_ok);

    // supposed to output here
    for (int i = 0; i < paths_ok->size; i++) {
        print_path_block(paths_ok->data[i]->data[0], paths_ok->data[i]->data[paths_ok->data[i]->size - 1],
                         // paths_ok_sizes[i] - 1],
                         paths_ok->data[i]->data, paths_ok->data[i]->size, graph);
    }
    custom_free2d(paths_ok);
    custom_free2d(queue);
}

// Entry point to find paths for all pairs of nodes
void print_paths(Graph *graph) {
    int num_islands = graph->num_islands;
    int *dist = (int *)malloc(num_islands * sizeof(int));

    // prev[i] - array of best predecessors for a vertex
    int **prev = (int **)malloc(num_islands * sizeof(int *));
    for (int i = 0; i < num_islands; i++) {
        prev[i] = (int *)malloc(num_islands * sizeof(int));
    }

    for (int src = 0; src < num_islands; src++) {
        // to check which nodes can be reached from <src>
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
