#include <algorithm>
#include <cstdio>
const int maxn = 1e6 + 10;
#define int long long
int fa[maxn], d[maxn];
int n, m, ans;
int find(int x)
{
    if (fa[x] == x) return x;
    int f = fa[x];
    fa[x] = find(fa[x]);
    d[x] += d[f];
    return fa[x];
}
void unite(int a, int b, int dis)
{
    int ffa = find(a), ffb = find(b);
    if (ffa == ffb)
    {
        ans += ((d[a] - d[b]) != dis);
        return;
    }
    if (ffa > ffb) std::swap(a, b), std::swap(ffa, ffb), dis = -dis;
    fa[ffa] = ffb;
    d[ffa] = dis - d[a] + d[b];
}
signed main()
{
    while (~scanf("%lld%lld", &n, &m))
    {
        for (int i = 1; i <= n + 1; ++i) fa[i] = i, d[i] = 0;
        ans = 0;
        while (m--)
        {
            int a, b, c;
            scanf("%lld%lld%lld", &a, &b, &c);
            unite(a, b + 1, c);
            // puts("");
            // for (int i = 1; i <= n + 1; ++i) printf("fa[%lld]=%lld d[%lld]=%lld\n", i, fa[i], i, d[i]);
            // puts("");
        }
        printf("%lld\n", ans);
    }
    return 0;
}