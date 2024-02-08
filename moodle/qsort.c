#include <stdio.h>

void print_array(int A[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int pivot_pos(int A[], int L, int R, int size, int *swapped){
    int pivot = A[L];
    *swapped = 0;
    while (L < R){
        while (L < R && A[R] >= pivot)
            R--;
        if (L < R) {
            A[L] = A[R];
            *swapped = 1;
        }
        while (L < R && A[L] <= pivot)
            L++;
        if (L < R) {
            A[R] = A[L];
            *swapped = 1;
        }
    }
    A[L] = pivot;
    return L;
}

void qsort(int A[], int L, int R, int size){
    if (L < R){
        int swapped;
        int pivotpos = pivot_pos(A, L, R, size, &swapped);
        if (swapped) {
            print_array(A, size);
        }
        qsort(A, L, pivotpos - 1, size);
        qsort(A, pivotpos + 1, R, size);
    }
}

int main(){
    int A[12];
    for (int i = 0; i < 12; i++)
        scanf("%d", &A[i]);
    print_array(A, 12);
    qsort(A, 0, 11, 12);
}
