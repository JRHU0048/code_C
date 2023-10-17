#include <stdio.h>
#include<stdlib.h>

int ways_to_fill(int N) {
    if (N <= 2) {
        return N;
    }
    int a = 1, b = 2, c = 4; 
    for (int i = 4; i <= N; ++i) {
        int temp = a + b + c;
        a = b;
        b = c;
        c = temp;
    }
    return c;
}

int main() {
    int N;
    scanf_s("%d", &N);
    printf("结果为: %d\n", ways_to_fill(N));
    system("pause");
    return 0;
}
