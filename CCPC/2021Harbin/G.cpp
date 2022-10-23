#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <queue>
using namespace std;
#define int long long
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc())
        ;
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e5 + 100;
struct node
{
    int to, next, w;
} E[maxn];
int head[maxn];
inline void add(const int& x, const int& y, const int& w)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot, E[tot].w = w;
}
int T, R, n, m, k, a[maxn];
int d[19][maxn], vis[maxn];
void dij(int s, int dis[])
{
    for (int i = 1; i <= n; ++i) vis[i] = 0, dis[i] = 1ll << 60;
    dis[s] = 0;
    priority_queue<pair<int, int>> q;
    q.push(make_pair(-dis[s], s));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (dis[v] > dis[u] + E[p].w)
            {
                dis[v] = dis[u] + E[p].w;
                q.push(make_pair(-dis[v], v));
            }
        }
    }
}
long double f[1 << 19][19], p[20], P[1 << 19];
long double dfs(int S, int u)
{
    if (f[S][u] > 0.00000001) return f[S][u];
    long double minn = 1.0 * d[u][n] / T;
    for (int i = 1; i <= k; ++i)
        if ((((1 << (i - 1))) & S) == 0)
        {
            minn = min(minn, 1.0 * d[u][a[i]] / T + dfs(S | (1 << (i - 1)), i));
        }
    f[S][u] = (1.0 - p[u]) * d[u][n] / R + p[u] * minn;
    return f[S][u];
}
signed main()
{
    read(T), read(R);
    read(n), read(m);
    for (int i = 1, u, v, w; i <= m; ++i) read(u), read(v), read(w), add(u, v, w), add(v, u, w);
    read(k);
    for (int i = 1, t; i <= k; ++i) read(a[i]), read(t), p[i] = t / 100.0;
    dij(1, d[0]);
    for (int i = 1; i <= k; ++i) dij(a[i], d[i]);
    if (d[0][n] > 1e10) return puts("-1"), 0;
    long double res = 1.0 * d[0][n] / T;
    for (int i = 1; i <= k; ++i) res = min(res, dfs(1 << (i - 1), i) + 1.0 * d[0][a[i]] / T);
    printf("%.6Lf\n", res);
    return 0;
}