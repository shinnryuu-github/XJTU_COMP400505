#include <stdio.h>
#include <stdlib.h>


typedef struct _node{
    char ch;
    struct _node *next;
} node;

typedef node *stack;

void push(stack *s, char c){
    stack temp = (stack)malloc(sizeof(node));
    temp->ch = c;
    temp->next = *s;
    *s = temp;
}

char top(stack s){
    return s->ch;
}

char pop(stack *s){
    if ((*s)->ch == '$'){
        return '$';
    }
    stack temp = *s;
    (*s) = (*s)->next;
    char r = temp->ch;
    free(temp);
    return r;
}

char opp(char s){
    if (s == '{'){
        return '}';
    }
    else if (s == '['){
        return ']';
    }
    else if (s == '('){
        return ')';
    }
}

int main(){
    stack s = (stack)malloc(sizeof(node));
    s->ch = '$';
    char c, chars[100];
    int is = 1, count = 0;
    while ((c = getchar()) != EOF){
        if (c == '{' || c == '[' ||c == '(' ||c == '}' ||c == ']' ||c == ')' )
        chars[count++] = c;
    }
    for (int i = 0; i < count; i++){
        if (chars[i] == '{'){
            push(&s, chars[i]);
        }
        else if (chars[i] == '['){
            push(&s, chars[i]);
        }
        else if (chars[i] == '('){
            push(&s, chars[i]);
        }
        else if (chars[i] == '}'){
            if (top(s) == '{'){
                pop(&s);
            }
            else{
                is = 0;
                printf("缺少{括号");
            }
        }
        else if (chars[i] == ']'){
            if (top(s) == '['){
                pop(&s);
            }
            else{
                is = 0;
                printf("缺少[括号");
            }
        }
        else if (chars[i] == ')'){
            if (top(s) == '('){
                pop(&s);
            }
            else{
                is = 0;
                printf("缺少(括号");
            }
        }
    }
    while (top(s) != '$'){
        printf("缺少%c括号", opp(pop(&s)));
        is = 0;
    }
    if (is == 1) printf("匹配成功");
}