#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int maxn = 2e5 + 100;
int T,n;
char s[maxn];
int f[maxn],st[maxn],top,r[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        scanf("%s",s + 1);
        top = 0;
        for (int i = 1; i <= n; ++i)
        {
            f[i] = 1;
            if (s[i] == s[i - 1]) f[i] += f[i - 1], f[i - 1] = 0;
        }
        for (int i = 1; i <= n; ++i) if(f[i]) st[++top] = f[i],r[top] = i;
        int p = 1,now = 1,ans = 0;
        while(now <= top)
        {
            ++ans;
            if(p < now) p = now;
            while(p <= top && st[p] == 1) ++p;
            if(p <= top) --st[p],++now;
            else now += 2;
        }
        printf("%d\n",ans);
    }
    return 0;
}