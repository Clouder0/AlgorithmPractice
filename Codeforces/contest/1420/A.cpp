#include <cstdio>
const int maxn = 1e5 + 100;
int T,n,a[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i) scanf("%d",a + i);
        for (int i = 1; i < n; ++i) if(a[i] <= a[i + 1]) goto YES;
        puts("NO");
        continue;
        YES:puts("YES");
    }
    return 0;
}