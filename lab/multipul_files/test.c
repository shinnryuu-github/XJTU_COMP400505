#include <stdio.h>

extern int sum(int x, int y);

int main(){
    int a =10, b = 20;
    printf("%d", sum(a, b));
}