#include <cstdio>
#include <algorithm>
const int maxn = 510, maxm = 125010;
int n, m;
int U[maxm],V[maxm],out[maxn];
double a[maxn][maxn],f[maxn],g[maxm];
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d %d", U + i, V + i);
        if(U[i] > V[i]) std::swap(U[i],V[i]);
        out[U[i]]++,out[V[i]]++;
    }
    for (int i = 1; i < n; ++i) a[i][i] = 1.0;
    a[1][n] = 1;
    for (int i = 1; i <= m; ++i) 
    {
        if(V[i] == n) continue;
        a[U[i]][V[i]] -= 1.0 / out[V[i]];
        a[V[i]][U[i]] -= 1.0 / out[U[i]];
    }
    for (int i = 1; i < n; ++i)
    {
        int maxx = i;
        for (int j = i + 1; j < n; ++j)
            if (a[j][i] > a[maxx][i]) maxx = j;
        std::swap(a[maxx], a[i]);
        for (int j = 1; j < n; ++j)
        {
            if(i == j) continue;
            double t = a[j][i] / a[i][i];
            for (int k = i; k <= n; ++k) a[j][k] -= t * a[i][k];
        }
    }
    for (int i = 1; i < n; ++i) f[i] = a[i][n] / a[i][i];
    for (int i = 1; i <= m; ++i)
    {
        if (V[i] == n) g[i] += f[U[i]] / out[U[i]];
        else g[i] += f[U[i]] / out[U[i]] + f[V[i]] / out[V[i]];
    }
    std::sort(g + 1,g + 1 + m);
    double ans = 0;
    for (int i = 1; i <= m; ++i)  ans += (m - i + 1) * g[i];
    printf("%.3f",ans);
    return 0;
}