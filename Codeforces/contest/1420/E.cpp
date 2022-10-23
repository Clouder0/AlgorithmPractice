#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 90,inf = 0x3f3f3f3f;
int n,a[maxn],f[maxn],fc,sum[maxn];
int dp[maxn][maxn][maxn * maxn];
int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) scanf("%d",a + i);
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i]) f[++fc] = cnt, cnt = 0; else ++cnt;
    f[++fc] = cnt;
    for (int i = 1; i <= fc; ++i) sum[i] = sum[i - 1] + f[i];
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = 0;
    int up = n * (n - 1) / 2,maxx = sum[fc];
    for (int i = 0; i < fc; ++i)
        for (int s = 0; s <= maxx; ++s)
            for (int opt = 0; opt <= up; ++opt)
                if(dp[i][s][opt] != inf)
                    for (int to = s, t, tt; to <= maxx; ++to)
                    {
                        t = opt + abs(to - sum[i + 1]);
                        if (t > up) continue;
                        tt = to - s, dp[i + 1][to][t] = min(dp[i + 1][to][t], dp[i][s][opt] + tt * tt);
                    }
    int ans = inf;
    for (int i = 0; i <= up; ++i) ans = min(ans, dp[fc][maxx][i]),printf("%d ",(maxx * maxx  - ans) / 2);
    return 0;
}