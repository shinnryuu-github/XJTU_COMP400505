#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void n(char *T, int next[], int len){
    next[0] = -1;
    int i = 0, k = -1;
    while (i < len - 1){
        if (k == -1 || T[i] == T[k]){
            i++;
            k++;
            next[i] = k;
        }
        else {
            k = next[k];
        }
    }
}


int main(){
    int next[10];
    char *str = "abacababdeadcde";
    char T[10];
    gets(T);
    int i = 0, j = 0, pos;
    int len = strlen(T), size = strlen(str);
    n(T, next, len);
    while (i < size  && j < len ){
        if (j == -1 || str[i] == T[j]){
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }
    if (j > len - 1){
        pos = i - len + 1;
    }
    else
        pos = -1;
    if (pos == -1){
        printf("匹配未成功\n");
        for (int i = 0; i < len; i++){
        printf("%d", next[i]);
        }
    }
    else {
        printf("匹配成功\n");
        for (int i = 0; i < len; i++){
            printf("%d", next[i]);
        }
    }
}