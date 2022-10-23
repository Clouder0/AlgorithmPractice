#include <algorithm>
#include <cstdio>
const int maxn = 1e5 + 100;
const int mod = 1e9 + 7;
int n, k, c[maxn];
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void addE(int x, int y) { E[++tot].to = y, E[tot].next = head[x], head[x] = tot; }
inline int add(int x, int y)
{
    int res = x + y;
    return res >= mod ? res - mod : res;
}
inline int mul(int x, int y) { return 1ll * x * y % mod; }
int f[maxn][4];
void dfs(int u, int fa)
{
    if (c[u]) f[u][c[u]] = 1;
    else f[u][1] = f[u][2] = f[u][3] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs(v, u);
        f[u][1] = mul(f[u][1], add(f[v][2], f[v][3]));
        f[u][2] = mul(f[u][2], add(f[v][1], f[v][3]));
        f[u][3] = mul(f[u][3], add(f[v][1], f[v][2]));
    }
}
int main()
{
    scanf("%d %d", &n, &k);
    for (int i = 1, u, v; i < n; ++i) scanf("%d %d", &u, &v), addE(u, v), addE(v, u);
    for (int i = 1, x; i <= k; ++i) scanf("%d", &x), scanf("%d", c + x);
    dfs(1, 0);
    printf("%d\n", add(f[1][1], add(f[1][2], f[1][3])));
    return 0;
}
