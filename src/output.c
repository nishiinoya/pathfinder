#include "../inc/pathfinder.h"

void sort(int** a, int* l, int n){
    if(n<=1)return;
    for(int i=0;i<n-1;i++){
        bool correct_order = 1;
        for(int j=0;j<l[i]||j<l[i+1];j++){
            if(a[i][j]>a[i+1][j]) {
                correct_order = 0;
                break;
            }else if(a[i][j]<a[i+1][j]){
                break;
            }
        }
        //swap
        if(!correct_order){
            int* a_ = a[i];
            a[i] = a[i+1];
            a[i+1] = a_;
            int l_ = l[i];
            l[i] = l[i+1];
            l[i+1] = l_;
        }
    }
    sort(a,l,n-1);
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
static void resize_queue(int ***queue, int **queue_lengths, int *capacity, int rear) {
    if (rear >= *capacity) {
        *capacity *= 10;
        *queue = (int **)realloc(*queue, (*capacity) * sizeof(int *));
        *queue_lengths = (int *)realloc(*queue_lengths, (*capacity) * sizeof(int));
        if (*queue == NULL || *queue_lengths == NULL) {
            exit(1);
        }
    }
}
static void resize_valid_paths(int ***paths, int **lengths, int *capacity, int count) {
    if (count >= *capacity) {
        *capacity *= 10;
        *paths = (int **)realloc(*paths, (*capacity) * sizeof(int *));
        *lengths = (int *)realloc(*lengths, (*capacity) * sizeof(int));
        if (*paths == NULL || *lengths == NULL) {
            exit(1);
        }
    }
}
static int *dequeue_path(int **queue, int *queue_lengths, int *path_length, int *front) {
    int *path = queue[*front];
    *path_length = queue_lengths[*front];
    (*front)++;
    return path;
}

static void enqueue_path(int **queue, int *queue_lengths, int *path, int path_length, int *rear, int *capacity) {
    resize_queue(&queue, &queue_lengths, capacity, *rear);
    queue[*rear] = (int *)malloc(path_length * sizeof(int));
    for (int i = 0; i < path_length; i++) {
        queue[*rear][i] = path[i];
    }
    queue_lengths[*rear] = path_length;
    (*rear)++;
}

void find_all_paths(int **prev, int dest, int src, Graph *graph) {
    int capacity = 10000;
    int **queue = (int **)malloc(capacity * sizeof(int *));
    int *queue_lengths = (int *)malloc(capacity * sizeof(int));
    int front = 0, rear = 0;

    int *initial_path = (int *)malloc(sizeof(int));
    initial_path[0] = dest;
    enqueue_path(queue, queue_lengths, initial_path, 1, &rear, &capacity);
    free(initial_path);

    // storing all valid paths
    int all_valid_paths_capacity = 10000;
    int **all_valid_paths = (int **)malloc(all_valid_paths_capacity * sizeof(int *));
    int *all_valid_paths_lengths = (int *)malloc(all_valid_paths_capacity * sizeof(int));
    int all_valid_paths_cnt = 0;

    while (front < rear) {
        int path_length;
        int *path = dequeue_path(queue, queue_lengths, &path_length, &front);
        int current_node = path[path_length - 1];

        if (current_node == src) {
            int *reversed_path = (int *)malloc(path_length * sizeof(int));
            for (int i = 0; i < path_length; i++) {
                reversed_path[i] = path[path_length - i - 1];
            }

            // instead I want to save it to sort
            {
                resize_valid_paths(&all_valid_paths, &all_valid_paths_lengths, &all_valid_paths_capacity, all_valid_paths_cnt);
                all_valid_paths[all_valid_paths_cnt] = reversed_path;
                all_valid_paths_lengths[all_valid_paths_cnt] = path_length;
                all_valid_paths_cnt++;
//                print_path_block(reversed_path[0], reversed_path[path_length - 1], reversed_path, path_length, graph);
            }

//            free(reversed_path);
        } else {
            for (int i = 0; prev[current_node][i] != -1; i++) {
                int predecessor = prev[current_node][i];
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
                    enqueue_path(queue, queue_lengths, new_path, path_length + 1, &rear, &capacity);
                    free(new_path);
                }
            }
        }
        free(path);
    }

    // sort the paths
    {
        sort(all_valid_paths,all_valid_paths_lengths,all_valid_paths_cnt);
    }
    // supposed to output here
    {
        for(int i=0;i<all_valid_paths_cnt;i++){
            print_path_block(all_valid_paths[i][0], all_valid_paths[i][all_valid_paths_lengths[i] - 1],
                             all_valid_paths[i], all_valid_paths_lengths[i], graph);
        }
    }

    for(int i=0;i<all_valid_paths_cnt;i++){
        free(all_valid_paths[i]);
    }
    free(all_valid_paths);
    free(all_valid_paths_lengths);

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
