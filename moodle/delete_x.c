#include <stdio.h>
#include <string.h>
 
#define MAX_SIZE 100
#define MAX_ELEMENT_SIZE 20
 
void removeElement(char arr[][MAX_ELEMENT_SIZE], int *len, const char *x) {
    int i, j = 0;
    for (i = 0; i < *len; i++) {
        if (strcmp(arr[i], x) != 0) {
            strcpy(arr[j++], arr[i]);
        }
    }
    *len = j;
}
 
int main() {
    char arr[MAX_SIZE][MAX_ELEMENT_SIZE];
    int len = 0;
 
     
    while (scanf("%s", arr[len]) != EOF) {
        len++;
    }
 
    removeElement(arr, &len, "x");
 
    for (int i = 0; i < len; i++) {
        printf("%s ", arr[i]);
    }
    return 0;
}
