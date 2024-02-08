#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int No;
    int data;
    struct _Node* next;
}Node;

Node* createNode(int No, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->No = No;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void josephus(int n, int m, int* passwords) {
	Node* head = createNode(1, passwords[0]);
	Node* tail = head;
    int i;

    for (i = 1; i < n; ++i) {
        tail->next = createNode(i + 1, passwords[i]);
        tail = tail->next;
    }
    tail->next = head;

	Node* prev = tail;
	Node* current = head;
    int count = 1;

    printf("出列顺序：");
    while (n > 0) {
        if (count == m) {
            printf("%d ", current->No);
            prev->next = current->next;
            m = current->data;
            free(current);
            current = prev->next;
            count = 1;
            n--;
        } else {
            prev = current;
            current = current->next;
            count++;
        }
    }
    printf("\n");
}

int main() {
    int N, m, i;
    printf("输入m n的值："); 
    scanf("%d %d", &N, &m);
    printf("输入密码："); 
    int passwords[N];
	for (i = 0; i < N; i++)
	{
		scanf("%d", &passwords[i]);
	}
    josephus(N, m, passwords);
    return 0;
}

