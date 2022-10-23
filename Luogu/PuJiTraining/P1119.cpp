#include <cstdio>
#include <algorithm>
const int maxn = 210;
int n,m, q;
int T[maxn];
int dis[maxn][maxn][maxn];
int inf = 1e9;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", T + i);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) dis[0][i][j] = inf;
    for (int i = 1; i <= n; ++i) dis[0][i][i] = 0;
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ++u, ++v;
        dis[0][u][v] = dis[0][v][u] = w;
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                dis[k][i][j] = std::min(dis[k - 1][i][j], dis[k - 1][i][k] + dis[k - 1][k][j]);
    scanf("%d",&q);
    while(q--)
    {
        int x, y, t;
        scanf("%d%d%d", &x, &y, &t);
        ++x, ++y;
        int k = std::upper_bound(T + 1, T + 1 + n, t) - T - 1;
        if (dis[k][x][y] >= inf || T[x] > t || T[y] > t) puts("-1");
        else printf("%d\n", dis[k][x][y]);
    }
    return 0;
}