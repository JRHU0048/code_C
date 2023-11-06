#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define D 3
#define L 2

void int_random() {
    srand((unsigned int)time(NULL));
}
double f1() {
    double r2 = (double)(rand() % (D * 10000)) / 10000;  // 生成0到(D-1)的随机小数  火柴长度投影
    return r2;
}

double f2() {
    double r2 = (double)(rand() % (L * 10000)) / 10000;  // 生成0到(L-1)的随机小数  火柴长度投影
    return r2;
}

int main() {
    int n = 0;
    int N;
    printf("请输入N的值: ");
    scanf_s("%d", &N);
   
    for (int i = 0; i < N; i++) {
        double t = f1();  // 中点
        double r = f2();  // 长度
       
        if (t * 2 < D-1 && t * 2 - r < 0) {  // 落点在0到D/2范围
            n++;
        }
        else if (t * 2 >= D-1 && 2*(D - t) <= r) {  // 落点在D/2到D范围
            n++;
        }
    }

    double p = (double)n /N;
    printf("相交的次数为：%d\n", n);
    printf("相交的概率p:%f\n", p);
    system("pause");
    return 0;
}
以上是我自己写的不对的程序，后面再看看问题出现在了哪里。
