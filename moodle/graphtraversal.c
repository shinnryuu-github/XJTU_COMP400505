#include <stdio.h>
#include <stdlib.h>

char vertexes[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
int visited[9] = {0};

typedef struct _queue{
    int head, rear, list[10];
} *queue;

queue creat_queue(){
    queue q = malloc(sizeof(struct _queue));
    q->head = q->rear = 0;
    return q;
}

void enqueue(queue q, int vertex){
    q->rear = (q->rear + 1) % 10;
    q->list[q->rear] = vertex;
}

int dequeue(queue q){
    q->head = (q->head + 1) % 10;
    return q->list[q->head];
}

void DFS(int graph[][9], int i){
    printf("%c", vertexes[i]);
    visited[i] = 1;
    for (int j = 0; j < 9; j++){
        if (graph[i][j] == 1 && !visited[j]){
            DFS(graph, j);
        }
    }
}

void BFS(int graph[][9], int i){
    visited[i] = 1;
    printf("%c", vertexes[i]);
    queue q = creat_queue();
    enqueue(q, i);
    while (q->head != q->rear){
        int w = dequeue(q);
        for (int j = 0; j < 9; j++){
            if (graph[w][j] == 1 && !visited[j]){
                visited[j] = 1;
                printf("%c", vertexes[j]);
                enqueue(q, j);
            }
        }
    }
}

int main(){
    int graph[9][9];
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            scanf("%d", &graph[i][j]);
        }
    }
    DFS(graph, 0);
    for (int i = 0; i < 9; i++)
        visited[i] = 0;
    printf("\n");
    BFS(graph, 0);
}   