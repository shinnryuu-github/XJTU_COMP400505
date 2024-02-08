#include <stdio.h>
#include <stdlib.h>

int main(){
    int gap[] = {3, 2, 1};
    int A[12];
    for (int i = 0; i < 12; i++)
        scanf("%d", &A[i]);
    for (int g = 3; g > 0; g--){
        for (int i = g; i < 12; i++){
            int temp = A[i], j;
            for (j = i; j >= g && A[j - g] > temp; j -= g)
                A[j] = A[j - g];
            A[j] = temp;
        }
        for (int k = 0; k < 12; k++)
            printf("%d ", A[k]);
        printf("\n");
    }
}