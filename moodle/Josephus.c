#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int num;
    struct _node *next;
}Node;

typedef Node *List;

List creat_list(int N){
    List L = (List)malloc(sizeof(Node));
    L->next = NULL;
    List r = L;
    for (int i = 1; i <= N; i++){
        List temp = (List)malloc(sizeof(Node));
        temp->num = i;
        temp->next = NULL;
        r->next = temp;
        r = temp;
    }
    List temp = L;
    L = L->next;
    free(temp);
    r->next = L;
    return L;
}

int main(){
    int N;
    scanf("%d", &N);
    List L = (List)malloc(sizeof(Node));
    L = creat_list(N);
    int count = 1, n = N;
    List head = L, pre = NULL;
    while (n >= 3){
        if (count == 3){
            n--;
            count = 1;
            pre->next = head->next;
            free(head);
            head = pre->next;
        }
        else {
            count++;
            pre = head;
            head = head->next;
        }
    }
    printf("%d ", head->num);
    head = head->next;
    printf("%d", head->num);
}