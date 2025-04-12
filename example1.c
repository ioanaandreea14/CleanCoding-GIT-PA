//Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf
#include <stdlib.h>
#include <stdio.h>

typedef struct NODE {
    struct NODE *next;
    int data;
}NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct g {
    int v;
    int *vis;
    struct NODE **alst;
}GPH;

typedef struct s {
    int t;
    int scap;
    int *arr;
}STK;

NODE *create_node (int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge (GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;
    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g (int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE *) * v);
    g->vis = malloc(sizeof(int) * v);

    for (int i=0; i<v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STK *create_s (int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push (int pshd, STK *s) {
    s->t = s->t+1;
    s->arr[s->t] = pshd;
}

void DFS (GPH *g, STK *s, int v_nr) {
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);

    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g,s,con_ver);
        aux = aux->next;
    }
}

void insert_edges (GPH *g, int edg_nr, int nrv) {
    int src, dest;
    printf("adauga %d muchii (de la 0 la %d)\n", edg_nr, nrv - 1);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe (GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

void canbe (GPH *g, int nrv, STK *s1, STK *s2, int *ans) {
    for (int i = 0; i < nrv; i++) {
        for (int j = i + 1; j < nrv; j++) {
            s1->t = -1;
            DFS(g, s1, i);
            wipe(g, nrv);

            s2->t = -1;
            DFS(g, s2, j);
            wipe(g, nrv);

            for (int a = 0; a <= s1->t && *ans == 0; a++) {
                for (int b = 0; b <= s2->t && *ans == 0; b++) {
                    if ((s1->arr[a] == j) && (s2->arr[b] == i)) {
                        *ans = 1;
                    }
                }
            }
        }
    }
}

int main() {

    int nrv, edg_nr, ans=0;

    printf("Cate noduri are graful?\n");
    scanf("%d", &nrv);

    printf("Cate muchii are graful?\n");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    canbe(g, nrv, s1, s2, &ans);
    printf("\n");
    if (ans)
        printf("Exista drum direct intre doua restaurante.");
    else
        printf("Nu exista drum direct doua restaurante.");

    return 0;
}