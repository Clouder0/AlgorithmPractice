#include <cstdio>
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c; r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 1e4 + 100;
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn], tot;
inline void add(const int &x, const int &y, const int &val) { E[++tot].to = y, E[tot].next = head[x], E[tot].val = val, head[x] = tot; }
int n, m, root, treeSize;
int size[maxn], maxp[maxn], vis[maxn];
void dfs1(int u, int fa)
{
    size[u] = 1, maxp[u] = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa || vis[v]) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (maxp[u] < size[v]) maxp[u] = size[v];
    }
    if (treeSize - size[u] > maxp[u]) maxp[u] = treeSize - size[u];
    if (maxp[u] < maxp[root]) root = u;
}
int query[110], ans[110];
int rem[maxn], dis[maxn];
int judge[10000100];
void getdis(int u, int fa)
{
    if (dis[u] > 10000000) return;
    rem[++rem[0]] = dis[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa || vis[v]) continue;
        dis[v] = dis[u] + E[p].val;
        getdis(v, u);
    }
}
int q[maxn], tail;
void calc(int u)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (vis[v]) continue;
        rem[0] = 0, dis[v] = E[p].val;
        getdis(v, u);
        for (int i = 1; i <= rem[0]; ++i)
            for (int j = 1; j <= m; ++j)
                if (query[j] >= rem[i])
                    ans[j] |= judge[query[j] - rem[i]];
        for (int i = 1; i <= rem[0]; ++i)
            q[++tail] = rem[i], judge[rem[i]] = 1;
    }
    while (tail)
        judge[q[tail--]] = 0;
}
void solve(int u)
{
    vis[u] = judge[0] = 1;
    calc(u);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (vis[v]) continue;
        treeSize = size[v], maxp[root = 0] = 1 << 30;
        dfs1(v, 0), solve(root);
    }
}
int main()
{
    read(n), read(m);
    for (int i = 1; i < n; ++i)
    {
        int a, b, c;
        read(a), read(b), read(c);
        add(a, b, c), add(b, a, c);
    }
    for (int i = 1; i <= m; ++i)
        read(query[i]);
    root = 1, maxp[root] = treeSize = n;
    dfs1(1, 0), solve(root);
    for (int i = 1; i <= m; ++i) puts(ans[i]?"AYE":"NAY");
    return 0;
}