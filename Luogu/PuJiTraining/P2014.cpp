#include <cstdio>
#include <algorithm>
const int maxn = 310;
struct node
{
    int next, to;
} E[maxn << 1];
int head[maxn], cnt;
inline void add(const int& u, const int& v)
{
    E[++cnt].next = head[u], head[u] = cnt, E[cnt].to = v;
}
int n, m, fa[maxn], siz[maxn], v[maxn], f[maxn][maxn];
void dfs(int u)
{
    siz[u] = 1, f[u][1] = v[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        fa[v] = u, dfs(v);
        for (int i = std::min(m, siz[u]); i; --i)
            for (int j = 1; j <= siz[v] && j <= m; ++j)
                f[u][i + j] = std::max(f[u][i + j], f[u][i] + f[v][j]);
        siz[u] += siz[v];
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d%d", fa + i, v + i), add(fa[i], i);
    dfs(0);
    int maxx = 0;
    for (int i = 0; i <= m + 1; ++i) maxx = std::max(maxx, f[0][i]);
    printf("%d\n", maxx);
    return 0;
}