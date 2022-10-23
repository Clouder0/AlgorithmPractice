#include <stdio.h>
#include <memory.h>
#include <math.h>
using namespace std;
const int maxn = 16;
double x[maxn], y[maxn];
double dis[maxn][maxn];
double dp[maxn][1 << maxn]; //dp[i][j]最后在i点，到达状态为j的时候到起点的最短距离。
int n;
double ans = 1e9;
double dfs(int v, int status)
{
    if(dp[v][status] != -1)
        return dp[v][status];
    if(status == 1<<(v-1))
        return dp[v][status] = dis[0][v];
    double minn = 1e9;
    for (int u = 1; u <= n; ++u)
    {
        if(u == v)
            continue;
        if((status&(1<<(u-1))) == 0)
            continue;
        double res = dfs(u,status^(1<<(v-1))) + dis[u][v];
        if(res < minn)
            minn = res;
    }
    return dp[v][status] = minn;
}
int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i)
        scanf("%lf %lf", x + i, y + i);
    for (int i = 0; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            dis[i][j] = dis[j][i] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j < (1 << n); ++j)
            dp[i][j] = -1;
    double t;
    for(int i = 1;i<=n;++i)
        if((t = dfs(i,(1<<n)-1)) < ans)
            ans = t;
    printf("%.2lf", ans);
    return 0;
}