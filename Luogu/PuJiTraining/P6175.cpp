#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 110;
int n,m;
int val[maxn][maxn],dis[maxn][maxn];
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1; i <= n; ++i) for(int j = 1;j<=n;++j) val[i][j] = dis[i][j] = 1<<29;
    while(m--)
    {
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        dis[u][v] = val[u][v] = min(val[u][v],w);
        dis[v][u] = val[v][u] = min(val[u][v],w);
    }
    int ans = 1 << 29;
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i < k; ++i)
            for (int j = i + 1; j < k; ++j) ans = min(ans, dis[i][j] + val[i][k] + val[k][j]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
    if (ans == 1 << 29) puts("No solution.");
    else printf("%d\n", ans);
    return 0;
}