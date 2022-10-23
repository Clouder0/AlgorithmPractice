#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define int long long
template <typename T>
inline void swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 251000;
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x, const int &y, const int &val)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    E[tot].val = val;
    head[x] = tot;
}
int n, m;
int f[maxn];
namespace Decomposition
{
    int dep[maxn], fa[maxn], size[maxn], son[maxn];
    void dfs1(int u)
    {
        size[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (v == fa[u]) continue;
            fa[v] = u, dep[v] = dep[u] + 1;
            f[v] = min(f[u], E[p].val);
            dfs1(v);
            size[u] += size[v];
            if (size[son[u]] < size[v]) son[u] = v;
        }
    }
    int top[maxn], dfn[maxn], time;
    void dfs2(int u, int topf)
    {
        top[u] = topf, dfn[u] = ++time;
        if (!son[u]) return;
        dfs2(son[u], topf);
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }
    int lca(int x, int y)
    {
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            x = fa[top[x]];
        }
        return dep[x] < dep[y] ? x : y;
    }
} // namespace Decomposition
int s[maxn], top;
int is[maxn];
std::vector<int> V[maxn];
const bool cmp(const int &a, const int &b)
{
    return Decomposition::dfn[a] < Decomposition::dfn[b];
}
inline void addE(int x, int y)
{
    V[x].push_back(y), V[y].push_back(x);
}
inline void push(int x)
{
    if (top == 1)
    {
        s[++top] = x;
        return;
    }
    int lca = Decomposition::lca(x, s[top]);
    if (lca == s[top])
        return;
    while (top > 1 && Decomposition::dfn[s[top - 1]] >= Decomposition::dfn[lca])
        V[s[top - 1]].push_back(s[top]),--top;
    if (s[top] != lca)
        V[lca].push_back(s[top]),s[top] = lca;
    s[++top] = x;
}
int dp(int u)
{
    if (V[u].size() == 0)
        return f[u];
    int t = 0;
    for (std::vector<int>::iterator it = V[u].begin(); it != V[u].end(); ++it)
        t += dp(*it);
    V[u].clear();
    return min(f[u], t);
}
signed main()
{
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u);
        read(v);
        read(w);
        add(u, v, w);
        add(v, u, w);
    }
    f[1] = 1ll << 60;
    Decomposition::dep[1] = 1;
    Decomposition::dfs1(1);
    Decomposition::dfs2(1, 1);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int k;
        read(k);
        for (int j = 1; j <= k; ++j)
            read(is[j]);
        std::sort(is + 1, is + 1 + k, cmp);
        s[top = 1] = 1;
        for (int j = 1; j <= k; ++j)
            push(is[j]);
        while (top)
            V[s[top-1]].push_back(s[top]),--top;
        printf("%lld\n", dp(1));
    }
    return 0;
}