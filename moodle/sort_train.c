#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int data;
    struct _node *next;
} node;


typedef struct{
    node *head, *rear;
}queue;

int is_empty(queue q){
    if (q.head == NULL){
        return 1;
    }
    return 0;
}

void enqueue(queue *q, int data){
    node *temp = malloc(sizeof(node));
    if (is_empty(*q)){
        temp->data = data;
        temp->next = NULL;
        q->rear = q->head = temp;
        return;
    }
    temp->data = data;
    temp->next = NULL;
    q->rear->next = temp;
    q->rear = temp;
}

int dequeue(queue *q){
    if (is_empty(*q)){
        return -1;
    }
    node *temp = q->head;
    q->head = q->head->next;
    int r = temp->data;
    free(temp);
    return r;
}

int rear(queue q){
    if (is_empty(q)){
        return -1;
    }
    return q.rear->data;
}

int head(queue q){
    return q.head->data;
}

void print(queue *q){
    int nums[5], count = 0;
    while (!is_empty(*q)){
        nums[count] = dequeue(q);
        count++;
    }
    for (int i = count - 1; i >= 0; i--){
        printf("%d ", nums[i]);
    }
}

int main()
{
    int n = 5;
    int inputs[n];
    queue input;
    input.head = input.rear = NULL;
    for (int i = 0; i < n; i++){
        int no;
        scanf("%d", &no);
        inputs[i] = no;
    }
    for (int i = n - 1; i >= 0; i--){
        enqueue(&input, inputs[i]);
    }
    queue rails[3];
    for (int i = 0; i < 3; i++){
        rails[i].head = rails[i].rear = NULL;
    }
    while (!is_empty(input)){
        int temp = dequeue(&input);
        int is_sucsess = 3;
        for (int i = 0; i < 3; i++){
            if (is_empty(rails[i])){
                enqueue(&rails[i], temp);
                break;
            }
            else if (rear(rails[i]) < temp){
                enqueue(&rails[i], temp);
                break;
            }
            else {
                is_sucsess--;
            }
        }
        if (!is_sucsess){
            printf("重排失败");
            return 0;
        }
    }
    queue output;
    output.head = output.rear = NULL;
    while(!is_empty(rails[0]) || !is_empty(rails[1]) || !is_empty(rails[2])){
        int min = 6, index;
        for (int i = 0; i < 3; i++){
            if (!is_empty(rails[i])){
                if (head(rails[i]) < min){
                    min = head(rails[i]);
                    index = i;
                }
            }
        }
        dequeue(&rails[index]);
        enqueue(&output, min);
    }
    print(&output);
}