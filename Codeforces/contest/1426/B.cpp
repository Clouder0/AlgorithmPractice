#include <cstdio>
const int maxn = 110;
int T,n,m;
int lu[maxn],ld[maxn],ru[maxn],rd[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for (int i = 1; i <= n; ++i) scanf("%d %d %d %d", lu + i, ru + i, ld + i, rd + i);
        if(m % 2) goto no;
        for (int i = 1; i <= n; ++i) if(ld[i] == ru[i]) goto yes;
        no: puts("NO");
        continue;
        yes:puts("YES");
    }
    return 0;
}