#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node
{
    int i, j, t, b;
    struct _node *next;
}node;

typedef node *stack;

stack creat(){
    stack s = (stack)malloc(sizeof(node));
    s->next = NULL;
    return s;
}

void push(stack *s, int i, int j){
    stack temp = (stack)malloc(sizeof(node));
    temp->i = i;
    temp->j = j;
    temp->t = 0;
    temp->b = 0;
    temp->next = *s;
    (*s) = temp;
}

bool is_empty(stack s){
    if (!s->next){
        return true;
    }
    return false;
}

void pop(stack *s){
    if (is_empty(*s)){
        return;
    }
    stack temp = (*s);
    (*s)= (*s)->next;
    node r = *temp;
    free(temp);
}

void run(stack *s, int m, int n, int maze[][n + 2], int visited[][n + 2], int a, int b, int c, int d){
    push(s, a, b);
    while (!is_empty(*s) && ((*s)->i != c || (*s)->j != d)){
        int index = ++(*s)->t;
        if (index == 5){
            pop(s);
        }
        else{
            switch (index)
            {
                case 1:
                    if (!maze[(*s)->i][(*s)->j + 1] && !visited[(*s)->i][(*s)->j + 1]){
                        visited[(*s)->i][(*s)->j + 1] = 1;
                        push(s, (*s)->i, (*s)->j + 1);
                    }
                    break;           
                case 2:
                    if (!maze[(*s)->i + 1][(*s)->j] && !visited[(*s)->i + 1][(*s)->j]){
                        visited[(*s)->i + 1][(*s)->j] = 1;
                        push(s, (*s)->i + 1, (*s)->j);
                        }
                    break;
                case 3:
                    if (!maze[(*s)->i][(*s)->j - 1] && !visited[(*s)->i][(*s)->j - 1]){
                            visited[(*s)->i][(*s)->j - 1] = 1;
                            push(s, (*s)->i, (*s)->j - 1);
                        }
                    break;
                case 4:
                    if (!maze[(*s)->i - 1][(*s)->j] && !visited[(*s)->i - 1][(*s)->j]){
                            visited[(*s)->i - 1][(*s)->j] = 1;
                            push(s, (*s)->i - 1, (*s)->j);
                        }
                    break;
            }
        }
    }
}

void delete(stack *s){
    while((*s)->next){
        pop(s);
    }
    free(*s);
}

void print(stack s){
    if (is_empty(s)){
        printf("没有通路");
        return;
    }
    printf("可行的一条通路为：");
    stack t = creat();
    while (s->next){
        push(&t, s->i, s->j);
        s = s->next;
    }
    while (t->next->next){
        printf("(%d,%d)->", t->i, t->j);
        t = t->next;
    }
    printf("(%d,%d)", t->i, t->j);
    delete (&t);
}

int main(){
    int m, n, a, b, c, d;
    printf("输入迷宫大小：");
    scanf("%d %d", &m, &n);
    printf("输入入口：");
    scanf("%d %d", &a, &b);
    printf("输入出口：");
    scanf("%d %d", &c, &d);
    printf("输入迷宫(1代表障碍,0代表无障碍):");
    printf("\n");
    int maze[m+2][n+2], visited[m+2][n+2];
    for (int i = 0; i < m + 2; i++){
        if (i == 0 || i == m + 1){
            for (int j = 0; j < n + 2; j++){
                maze[i][j] = 1;
            }
        }
        else{
            maze[i][0] = maze[i][n + 1] = 1;
            for (int j = 1; j < n + 1; j++){
                scanf("%d", &maze[i][j]);
                visited[i][j] = 0;
            }
        }
    }
    stack s = creat();
    run(&s, m, n, maze, visited, a, b, c, d);
    print(s);
    delete (&s);
}