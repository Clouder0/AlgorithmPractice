#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 2e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y; }
int n, size[maxn];
long long f[maxn], g[maxn], k[maxn];
void dfs1(int u, int fa)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs1(v, u), size[u] += size[v], f[u] += f[v];
    }
    f[u] += size[u];
}
void dfs2(int u, int fa)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        k[u] = g[u] - f[v] - n + n - size[v];
        g[v] = f[v] + k[u] - size[v] + n;
        dfs2(v, u);
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i) scanf("%d%d", &u, &v), add(u, v), add(v, u);
    dfs1(1, 0), g[1] = f[1], dfs2(1, 0);
    long long maxx = 0;
    for (int i = 1; i <= n; ++i) maxx = std::max(maxx, g[i]);
    printf("%lld\n", maxx);
    return 0;
}
