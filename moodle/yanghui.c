#include <stdio.h>
#include <stdlib.h>

typedef struct _queue
{
    int head, rear;
    int nums[100];
}queue;

int enqueue(queue *q, int n){
    if ((q->rear + 1) % 100 == q->head){
        return -1;
    }
    q->rear = (q->rear + 1) % 100;
    q->nums[q->rear] = n;
    return 1;
}

int dequeue(queue *q){
    if (q->head == q->rear){
        return -1;
    }
    q->head = (q->head + 1) % 100;
    return q->nums[q->head];
}

int main(){
    queue yanghui;
    yanghui.head = yanghui.rear = 0;
    int n;
    scanf("%d", &n);
    if (n == 1){
        printf("1\n");
        return 0;
    }
    enqueue(&yanghui, 0);
    enqueue(&yanghui, 1);
    for (int i = 2; i <= n - 1; i++){
        if (enqueue(&yanghui, 0) == -1){
            printf("队列已满");
            return 0;
        }
        for (int j = 0; j < i; j++){
            int temp = dequeue(&yanghui);
            if (temp == -1){
                printf("队列已满");
                return 0;
            }
            temp += yanghui.nums[(yanghui.head + 1) % 100];
            enqueue(&yanghui, temp);
        }
    }
    enqueue(&yanghui, 0);
    for (int j = 0; j < n; j++){
        int temp = dequeue(&yanghui);
        if (temp == -1){
            printf("队列已满");
            return 0;
        }
        temp += yanghui.nums[(yanghui.head + 1) % 100];
        printf("%d ", temp);
        enqueue(&yanghui, temp);
    }
}