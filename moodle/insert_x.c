#include <stdio.h>



typedef struct 
{
    union 
    {
        int int_v;
        char char_v;
    }v;
    
}value;


int main(){
    value vs[5];
    int i = 0, len = 0, index;
    char input[100];
    gets(input);
    while (scanf(input + i, "%d", &vs[len].v.int_v) == 1) {
        len++;
        while (input[i] != ' ' && input[i] != '\n') {
            i++;
        }
        if (input[i] == '\n') {
            break;
        }
        i++;
    }
    scanf("%d", &index);
    for (int i = len; i >= index - 1; i--){
        vs[i].v.int_v = vs[i - 1].v.int_v;
    }
    vs[index - 1].v.char_v = 'x';
    for (int i = 0; i < index - 1; i++)
    {
        printf("%d ", vs[i].v.int_v);
    }
    printf("%c ", vs[index - 1].v.char_v);
    for (int i = index; i < len + 1; i++)
    {
        printf("%d ", vs[i].v.int_v);
    }
}