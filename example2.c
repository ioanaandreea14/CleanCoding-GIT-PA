//parcurgerge  graf cu DFS/BFS/

#include <stdlib.h>
#include <stdio.h>

typedef struct NODE {
    int data;
    struct NODE *next;
}NODE;

typedef struct Graph {
    int vertices;
    int *visited;
    struct NODE **adjacency_lists;
}GPH;

NODE *create_NODE (int v) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH *create_graph (int vertices) {

    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge (GPH *graph, int src, int dest) {
    NODE *new_NODE = create_NODE(dest);
    new_NODE->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_NODE;

    new_NODE = create_NODE(src);
    new_NODE->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_NODE;
}

int *insedg (int nr_of_vertices, int nr_of_edges, GPH *graph) {
  int src, dest;
  printf("adauga %d muchii (de la 0 la %d)\n", nr_of_edges, nr_of_vertices-1);

  for (int i = 0; i < nr_of_edges; i++) {
    scanf("%d%d", &src, &dest);
    add_edge(graph, src, dest);
  }
  return graph->visited;
}
/// bfs utils
int is_empty (NODE *queue) {
    return queue == NULL;
}

void enqueue (NODE **queue, int data) {
    NODE *new_NODE = create_NODE(data);

    if (is_empty(*queue))
      *queue = new_NODE;
    else {
       NODE *temp = *queue;
       while (temp->next) {
           temp = temp->next;
       }
       temp->next = new_NODE;
    }
}

int dequeue (NODE **queue) {
    int data = (*queue)->data;
    NODE *temp = (*queue);
    (*queue) = (*queue)->next;
    free(temp);
    return data;
}

void print_graph (GPH *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        NODE *temp = graph->adjacency_lists[i];
        while (temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void print_queue (NODE *queue) {
    while (queue != NULL) {
      printf("%d ", queue->data);
      queue = queue->next;
    }
}

void wipe_visited_list (GPH *graph, int nr_of_vertices) {
    for (int i = 0; i < nr_of_vertices; i++) {
        graph->visited[i] = 0;
    }
}

// parcurgeri
void DFS (GPH *graph, int vertex_nr) {
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);

    while (temp != NULL) {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS (GPH *graph, int start) {
    NODE *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];

        while (temp) {
          int adj_vertex = temp->data;

          if (graph->visited[adj_vertex] == 0) {
            graph->visited[adj_vertex] = 1;
            enqueue(&queue, adj_vertex);
          }
          temp = temp->next;
        }
    }
}

int main() {
    int nr_of_vertices, nr_of_edges, starting_vertex;

    printf("Cate noduri are graful?\n");
    scanf("%d", &nr_of_vertices);

    printf("Cate muchii are graful?\n");
    scanf("%d", &nr_of_edges);

    GPH *graph = create_graph(nr_of_vertices);
    insedg(nr_of_vertices, nr_of_edges, graph);

    printf("De unde plecam in DFS?\n");
    scanf("%d", &starting_vertex);

    printf("Parcurgere cu DFS:\n");
    DFS(graph, starting_vertex);

    wipe_visited_list(graph, nr_of_vertices);
    printf("\n");

    printf("De unde plecam in BFS?\n");
    scanf("%d", &starting_vertex);

    printf("parcurgere cu BFS:\n");
    BFS(graph, starting_vertex);

    return 0;
}