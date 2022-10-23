#include <algorithm>
#include <cstdio>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
#define int long long
inline char nc()
{
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
const int maxn = 510, maxm = 1e5;
struct node
{
    int to, next, cap;
} E[maxm];
int head[maxn], tot = 1;
inline void add(int x, int y, int cap)
{
    E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].cap = cap;
    E[++tot].next = head[y], head[y] = tot, E[tot].to = x, E[tot].cap = 0;
}
int n, m, w[maxn];
int s, t, id[maxn][maxn], cnt, dep[maxn], cur[maxn];
int q[maxn], qt, qh;
bool bfs()
{
    for (int i = 1; i <= cnt; ++i) dep[i] = 0, cur[i] = head[i];
    qh = 1, q[qt = 1] = s, dep[s] = 1;
    while (qt >= qh)
    {
        int u = q[qh++];
        if (u == t) return 1;
        for (int p = head[u], v; p; p = E[p].next) 
            if (!dep[v = E[p].to] && E[p].cap) dep[v] = dep[u] + 1, q[++qt] = v;
    }
    return 0;
}
int dfs(int u, int flow)
{
    if (u == t || !flow) return flow;
    int sumflow = 0;
    for (int &p = cur[u], v, vflow; p; p = E[p].next)
        if (dep[v = E[p].to] == dep[u] + 1 && E[p].cap && (vflow = dfs(v, min(E[p].cap, flow))))
        {
            E[p].cap -= vflow, E[p ^ 1].cap += vflow, sumflow += vflow, flow -= vflow;
            if (flow == 0) break;
        }
    return sumflow;
}
const int inf = 1ll << 60;
const int big = 4e11;
bool vis[maxn];
void dfs2(int u)
{
    vis[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (!vis[v] && E[p].cap > 0) dfs2(v);
    }
}
signed main()
{
    read(n), read(m);
    s = ++cnt, t = ++cnt;
    for (int i = 1; i <= n; ++i) for (int j = 0; j <= n; ++j) id[i][j] = ++cnt;
    for (int i = 1, a, b, c; i <= m; ++i)
    {
        read(a), read(b), read(c), w[a] += c, w[b] -= c;
        for (int j = 0; j < n; ++j) add(id[b][j], id[a][j + 1], inf);
    }
    for (int i = 1; i <= n; ++i)
    {
        add(s, id[i][0], inf), add(id[i][n], t, inf);
        for (int j = 0; j < n; ++j) add(id[i][j], id[i][j + 1], w[i] * j + big);
    }
    while (bfs()) dfs(s, inf);
    dfs2(s);
    for (int i = 1; i <= n; ++i)
    {
        int ans = 0;
        for (int j = 0; j <= n; ++j) if (vis[id[i][j]]) ans = j;
        printf("%lld ", ans);
    }
    return 0;
}