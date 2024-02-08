#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pre(char tree[], int len, int position){
    if (position >= len)
        return;
    if (tree[position] == '0')
        return;
    printf("%c", tree[position]);
    pre(tree, len, 2 * position + 1);
    pre(tree, len, 2 * position + 2);
}

void in(char tree[], int len, int position){
    if (position >= len)
        return;
    if (tree[position] == '0')
        return;
    in(tree, len, 2 * position + 1);
    printf("%c", tree[position]);
    in(tree, len, 2 * position + 2);
}

void ba(char tree[], int len, int position){
    if (position >= len)
        return;
    if (tree[position] == '0')
        return;
    ba(tree, len, 2 * position + 1);
    ba(tree, len, 2 * position + 2);
    printf("%c", tree[position]);
}

int main(){
    char tree[100];
    gets(tree);
    int len = strlen(tree);
    pre(tree, len, 0);
    printf("\n");
    in(tree, len, 0);
    printf("\n");
    ba(tree, len, 0);
}