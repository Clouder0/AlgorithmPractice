#include <cstdio>
#include <cstring>
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
const int bufSize = 1000000;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
void read(T &r)
{
    static char c; r = 0;
    for (c = nc(); c > '9' || c < '0'; c = nc());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = nc());
}
const int maxn = 2e5 + 100;
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn], tot;
inline void add(const int &x, const int &y, const int &val) { E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot; }
const int inf = 1 << 30;
int n, k, root, treeSize, ans = inf;
int size[maxn], maxp[maxn], vis[maxn];
void getroot(int u, int fa)
{
    size[u] = 1, maxp[u] = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (vis[v] || v == fa) continue;
        getroot(v, u);
        size[u] += size[v];
        maxp[u] = max(maxp[u], size[v]);
    }
    maxp[u] = max(maxp[u], treeSize - size[u]);
    if (maxp[u] < maxp[root]) root = u;
}
int dis[maxn], d[maxn], rem[maxn], map[1001000];
void getdis(int u, int fa)
{
    if (dis[u] > k) return;
    rem[++rem[0]] = u;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (vis[v] || v == fa) continue;
        dis[v] = dis[u] + E[p].val, d[v] = d[u] + 1;
        getdis(v, u);
    }
}
void calc(int u)
{
    dis[u] = 0, d[u] = 0, rem[rem[0] = 1] = u, map[0] = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (vis[v]) continue;
        int t = rem[0];
        d[v] = 1, dis[v] = E[p].val, getdis(v, u);
        for (int i = t + 1; i <= rem[0]; ++i)
            ans = min(ans, map[k - dis[rem[i]]] + d[rem[i]]);
        for (int i = t + 1; i <= rem[0]; ++i)
            map[dis[rem[i]]] = min(map[dis[rem[i]]], d[rem[i]]);
    }
    for (int i = 1; i <= rem[0]; ++i) map[dis[rem[i]]] = inf;
}
void solve(int u)
{
    vis[u] = 1;
    calc(u);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (vis[v]) continue;
        treeSize = size[v], maxp[root = 0] = inf, getroot(v, u);
        solve(root);
    }
}
int main()
{
    read(n), read(k);
    for (int i = 1; i < n; ++i)
    {
        int a, b, c;
        read(a), read(b), read(c);
        ++a, ++b;
        add(a, b, c), add(b, a, c);
    }
    for (int i = 0; i <= k; ++i) map[i] = inf;
    treeSize = n, root = 1, getroot(1, 0);
    solve(root);
    if (ans >= n) puts("-1");
    else printf("%d", ans);
    return 0;
}