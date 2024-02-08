#include <stdio.h>
#include <stdlib.h>

void merge(int A[], int Tmp[], int L, int R, int Rend){
    int Lend = R - 1, ptr = L, num = Rend - L + 1;
    while (L <= Lend && R <= Rend){
        if (A[L] <= A[R])
            Tmp[ptr++] = A[L++];
        else 
            Tmp[ptr++] = A[R++];
    }
    while (L <= Lend)
        Tmp[ptr++] = A[L++];
    while (R <= Rend)
        Tmp[ptr++] = A[R++];
    for (int i = 0; i < num; i++, Rend--){
        A[Rend] = Tmp[Rend];
    }
}

void Msort(int A[], int Tmp[], int L, int Rend){
    if (L < Rend){
        int mid = (L + Rend) / 2;
        Msort(A, Tmp, L, mid);
        Msort(A, Tmp, mid + 1, Rend);
        merge(A, Tmp, L, mid + 1, Rend);
        for (int i = 0; i < 12; i++)
            printf("%d ", A[i]);
        printf("\n");
    }
}

int main(){
    int A[12], Tmp[12] = {0};
    for (int i = 0; i < 12; i++)
        scanf("%d", &A[i]);
    for (int i = 0; i < 12; i++)
        printf("%d ", A[i]);
    printf("\n");
    Msort(A, Tmp, 0, 11);
}