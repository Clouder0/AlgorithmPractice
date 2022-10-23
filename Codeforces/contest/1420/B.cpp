#include <cstdio>
const int maxn = 1e5 + 100;
int T,n,a[maxn];
long long num[33];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i) scanf("%d",a + i);
        for(int i = 0;i<=30;++i) num[i] = 0;
        long long ans = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 30; j >= 0; --j)
                if (a[i] & (1 << j)) { ans += num[j]++; break; }
        printf("%lld\n",ans);
    }
    return 0;
}