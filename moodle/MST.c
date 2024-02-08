#include <stdio.h>
#include <stdlib.h>

#define INFINITY 114514

typedef struct _gnode{
    int nv;
    int G[6][6];
} *graph;

graph build_graph(){
    graph g = malloc(sizeof(struct _gnode));
    g->nv = 6;
    for (int i = 0; i < g->nv; i++){
        for (int j = 0; j < g->nv; j++){
            int d;
            scanf("%d", &d);
            if (d == -1)
                g->G[i][j] = INFINITY;
            else
                g->G[i][j] = d;
        }
    }
    return g;
}

int prim(graph g){
    int total = 0, dist[6];
    for (int i = 0; i < 6; i++){
        dist[i] = g->G[0][i];
    }
    dist[0] = 0;
    for (int i = 0; i < 5; i++){
        int new, mindist = INFINITY;
        for (int j = 0; j < 6; j++){
            if (dist[j] && dist[j] < mindist){
                mindist = dist[j];
                new = j;
            }
        }
        total += mindist;
        dist[new] = 0;
        for (int k = 0; k < 6; k++){
            if (dist[k] && g->G[new][k] < INFINITY){
                if (g->G[new][k] < dist[k]){
                    dist[k] = g->G[new][k];
                }
            }
        }
    }
    return total;
}

int main(){
    graph g = build_graph();
    printf("%d", prim(g));
}