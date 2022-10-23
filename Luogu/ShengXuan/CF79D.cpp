#include <cstdio>
#include <algorithm>
#include <cctype>
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100;
const int maxk = 22;
int n, k, l, x[maxn], a[maxn], d[maxn], p[maxn], cnt;
int dis[maxk][maxn], q[maxn], qt, qh, cost[maxk][maxk];
bool vis[maxn];
int f[1 << maxk];
int main()
{
    read(n), read(k), read(l);
    for (int i = 1; i <= k; ++i) read(x[i]), d[x[i]] ^= 1, d[x[i] + 1] ^= 1;
    for (int i = 1; i <= l; ++i) read(a[i]);
    for (int i = 1; i <= n + 1; ++i) if (d[i]) p[++cnt] = i;
    for (int t = 1; t <= cnt; ++t)
    {
        for (int i = 1; i <= n + 1; ++i) vis[i] = 0;
        q[qt = 1] = p[t], qh = 1, vis[p[t]] = 1;
        while (qt >= qh)
        {
            int u = q[qh++];
            for (int i = 1, v; i <= l; ++i)
            {
                v = u + a[i];
                if (v <= n + 1 && !vis[v]) vis[v] = 1, dis[t][v] = dis[t][u] + 1, q[++qt] = v;
                v = u - a[i];
                if (v > 0 && !vis[v]) vis[v] = 1, dis[t][v] = dis[t][u] + 1, q[++qt] = v;
            }
        }
        for (int i = 1; i <= n + 1; ++i) if (!vis[i]) dis[t][i] = 1 << 28;
    }
    for (int i = 1; i <= cnt; ++i) for (int j = 1; j <= cnt; ++j) cost[i][j] = dis[i][p[j]];
    int maxs = 1 << cnt;
    for (int i = 1; i < maxs; ++i) f[i] = 1 << 30;
    for (int i = 0; i < maxs; ++i) 
        for (int j = 0; j < cnt; ++j) for (int k = j + 1; k < cnt; ++k) if (((1 << j) & i) == 0 && ((1 << k) & i) == 0)
            f[i | (1 << j) | (1 << k)] = std::min(f[i | (1 << j) | (1 << k)], f[i] + cost[j + 1][k + 1]);
    if (f[maxs - 1] >= (1 << 28)) puts("-1");
    else printf("%d\n", f[maxs - 1]);
    return 0;
}