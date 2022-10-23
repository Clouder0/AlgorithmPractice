#include <algorithm>
#include <cstdio>
#define int long long
const int maxn = 1e5 + 100, maxm = 4e4 + 100;
int n, W;
int v[maxn], w[maxn], num[maxn];
int f[2][maxm];
int q[maxn], id[maxn], qh, qt;
signed main()
{
    scanf("%lld%lld", &n, &W);
    for (int i = 1; i <= n; ++i) scanf("%lld%lld%lld", v + i, w + i, num + i);
    int now = 0, last = 1;
    for (int i = 1; i <= W; ++i) f[last][i] = -(1ll << 60);
    f[last][0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < w[i]; ++j)
        {
            qh = 1, qt = 0;
            for (int k = 0; j + k * w[i] <= W; ++k)
            {
                while (qt >= qh && k - id[qh] > num[i]) ++qh;
                int ins = f[last][j + k * w[i]] - k * v[i];
                while (qt >= qh && q[qt] < ins) --qt;
                q[++qt] = ins, id[qt] = k;
                f[now][j + k * w[i]] = q[qh] + k * v[i];
            }
        }

        last ^= 1, now ^= 1;
    }
    int maxx = 0;
    for (int i = 0; i <= W; ++i) maxx = std::max(f[last][i], maxx);
    printf("%lld\n", maxx);
    return 0;
}
