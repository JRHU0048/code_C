DP1 斐波那契数列
#include <stdio.h>

int main() {
    int n;
    scanf("%d\n",&n);
    int a[40];
    a[0]=1,a[1]=1;
    for(int i=2;i<n;i++)
    {
        a[i]=a[i-1]+a[i-2];
    }
    printf("%d\n",a[n-1]);
    return 0;
}

DP2 跳台阶
#include <stdio.h>

int main() {
    int n;
    scanf("%d",&n);
    int a[40];
    a[0]=1,a[1]=2;
    for(int i=2;i<n;i++)
    {
        a[i]=a[i-1]+a[i-2];
    }
    printf("%d\n",a[n-1]);
    return 0;
}

DP3 跳台阶扩展问题
#include <stdio.h>

int main() {
    int n=0;
    scanf("%d",&n);
    int a[20]={0};
    a[0]=0,a[1]=1,a[2]=2,a[3]=4;
    for(int i=4;i<=n;i++)
    {
        for(int j=1;j<i;j++)
        {
            a[i]+=a[j];
        }
        a[i]++;
    }
    printf("%d\n",a[n]);
    return 0;
}
