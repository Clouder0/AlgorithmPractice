#include <algorithm>
#include <cstdio>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 2e5 + 100;
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y, const int& val)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot;
}
const int inf = 1 << 30;
int n, f[maxn][2], g[maxn], maxson[maxn], maxx[maxn], secx[maxn];
void dfs(int u, int fa)
{
    maxx[u] = secx[u] = -inf;
    for (int p = head[u], v; p; p = E[p].next) if ((v = E[p].to) != fa) dfs(v, u), f[u][0] += max(f[v][0], f[v][1] + E[p].val);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        int t = f[v][0] + E[p].val - max(f[v][0], f[v][1] + E[p].val);
        if (t >= maxx[u]) secx[u] = maxx[u], maxx[u] = t, maxson[u] = v;
        else if (t > secx[u]) secx[u] = t;
    }
    f[u][1] = f[u][0] + maxx[u];
}
void dfs2(int u, int fa)
{
    for (int p = head[u], t0, t1, maxt, t; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        t0 = g[u] - max(f[v][0], f[v][1] + E[p].val);    // f[u][0] as u is root, except sub-tree v
        t1 = t0 + (maxson[u] != v ? maxx[u] : secx[u]);  // f[u][1] as u is root,except sub-tree v
        maxt = max(t0, t1 + E[p].val);                   //just a frequently used variable
        t = t0 + E[p].val - maxt;
        if (t >= maxx[v]) secx[v] = maxx[v], maxx[v] = t, maxson[v] = u;
        else if (t > secx[v]) secx[v] = t;
        g[v] = f[v][0] + maxt;
        dfs2(v, u);
    }
}
int main()
{
    read(n);
    for (int i = 1, a, b, c; i < n; ++i) read(a), read(b), read(c), add(a, b, c), add(b, a, c);
    dfs(1, 0), g[1] = f[1][0], dfs2(1, 0);
    int ans = -inf;
    for (int i = 1; i <= n; ++i) ans = max(ans, g[i]);
    printf("%d\n", ans);
    return 0;
}