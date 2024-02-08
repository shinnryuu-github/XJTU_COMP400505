#include <stdio.h>
#include <stdlib.h>

#define radix 10

typedef struct _node{
    int data;
    struct _node *next;
} *node;

typedef struct _lnode{
    node head, tail;
} *lnode;

int get_digit(int x, int d){
    int digit;
    for (int i = 1; i <= d; i++){
        digit = x % radix;
        x /= radix;
    }
    return digit;
}

void RadixSort(int A[], int N){
    lnode L[radix];
    node List = NULL, p, tmp;
    for (int i = 0; i < radix; i++){
        L[i] = malloc(sizeof(struct _lnode));
        L[i]->head = L[i]->tail = NULL;
    }
    for (int i = 0; i < N; i++){
        tmp = malloc(sizeof(struct _node));
        tmp->data = A[i];
        tmp->next = List;
        List = tmp;
    }
    for (int i = 1; i <= 2; i++){
        p = List;
        while (p){
            int digit = get_digit(p->data, i);
            tmp = p;
            p = p->next;
            tmp->next = NULL;
            if (i == 1){
                if (!L[digit]->head)
                    L[digit]->head = L[digit]->tail = tmp;
                else {
                    tmp->next = L[digit]->head;
                    L[digit]->head = tmp;
                }
            }
            if (i == 2){
                if (!L[digit]->head)
                    L[digit]->head = L[digit]->tail = tmp;
                else {
                    L[digit]->tail->next = tmp;
                    L[digit]->tail = tmp;
                }
            }
        }
        List = NULL;
        for (int j = radix - 1; j >= 0; j--){
            if (L[j]->head){
                L[j]->tail->next = List;
                List = L[j]->head;
                L[j]->head = L[j]->tail = NULL;
            }
        }
        tmp = List;
        while(tmp){
            printf("%d ", tmp->data);
            tmp = tmp->next;
        }
        printf("\n");
    }
    for (int i = 0; i < N; i++){
        tmp = List;
        A[i] = tmp->data;
        List = List->next;
        free(tmp);
    }
}

int main(){
    int A[12];
    for (int i = 0; i < 12; i++)
        scanf("%d", &A[i]);
    RadixSort(A, 12);
}