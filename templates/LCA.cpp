#include <algorithm>
#include <cstdio>
const int maxn = 1e6 + 100;

struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int n, m, s;

namespace LCA
{
// Heavy Light Chain Decomposition
int fa[maxn], siz[maxn], son[maxn], dep[maxn], top[maxn], dfn[maxn], id[maxn], ind;
void dfs1(int u)
{
    siz[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1, fa[v] = u, dfs1(v), siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    dfn[u] = ++ind, id[ind] = u;
    if (son[u]) top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v);
    }
}
int lca(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
int root;
void init()
{
    ind = siz[0] = 0;
    for (int i = 1; i <= n; ++i) fa[i] = siz[i] = son[i] = dep[i] = top[i] = dfn[i] = id[i] = 0;
    dep[root] = 1;
    dfs1(root);
    top[root] = root;
    dfs2(root);
}
}  // namespace LCA

int main()
{
    scanf("%d%d%d", &n, &m, &s);
    LCA::root = s;
    for (int i = 1, a, b; i < n; ++i) scanf("%d%d", &a, &b), add(a, b), add(b, a);
    LCA::init();
    while (m--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", LCA::lca(a, b));
    }
    return 0;
}