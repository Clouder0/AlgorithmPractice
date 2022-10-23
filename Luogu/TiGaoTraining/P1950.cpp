#include <cstdio>
using namespace std;
const int maxn = 1e3 + 10;
int n,m;
char temp[maxn];
int a[maxn][maxn];
int up[maxn][maxn];
int l[maxn][maxn],r[maxn][maxn];
int s[maxn],top;
int main()
{
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;++i)
    {
        scanf("%s",temp+1);
        for(int j = 1;j<=m;++j)
            a[i][j] = (temp[j] == '.');
    }
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<=m;++j)
        {
            if(!a[i][j])
                continue;
            up[i][j] = up[i-1][j] + 1;
        }
    }
    for(int i = 1;i<=n;++i)
    {
        top = 0;
        for(int j = m;j;--j)
        {
            while(top && up[i][s[top]] >= up[i][j])
                l[i][s[top]] = j,--top;
            s[++top] = j;
        }
        while(top)
            l[i][s[top--]] = 0;
    }
    for(int i = 1;i<=n;++i)
    {
        top = 0;
        for(int j = 1;j<=m;++j)
        {
            while(top && up[i][s[top]] > up[i][j])
                r[i][s[top]] = j,--top;
            s[++top] = j;
        }
        while(top)
            r[i][s[top--]] = m + 1;
    }
    long long ans = 0;
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<=m;++j)
        {
            ans += up[i][j] * (j - l[i][j]) * (r[i][j] - j);
        }
    }
    printf("%lld",ans);
    return 0;
}