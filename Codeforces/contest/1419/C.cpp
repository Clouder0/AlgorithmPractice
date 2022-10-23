#include <cstdio>
const int maxn = 2e3 + 100;
int T,n,x,a[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&x);
        int flag = 0,flag2 = 1;
        int sum = 0;
        for (int i = 1; i <= n; ++i) scanf("%d",a + i),flag |= (a[i] == x),flag2 &= (a[i] == x),sum += a[i];
        if(flag2) puts("0");
        else if(flag) puts("1");
        else if(sum == n * x) puts("1");
        else puts("2");
    }
    return 0;
}