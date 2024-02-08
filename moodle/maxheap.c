#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20

typedef struct{
    int *data;
    int capacity, size;
} _maxheap;

typedef _maxheap *maxheap;

maxheap creat(int maxsize){
    maxheap r = malloc(sizeof(_maxheap));
    r->capacity = MAXSIZE;
    r->size = 0;
    r->data = malloc((r->capacity + 1) * sizeof(int));
    r->data[0] = 1000;
    return r;
}

void percdown(maxheap h, int i){
    int x = h->data[i];
    int parent = i, child;
    for (; 2 * parent <= h->size; parent = child){
        child = parent * 2;
        if (child + 1 <= h->size && h->data[child] < h->data[child + 1]){
            child++;
        }
        if (x >= h->data[child])
            break;
        else{
            h->data[parent] = h->data[child];
        }
    }
    h->data[parent] = x;
}

void build(maxheap h){
    for (int i = h->size / 2; i > 0; i--){
        percdown(h, i);
    }
}

int main(){
    int inputs[20], count = 0;
    while (1){
        int n;
        if ((scanf("%d", &n)) == 1){
            inputs[count++] = n;
        }
        else{
            break;
        }
    }
    maxheap h = creat(count);
    for (int i = 1; i <= count; i++){
        h->data[i] = inputs[i - 1];
        h->size++;
    }
    build(h);
    for (int i = 1; i <= count; i++){
        printf("%d ", h->data[i]);
    }
}