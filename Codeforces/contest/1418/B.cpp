#include <cstdio>
#include <algorithm>
const int maxn = 110;
int T,n,a[maxn],locked[maxn],b[maxn],bcnt;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1; i <= n; ++i) scanf("%d", locked + i);
        bcnt = 0;
        for (int i = 1; i <= n; ++i) if(!locked[i]) b[++bcnt] = a[i];
        std::sort(b + 1 ,b + 1 + bcnt);
        for (int i = 1; i <= n; ++i) if(!locked[i]) a[i] = b[bcnt--];
        for (int i = 1; i <= n; ++i) printf("%d ",a[i]);
        puts("");
    }
    return 0;
}