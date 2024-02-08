#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int num;
    char name;
} Node;

int main(){
    char buffer1[100], buffer2[100];
    Node nodes[10], nodes2[10];
    int count = 0;
    char c;
    while ((c = getchar()) != '\n'){
        if (c <= '9' && c >= '0'){
            nodes[count].num = c - '0';
            count++;
        }
        else if (c >= 'A' && c <= "Z"){
            nodes[count].name = c;
        }
    }
    int count2 = 0;
    while ((c = getchar()) != EOF){
        if (c <= '9' && c >= '0'){
            nodes2[count2].num = c - '0';
            count2++;
        }
        else if (c >= 'A' && c <= "Z"){
            nodes2[count2].name = c;
        }
    }
    int k = 0, i = 0, j = 0;
    Node node3[20];
    while(i < count && j < count2){
        if (nodes[i].name == nodes2[j].name){
            node3[k].name = nodes2[j].name;
            node3[k].num = nodes[i].num + nodes2[j].num;
            i++;
            j++;
            k++;
        }
        else if (nodes[i].name < nodes2[j].name){
            node3[k].name = nodes[i].name;
            node3[k].num = nodes[i].num;
            k++;
            i++;
        }
        else{
            node3[k].name = nodes2[j].name;
            node3[k].num = nodes2[j].num;
            k++;
            j++;
        }
    }
    for (; i < count; i++){
        node3[k].name = nodes[i].name;
        node3[k].num = nodes[i].num;
        k++;
    }
    for (; j < count2; j++){
        node3[k].name = nodes2[j].name;
        node3[k].num = nodes2[j].num;
        k++;
    }
    for (int i = 0; i < k - 1; i++){
        printf("%c %d, ", node3[i].name, node3[i].num);
    }
    printf("%c %d;", node3[k - 1].name, node3[k - 1].num);
}