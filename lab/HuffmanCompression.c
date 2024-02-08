#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 5

typedef struct _hnode{
    int weight, code, data;
    struct _hnode *left, *right;
}hnode;

typedef hnode *huffman;

typedef struct _qnode{
    huffman data;
    struct _qnode *next;
}qnode;

typedef struct{
    qnode *head;
    qnode *rear;
} queue;

void push(queue *q, huffman data);
void pop(queue *q);
huffman top(queue q);
queue *creat_q(int data[], int weight[]);
int qlen(queue q);
huffman creat_ht(int data[], int weight[]);
void print(queue q){
    while (q.head){
        printf("%d ", q.head->data->weight);
        pop(&q);
    }
}
void printh(huffman h){
    if (!h){
        return;
    }
    printf("%d %d\n", h->data, h->weight);
    printh(h->left);
    printh(h->right);
}

int main(){
    int chd[MAXNUM];
    int weight[MAXNUM];
    for (int i = 0; i < MAXNUM; i++){
        scanf("%d %d", &weight[i], &chd[i]);
    }
    huffman ht = creat_ht(chd, weight);
    printh(ht);
    return 0;
}


void push(queue *q, huffman data){
    qnode *temp = malloc(sizeof(qnode));
    temp->data = data;
    if (!q->head){
        q->head = q->rear = temp;
        temp->next = NULL;
    }
    else{
        qnode *copy = q->head, *pre = NULL;
        if (temp->data->weight <= copy->data->weight){
            temp->next = copy;
            q->head = temp;
            return;
        }
        pre = copy;
        copy = copy->next;
        while (copy)
        {
            if (temp->data->weight <= copy->data->weight && temp->data->weight >= pre->data->weight){
                temp->next = copy;
                pre->next = temp;
                return;
            }
            pre = copy;
            copy = copy->next;
        }
        pre->next = temp;
        temp->next = NULL;
        q->rear = temp;
    }
}

void pop(queue *q){
    qnode *temp = q->head;
    if (!q->head){
        return;
    }
    if (!q->head->next){
        q->head = q->rear = NULL;
        return;
    }
    q->head = q->head->next;
    free(temp);
}

huffman top(queue q){
    return q.head->data;
}

queue *creat_q(int data[], int weight[]){
    queue *priotyQ = malloc(sizeof(queue));
    priotyQ->head = NULL;
    priotyQ->rear = NULL;
    for (int i = 0; i < MAXNUM; i++){
        huffman temp = malloc(sizeof(hnode));
        temp->data = data[i];
        temp->weight = weight[i];
        temp->left = temp->right = NULL;
        push(priotyQ, temp);
    }
    return priotyQ;
}

int qlen(queue q){
    int sum = 0;
    qnode *temp = q.head;
    while (temp){
        sum++;
        temp = temp->next;
    }
    return sum;
}


huffman creat_ht(int data[], int weight[]){
    queue *priotyQ = creat_q(data, weight);
    while (qlen(*priotyQ) > 1){
        huffman lefth, righth;
        lefth = top(*priotyQ);
        pop(priotyQ);
        righth = top(*priotyQ);
        pop(priotyQ);
        huffman new = malloc(sizeof(hnode));
        new->left = lefth;
        new->right = righth;
        new->weight = lefth->weight + righth->weight;
        new->data = -1;
        push(priotyQ, new);
    }
    huffman r = top(*priotyQ);
    pop(priotyQ);
    return r;
}