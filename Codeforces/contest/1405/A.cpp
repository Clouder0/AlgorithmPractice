#include <cstdio>
#include <algorithm>
int T,n,a[110];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i) scanf("%d",a+i);
        for (int i = n; i; --i) printf("%d ", a[i]);
        puts("");
    }
    return 0;
}