#include <stdio.h>
#include <math.h>

int divideThenRound(int top, int bottom) {
    int quotient = top / bottom;
    int result = round(quotient);
    return result;
}

int main() {
    int t = 10;
    int b = 2;
    int result = divideThenRound(t, b);
    printf("round(%d/%d)=%d\n", t, b, result);

    int t2 = 9;
    int b2 = 4;
    int result2 = divideThenRound(t2, b2);
    printf("round(%d/%d)=%d\n", t2, b2, result2);

    int t3 = 3;
    int b3 = 4;
    int result3 = divideThenRound(t3, b3);
    printf("round(%d/%d)=%d\n", t3, b3, result3);

    return 0;
}
