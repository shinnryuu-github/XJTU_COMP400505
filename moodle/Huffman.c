#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM 8

typedef struct _hnode{
    int weight;
    char data, code[10];
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
queue *creat_q(char data[], int weight[]);
int qlen(queue q);
huffman creat_ht(char data[], int weight[]);
void append(char *s, char c);
huffman code(huffman t, char *s, char c);
huffman find(huffman t, char c){
    if (!t){
        return NULL;
    }
    if (c == t->data){
        return t;
    }
    huffman l = find(t->left, c);
    huffman r = find(t->right, c);
    return (l) ? l : r;
}

void printh(huffman h){
    if (!h){
        return;
    }
    printf("%c %d %s\n", h->data, h->weight, h->code);
    printh(h->left);
    printh(h->right);
}

void printcode(huffman t){
    char chd[MAXNUM] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    for (int i = 0; i < MAXNUM; i++){
        huffman ps = find(t, chd[i]);
        printf("%s", ps->code);
    }
}

int main(){
    char chd[MAXNUM] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int weight[MAXNUM];
    for (int i = 0; i < MAXNUM; i++){
        scanf("%d", &weight[i]);
    }
    huffman ht = creat_ht(chd, weight);
    ht = code(ht, "", '-');
    printcode(ht);
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

queue *creat_q(char data[], int weight[]){
    queue *priotyQ = malloc(sizeof(queue));
    priotyQ->head = NULL;
    priotyQ->rear = NULL;
    for (int i = 0; i < MAXNUM; i++){
        huffman temp = malloc(sizeof(hnode));
        temp->data = data[i];
        temp->weight = weight[i];
        strcpy(temp->code, "");
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


huffman creat_ht(char data[], int weight[]){
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
        new->data = '#';
        strcpy(new->code, "");
        push(priotyQ, new);
    }
    huffman r = top(*priotyQ);
    pop(priotyQ);
    return r;
}

void append(char *s, char c){
    char *ptr = s;
    while (*ptr != '\0')
    {
        ptr++;
    }
    *(ptr++) = c;
    *ptr = '\0';
}

huffman code(huffman t, char *s, char c){
    if (!t)
        return NULL;
    strcpy(t->code, s);
    if (c != '-'){
        append(t->code, c);
    }
    t->left = code(t->left, t->code, '0');
    t->right = code(t->right, t->code, '1');
    return t;
}