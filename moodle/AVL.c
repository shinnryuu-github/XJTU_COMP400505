#include <stdio.h>
#include <stdlib.h>

typedef struct _tnode{
    int data, height;
    struct _tnode *left, *right;
}tnode;

typedef tnode *AVL;

typedef struct _qnode{
    AVL data;
    struct _qnode *next;
} qnode;

typedef struct{
    qnode *head, *rear;
} _queue;

typedef _queue *queue;

int max(int a, int b){
    return (a > b) ? a : b;
}

int get_height(AVL t){
    if (!t)
        return 0;
    return max(get_height(t->left), get_height(t->right)) + 1;
}

AVL LL(AVL t){
    AVL ptr = t->left;
    t->left = ptr->right;
    ptr->right = t;
    t->height = max(get_height(t->right), get_height(t->left)) + 1;
    ptr->height = max(get_height(ptr->right), get_height(ptr->left)) + 1;
    return ptr;
}

AVL RR(AVL t){
    AVL ptr = t->right;
    t->right = ptr->left;
    ptr->left = t;
    t->height = max(get_height(t->right), get_height(t->left)) + 1;
    ptr->height = max(get_height(ptr->right), get_height(ptr->left)) + 1;
    return ptr;
}

AVL LR(AVL t){
    t->left = RR(t->left);
    t = LL(t);
    return t;
}

AVL RL(AVL t){
    t->right = LL(t->right);
    t = RR(t);
    return t;
}

AVL insert(AVL t, int data){
    if (!t) {
        AVL ptr = malloc(sizeof(tnode));
        ptr->data = data;
        ptr->left = ptr->right = NULL;
        return ptr;
    }
    else {
        if (data < t->data){
            t->left = insert(t->left, data);
            if (get_height(t->left) - get_height(t->right) >= 2){
                if (data < t->left->data){
                    t = LL(t);
                }
                else{
                    t = LR(t);
                }
            }
        }
        else if (data > t->data){
            t->right = insert(t->right, data);
            if (get_height(t->left) - get_height(t->right) <= -2){
                if (data > t->right->data){
                    t = RR(t);
                }
                else{
                    t = RL(t);
                }
            }
        }
    }
    t->height = max(get_height(t->right), get_height(t->left)) + 1;
    return t;
}

queue creat_queue(){
    queue q = (queue)malloc(sizeof(_queue));
    q->head = NULL;
    q->rear = NULL;
    return q;
}

int qis_empty(queue q){
    return (q->head) ? 0 : 1;
}

queue enqueue(queue q, AVL t){
    qnode *ptr = malloc(sizeof(qnode));
    ptr->data = t;
    ptr->next = NULL;
    if (qis_empty(q)){
        q->head = q->rear = ptr;
    }
    else{
        q->rear->next = ptr;
        q->rear = ptr;
    }
    return q;
}

AVL dequeue(queue q){
    if (qis_empty(q))
        return NULL;
    qnode *ptr = q->head;
    AVL r = ptr->data;
    q->head = ptr->next;
    free(ptr);
    return r;
}

void traversal(AVL t){
    queue q = creat_queue();
    q = enqueue(q, t);
    while (!qis_empty(q)){
        AVL ptr = dequeue(q);
        printf("%d ", ptr->data);
        if (ptr->left)
            enqueue(q, ptr->left);
        if (ptr->right)
            enqueue(q, ptr->right);
    }
}

int main(){
    AVL t = NULL;
    int d;
    for (int i = 0; i < 5; i++){
        scanf("%d", &d);
        t = insert(t, d);
    }
    traversal(t);
}