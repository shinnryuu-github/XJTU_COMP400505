#include <stdio.h>
#include <stdlib.h>

#define INFINITE 2147483647

int find_min(int dist[], int collected[]){
    int mindist = INFINITE;
    int minvertex;
    for (int i = 0; i < 5; i++){
        if (!collected[i] && dist[i] < mindist){
            mindist = dist[i];
            minvertex = i;
        }
    }
    if (mindist < INFINITE)
        return minvertex;
    return -1;
}

void dijkstra(int graph[][5], int dist[], int collected[], int vertex){
    for (int i = 0; i < 5; i++){
        dist[i] = INFINITE;
        collected[i] = 0;
    }
    dist[vertex] = 0;
    while (1){
        int w = find_min(dist, collected);
        if (w == -1)
            break;
        collected[w] = 1;
        for (int i = 0; i < 5; i++){
            if (graph[w][i] < INFINITE && graph[w][i] != 0 && !collected[i]){
                if (dist[w] + graph[w][i] < dist[i])
                    dist[i] = dist[w] + graph[w][i];
            }
        }
    }
}

int main(){
    int graph[5][5];
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            int d;
            scanf("%d", &d);
            if (d == -1){
                graph[i][j] = INFINITE;
            }
            else{
                graph[i][j] = d;
            }
        }
    }
    int dist[5], collected[5];
    dijkstra(graph, dist, collected, 0);
    for (int i = 0; i < 5; i++)
        printf("%d ", dist[i]);
}