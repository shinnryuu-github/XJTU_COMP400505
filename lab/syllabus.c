#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXNUM 101

typedef struct _qnode{
    int n, head, rear, *list;
} *queue;

queue creat_queue(int n){
    queue q = malloc(sizeof(struct _qnode));
    q->n = n;
    q->head = q->rear = 0;
    q->list = malloc(sizeof(int) * (n + 1));
    return q;
}

void enqueue(queue q, int v){
    if ((q->rear + 1) % q->n == q->head){
        return;
    }
    q->rear = (q->rear + 1) % q->n;
    q->list[q->rear] = v;
}

int dequeue(queue q){
    if (q->rear == q->head){
        return -1;
    }
    q->head = (q->head + 1) % q->n;
    return q->list[q->head];
}

typedef struct _enode{
    int v1, v2;
} *edge;

typedef struct _gnode{
    int nc, ns, nv, in_degree[MAXNUM], matix[MAXNUM][MAXNUM], credit[MAXNUM];
} *graph;

graph creat_graph(int n, int c, int ns){
    graph g = malloc(sizeof(struct _gnode));
    g->ns = ns;
    g->nv = n;
    g->nc = c;
    for (int i = 1; i <= g->nv; i++){
        for (int j = 1; j <= g->nv; j++){
            g->matix[i][j] = 0;
        }
        g->in_degree[i] = 0;
        g->credit[i] = 0;
    }
    return g;
}

void insert_edge(graph g, edge e){
    g->matix[e->v1][e->v2] = 1;
    g->in_degree[e->v2]++;
}

graph build_graph(){
    int n, c, ns;
    scanf("%d %d %d", &ns, &c, &n);
    graph g = creat_graph(n, c, ns);
    printf("请输入每门课的课程号(固定3位的字母数字)、学分和直接先修课的课程号：(空格隔开)\n");
    for (int i = 0; i < n; i++){
        int c, index;
        char temp[4];
        scanf("%s %d", &temp, &c);
        index = atoi(temp + 1);
        g->credit[index] = c;
        char buffer[100];
        fgets(buffer, sizeof(buffer), stdin);
        char *ptr = strtok(buffer, " \n");
        while (ptr){
            int index2;
            index2 = atoi(ptr + 1);
            if (index2 <= n){
                edge e = malloc(sizeof(struct _enode));
                e->v2 = index;
                e->v1 = index2;
                insert_edge(g, e);
            }
            ptr = strtok(NULL, " \n");
        }
    }
    return g;
}

int top_sort(graph g, int top_order[]){
    queue q = creat_queue(g->nv + 1);
    int count = 0;
    for (int i = 1; i <= g->nv; i++){
        if (!g->in_degree[i])
            enqueue(q, i);
    }
    while (q->head != q->rear){
        int w = dequeue(q);
        top_order[count++] = w;
        for (int i = 1; i <= g->nv; i++){
            if (g->matix[w][i]){
                if (--g->in_degree[i] == 0){
                    enqueue(q, i);
                }
            }
        }
    }
    if (count != g->nv)
        return 0;
    return 1;
}

int main(){
    printf("请输入学期总数，一学期的学分上限，课程总数:\n");
    graph g = build_graph();
    int top_order[g->nv];
    int b = top_sort(g, top_order);
    if (b == 0){
        printf("拓扑排序失败");
        return 1;
    }
    printf("拓扑排序结果为：\n");
    char top[g->nv][4];
    for (int i = 0; i < g->nv - 1; i++){
        top[i][0] = 'c';
        itoa(top_order[i], top[i] + 1, 10);
        printf("%s->", top[i]);
    }
    top[g->nv - 1][0] = 'c';
    itoa(top_order[g->nv - 1], top[g->nv - 1] + 1, 10);
    printf("%s\n", top[g->nv - 1]);
    printf("请输入编排策略：使学生在各学期中的学习负担尽量均匀输入1，使课程尽可能地集中在前几个学期中输入2\n");
    int s;
    scanf("%d", &s);
    if (s == 1){
        int total_credit = 0;
        for (int i = 1; i <= g->nv; i++)
            total_credit += g->credit[i];
        float average = (float)total_credit / (float)g->ns;
        if (average > g->nc){
            printf("问题无解");
        }
        int count = 0, no = 1, pre = 0;
        while (count < g->nv && no <= g->ns){
            float delta;
            float total = 0;
            while (total < average && total <= g->nc){
                total += g->credit[top_order[count++]];
            }
            delta = abs(total - average);
            printf("第%d学期安排的课程为：", no);
            if (delta < abs(total - g->credit[top_order[count - 1]] - average)){
                for (int j = pre; j < count; j++){
                    printf("%s ", top[j]);
                }
                printf("\n");
            }
            else{
                count--;
                for (int j = pre; j < count; j++){
                    printf("%s ", top[j]);
                }
                printf("\n");
            }
            pre = count;
            no++;
        }
    }
    else if (s == 2){
        int count = 0, no = 1, pre = 0;
        while (count < g->nv && no <= g->ns){
            float total = 0;
            while (total <= g->nc){
                total += g->credit[top_order[count++]];
            }
            printf("第%d学期安排的课程为：", no);
            if (total > g->nc){
                count--;
                for (int j = pre; j < count; j++){
                    printf("%s ", top[j]);
                }
                printf("\n");
            }
            else{
                for (int j = pre; j < count; j++){
                    printf("%s ", top[j]);
                }
                printf("\n");
            }
            pre = count;
            no++;
        }
    }
    else{
        printf("输入错误");
    }
}