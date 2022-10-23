#include <cstdio>
#include <algorithm>
const int maxn = 20;
int n, m;
int a[maxn][maxn], b[maxn][maxn];
int up[maxn];
int save()
{
    int s = 0;
    for (int i = m; i; --i)
    {
        int walk = (1 << (up[i] - up[i + 1])) - 1;
        s = (s << (up[i] - up[i + 1] + 1)) | walk;
    }
    return s;
}
int f[30000001];
int dfs(int s, int step)
{
    // step = 0: last
    // step = 1: first
    if (f[s] != -(1 << 30) && f[s] != (1 << 30)) return f[s];
    if(up[m] == n) return f[s] = 0;
    int res = step ? -(1 << 30) : (1 << 30);
    for (int i = m; i; --i)
    {
        if (up[i] + 1 <= up[i - 1])
        {
            ++up[i];
            if(step)
                res = std::max(res, dfs(save(), step ^ 1) + a[up[i]][i]);
            else
                res = std::min(res, dfs(save(), step ^ 1) - b[up[i]][i]);
            --up[i];
        }
    }
    
//    for(int i = 1;i<=m;++i) printf("%d ",up[i]);
//    puts("");
//    printf("f=%d step=%d\n",res,step);
//    puts("");
    
    return f[s] = res;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) scanf("%d", a[i] + j);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) scanf("%d", b[i] + j);
    for (int i = 0; i <= 30000000; ++i) f[i] = -(1 << 30);
    up[0] = n;
    for (int i = 1; i <= m; ++i) up[i] = 0;
    int res = dfs(save(), 1);
    printf("%d\n",res);
    return 0;
}