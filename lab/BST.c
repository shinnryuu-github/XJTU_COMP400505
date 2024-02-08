#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM 1000

//二叉链表实现二叉搜索树
typedef struct _tnode{
    int data;
    struct _tnode *left, *right;
} tnode;

typedef tnode *Ps;
typedef tnode *BCT;

BCT insert1(BCT t, int d){
    if (!t){
        BCT ptr = malloc(sizeof(tnode));
        ptr->data = d;
        ptr->left = ptr->right = NULL;
        return ptr;
    }
    if (d < t->data)
        t->left = insert1(t->left, d);
    else if (d > t->data)
        t->right = insert1(t->right, d);
    return t;
}

Ps find1(BCT t, int d){
    if (!t){
        return NULL;
    }
    if (d < t->data)
        return find1(t->left, d);
    else if (d > t->data)
        return find1(t->right, d);
    return t;
}

Ps findmin1(BCT t){
    if (!t){
        return NULL;
    }
    Ps ptr = t;
    while(ptr->left){
        ptr = ptr->left;
    }
    return ptr;
}

BCT delete1(BCT t, int d){
    if (!t){
        return NULL;
    }
    if (d < t->data){
        t->left = delete1(t->left, d);
    }
    else if (d > t->data){
        t->right = delete1(t->right, d);
    }
    else{
        if (t->left && t->right){
            Ps ptr = findmin1(t->right);
            t->data = ptr->data;
            t->right = delete1(t->right, ptr->data);
        }
        else {
            Ps ptr = t;
            if (!t->left){
                t = t->right;
            }
            else{
                t = t->left;
            }
            free(ptr);
        }
    }
    return t;
}

int WPL1(BCT t, int d){
    if (!t){
        return 0;
    }
    return d + WPL1(t->left, d + 1) + WPL1(t->right, d + 1);
}

void print1(BCT t){
    if (t){
        print1(t->left);
        printf("%d ", t->data);
        print1(t->right);
    }
}

// 顺序表实现二叉搜索树
typedef struct {
    int data;
    int isNull;
} TreeNode;

typedef TreeNode SBT[MAXNUM];

int find2(SBT t, int d, int *pos) {
    *pos = 1;
    while (!t[*pos].isNull && (*pos < MAXNUM)) {
        if (d < t[*pos].data) {
            *pos = 2 * (*pos);
        } else if (d > t[*pos].data) {
            *pos = 2 * (*pos) + 1;
        } else {
            return 1;
        }
    }
    return t[*pos].isNull ? 0 : 1;
}

void insert2(SBT t, int d) {
    int pos;
    if (!find2(t, d, &pos)) {
        t[pos].data = d;
        t[pos].isNull = 0;
    }
}

void print2(SBT t, int idx) {
    if (!t[idx].isNull) {
        print2(t, 2 * idx);
        printf("%d ", t[idx].data);
        print2(t, 2 * idx + 1);
    }
}

void initializeSBT(SBT t) {
    for (int i = 0; i < MAXNUM; i++) {
        t[i].isNull = 1;
    }
}

int WPL2(SBT t, int idx, int d) {
    if (t[idx].isNull) {
        return 0;
    }
    return d + WPL2(t, 2*idx, d + 1) + WPL2(t, 2*idx + 1, d + 1);
}

int findmin2_pos(SBT t, int idx) {
    while (!t[2*idx].isNull) {
        idx = 2*idx;
    }
    return idx;
}

void delete2(SBT t, int d) {
    int pos;
    if (find2(t, d, &pos)) {
        if (!t[2*pos].isNull && !t[2*pos+1].isNull) {
            t[pos].isNull = 1;
        } else if (!t[2*pos].isNull) {
            t[pos] = t[2*pos+1];
            t[2*pos+1].isNull = 1;
        } else if (!t[2*pos+1].isNull) {
            t[pos] = t[2*pos];
            t[2*pos].isNull = 1;
        } else {
            int replacePos = findmin2_pos(t, 2*pos+1);
            t[pos].data = t[replacePos].data;
            delete2(t, t[replacePos].data);
        }
    }
}


//AVL
typedef struct _node{
    int height, data;
    struct _node *left, *right;
} node;

typedef node *AVL;

int max(int a, int b){
    return (a > b) ? a : b;
}

int get_height(AVL t){
    if (!t) return 0;
    return t->height;
}

void updateHeight(AVL t){
    t->height = max(get_height(t->left), get_height(t->right)) + 1;
}

int getBalance(AVL t){
    if (!t)
        return 0;
    return get_height(t->left) - get_height(t->right);
}

void LL(AVL *t){
    AVL left = (*t)->left;
    (*t)->left = left->right;
    left->right = (*t);
    updateHeight(*t);
    updateHeight(left);
    (*t) = left;
}

void RR(AVL *t){
    AVL right = (*t)->right;
    (*t)->right = right->left;
    right->left = (*t);
    updateHeight(*t);
    updateHeight(right);
    (*t) = right;
}

void LR(AVL *t){
    RR(&(*t)->left);
    LL(t);
}

void RL(AVL *t){
    LL(&(*t)->right);
    RR(t);
}

void insert3(AVL *t, int data){
    node *temp = malloc(sizeof(node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    if (!(*t)){
        (*t) = temp;
    }
    else if (data < (*t)->data){
        insert3(&(*t)->left, data);
        if (getBalance(*t) >= 2){
            if (data < (*t)->left->data){
                LL(t);
            }
            else {
                LR(t);
            }
        }
    }
    else if (data > (*t)->data){
        insert3(&(*t)->right, data);
        if (getBalance(*t) <= -2){
            if (data > (*t)->right->data){
                RR(t);
            }
            else {
                RL(t);
            }
        }
    }
    updateHeight(*t);
}

int WPL3(AVL t, int d){
    if (!t) return 0;
    return d + WPL3(t->left, d + 1) + WPL3(t->right, d + 1);
}

void print3(AVL t){
    if (t){
        print3(t->left);
        printf("%d ", t->data);
        print3(t->right);
    }
}

AVL minValueNode(AVL t){
    AVL current = t;
    while (current->left != NULL)
        current = current->left;
    return current;
}

int main(){
    //二叉链表实现二叉搜索树
    printf("二叉链表实现二叉搜索树\n");
    char buffer[100];
    int count = 0, inputs[MAXNUM], d;
    BCT t = NULL;
    printf("请输入数字：");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        char *token = strtok(buffer, " \n");
        while (token) {
            int d;
            if (sscanf(token, "%d", &d) == 1) {
                inputs[count] = d;
                t = insert1(t, inputs[count++]);
            }
            token = strtok(NULL, " \n");
        }
    }
    printf("中序遍历结果：\n");
    print1(t);
    int wpl = WPL1(t, 0);
    printf("\n平均查找长度为：%.3f\n", 1.0 * wpl / count);
    int del;
    printf("请输入删除的元素：");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        if (sscanf(buffer, "%d", &del) == 1) {
            if (!find1(t, del)) {
                printf("无%d\n", del);
            } else {
                t = delete1(t, del);
                printf("中序遍历结果：\n");
                print1(t);
            }
        }
    }

    //顺序存储实现二叉排序树
    printf("\n顺序存储实现二叉排序树\n");
    SBT t2;
    initializeSBT(t2);
    count = 0;
    printf("\n请输入数字：");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        char *token = strtok(buffer, " \n");
        while (token) {
            int d;
            if (sscanf(token, "%d", &d) == 1) {
                inputs[count++] = d;
                insert2(t2, d);
            }
            token = strtok(NULL, " \n");
        }
    }
    printf("中序遍历结果：\n");
    print2(t2, 1);
    int wpl2 = WPL2(t2, 1, 0);
    printf("\n平均查找长度为：%.3f\n", 1.0 * wpl2 / count);

    printf("请输入删除的元素：");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        if (sscanf(buffer, "%d", &del) == 1) {
            int pos;
            if (!find2(t2, del, &pos)) {
                printf("无%d\n", del);
            } else {
                delete2(t2, del);
                printf("中序遍历结果：\n");
                print2(t2, 1);
            }
        }
    }


    // AVL
    printf("\n平衡二叉树\n");
    AVL t3 = NULL;
    count = 0;
    printf("\n请输入数字：");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        char *token = strtok(buffer, " \n");
        while (token) {
            int d;
            if (sscanf(token, "%d", &d) == 1) {
                inputs[count++] = d;
                insert3(&t3, d);
            }
            token = strtok(NULL, " \n");
        }
    }
    printf("中序遍历结果：\n");
    print3(t3);
    int wpl3 = WPL3(t3, 0);
    printf("\n平均查找长度为：%.3f\n", 1.0 * wpl3 / count);
}