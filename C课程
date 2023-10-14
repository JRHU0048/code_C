//c语言程序设计实验一(0828)

//可以用，自己写的，比较简陋
#include<stdio.h>
int main() {
	  int i, total, d, c;
	  int n;
	  total = 0;
	  scanf_s("%d", &n);
	  for (i = 1;i <= n;i++)
	  {
		  d = i;
		  c = 0;
		  int m = 0;
		  while (d)
		{
		c = d % 10;
		if (c == 5) {
				m = 1;
				break;
		}

		if (c == 1) {
				m = 1;
				break;
		}
		else
			d = d / 10;
		}
		if (!m) {
			  total++;
		}
	}
	  printf("%d\n", total);
	  return 0;
}

//判断一个数既不含5也不含1
#include <stdio.h>
int count(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        int num = i;
        int m = 0;
        while (num > 0) {
            int digit = num % 10;
            if (digit == 1 || digit == 5) {
                m = 1;
                break;
            }
            num /= 10;
        }
        if (!m) {
            count++;
        }
    }
    return count;
}
int main() {
    int n;
    printf("请输入一个数n: ");
    scanf_s("%d", &n);
    int result = count(n);
    printf("%d\n", result);
    return 0;
}

#include<stdio.h>
void f(int a){
	a = 200;
}

int main(){
	int a = 100;
	f(a);
	printf("%d", a);
	return 0;
}

#include<stdio.h>
int a1 = 1;
int a2 = 2;
void f(int* c) {
	*c = &a2;
}
int main() {
	int* b = &a1;
	f(&b);
	printf("%d", *b);
	return 1;
}

//求两个数最大公约数的算法    辗转相除法  这个算法有一点问题， a<b时或者没有最大公约数的时候仍然能输出结果 
#include <stdio.h>
#include<stdlib.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1, num2;
    printf("请输入两个整数：");
    scanf_s("%d%d", &num1, &num2);
    int result = gcd(num1, num2);
    printf("最大公约数为：%d\n", result);
    system("pause");
    return 0;
}

#include<stdio.h>
int main() {
	int num1, num2 ,TmpNum;
	scanf_s("%d%d", &num1, &num2);
	if (num1 < num2)
	{
		TmpNum = num1;
		num1 = num2;
		num2 = TmpNum;  /*找出两个数中较大的那一个*/
	}
	while (num2 != 0)
	{
		TmpNum = num1 % num2;  /*求两个数的余数*/
		num1 = num2;
		num2 = TmpNum;
	}
	printf("%d", num1);
	return 0;
}

//0903
#include <stdlib.h>
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int i, j;
    int* result = (int*)malloc(sizeof(int) * 2); // 内存分配 分配内存是为了方便输出
    *returnSize = 2;

    for (i = 0; i < numsSize - 1; i++) { // 循环条件改为 i<numsSize-1
        for (j = i + 1; j < numsSize; j++) { // 循环条件改为 j=i+1
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
    return NULL; // 没有找到匹配项，返回NULL
}

//数的整除算法
#include<stdio.h>
#include<stdlib.h>
int main() {
	int n = 100;
    printf("1到100内能被3整除但是不能被5整除的数有:");
    for (int i = 1;i <= 100;i++) {
		if (i % 3 == 0 && i % 5 != 0) {
            printf("%d  ", i);
		}
	}
	system("pause");
	return 0;
}

//计算n的阶乘之和
//方法1：
#include<stdio.h>
#include<stdlib.h>
long long int  factor1(int n) {
	long long  int sum = 0,m=1;
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= i;j++)
		{
			m *= j;
		}
		sum += m;
		m = 1;
	}
	return sum;
}
int main() {
	int n;
	printf("请输入一个数n：\n");
	scanf_s("%d", &n);
	long long int  result = factor1(n);
	printf("1到%d的阶乘之和为：%11d\n", n, result);
	system("pause");
	return 0;
}

//方法2：
#include <stdio.h>
#include<stdlib.h>
int factorial(int num) {
	if (num == 0 || num == 1) {
		return 1;
	}
	else {
		return num * factorial(num - 1);
	}
}
int main() {
	int n;
	printf("请输入整数 n：");
	scanf_s("%d", &n);
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += factorial(i);
	}
	printf("从 1 到 %d 的阶乘之和为：%d\n", n, sum);
	system("pause");
	return 0;
}

//利用函数来计算n的阶乘之和
#include <stdio.h>
#include<stdlib.h>
double  factor1(int n) {
	double  sum = 0, m = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			m *= j;
		}
		sum += m;
		m = 1;
	}
	return sum;
}
double factor2(int n) {
	double  sum = 0, m = 1;
	for (int i = 1;i <= n;i++) {
		m *= i;
		sum += m;
	}
	return sum;
}
int main() {
	int n;
	printf("请输入一个数n：\n");
	scanf_s("%d", &n);
	printf("1到%d的阶乘之和为：%lf\n", n, factor1(n));
	printf("\n");
	printf("1到%d的阶乘之和为：%lf\n", n, factor2(n));
	system("pause");
	return 0;
}

//利用数组来写斐波那契数列
int fib(int n) {
	int arr[n + 1];

	if (n < 2) {
		return n;
	}
	arr[0] = 0;
	arr[1] = 1;
	for (int i = 2;i <= n;i++) {
		arr[i] = arr[i - 1] + arr[i - 2];   省去了反复赋值的过程
	}
	return arr[n];
}

//反向复制数字检查回文数
bool isPalindrome(int x) {
long int a=x,b=0;
if(x>=0&&x<10)
return true;
else if(x<0)
return false;
else while(a>0)
{
	b=b*10+a%10;
	a=a/10;
}
if(b==x) return true;
else return false;
}

//求一个数的算数平方根，暴力检索   二分法*/ //for循环比while循环所需时间要长一点
#include<stdlib.h>
int mySqrt(int x){
	long long  k;
	if(x==0)
	return 0 ;
	if (x==1)
	return 1;
	for(long long  i=1;i<x;i++){
		if(i*i<=x && (i+1)*(i+1)>x)
		k=i;
	}
	return k;
}
int main() {
	int x;
	scanf_s("%d\n", &x);
	printf("输出为%d", mySqrt(x));
	system("pause");
	return 0;
}//不知道为什么，结果会溢出！！！！！！  

//或者：
int mySqrt(int x){
	long long i =1;
	while (i*i<=x){
		i++;
	}
	return i-1;
}






