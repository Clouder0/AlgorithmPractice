#include <algorithm>
#include <cstdio>
#include <queue>
const int maxn = 1e3;
const int inf = 1 << 29;
int n;
int a[maxn][maxn];
bool vis[maxn];
int dis[2][maxn];
void dij(int u, int* D)
{
    std::queue<int> q;
    for (int i = 1; i <= n; ++i) vis[i] = 0, D[i] = a[u][i];
    D[u] = inf;
    for (int i = 1; i <= n; ++i)
        if (i != u) vis[i] = 1, q.push(i);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for (int i = 1; i <= n; ++i)
            if (D[i] > D[x] + a[x][i])
            {
                D[i] = D[x] + a[x][i];
                if (!vis[i]) vis[i] = 1, q.push(i);
            }
    }
}
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                scanf("%d", a[i] + j);
        dij(1, dis[0]), dij(n, dis[1]);
        printf("%d\n", std::min(dis[0][n], dis[0][1] + dis[1][n]));
    }
    return 0;
}