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

day_1107再次看昨天的题，发现了很多的问题，解决如下：
https://blog.csdn.net/undefinedUser_1/article/details/122827971
时间种子一定要放在循环外面，否则无法生成随机数！参考博客如上：

使用double类型转换时可能整数位用不了那么多，最高只有5位整数位？没搞懂为什么。
day_1107更新如下：可以跑通
    
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define pi 3.141592653
#define DEC (pi/180)

int main() {
	srand((unsigned int)time(NULL));
	int d=2,l=1,N=1000000;

	/*printf("请输入d和l的值：\n");
	scanf_s("%d%d\n", &d ,&l);
	printf("请输入实验次数N：");
	scanf_s("%d\n", &N);*/

	int m = 0;
	for (int i = 0;i < N;i++) {
		double r1 = double(rand() % (d * 1000+1)) / 1000;   //随机中点坐标
		double r2 = double(rand() % (900))/10;    //产生随机度数0-90°
		double y = sin(r2 * DEC);    //将角度转换为0-1区间
		double t = l * y;     //计算投影长度
		
		if (2 * r1 <= d && 2 * r1 <= t)
		{
			m++;
		}
		else if (2 * r1 >= d && 2 * (d - r1) <= t)
		{
			m++;
		}
	}
	printf("投中次数为：%d\n", m);
	printf("概率为：%f\n", double(m) / N);
	system("pause");
	return 0;
}
