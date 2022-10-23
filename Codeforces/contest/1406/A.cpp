#include <cstdio>
const int maxn = 110;
int T,n,cnt[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i = 0; i <= 100; ++i) cnt[i] = 0;
        for (int i = 1,x; i <= n; ++i) scanf("%d",&x),cnt[x]++;
        int mexa = 0,mexb = 0;
        while(mexa <= 100 && cnt[mexa])  cnt[mexa++]--;
        while(mexb <= 100 && cnt[mexb])  cnt[mexb++]--;
        printf("%d\n",mexa + mexb);
    }
    return 0;
}