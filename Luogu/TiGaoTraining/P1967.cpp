#include <cstdio>
#include <algorithm>
#include <cstring>
const int maxn = 1e4 + 10;
const int maxm = 5e4 + 10;
int head[maxn], cnt, fa[maxn], w[maxn], dep[maxn];
struct node
{
    int u, v, w;
} E[maxm];
bool cmp(const node& a, const node& b) { return a.w > b.w; }
int n, m, q, bel[maxn],vis[maxn];
int find(int x) { return bel[x] == x ? x : bel[x] = find(bel[x]); }
inline void unite(int a, int b) { bel[find(b)] = find(a); }
struct edge
{
    int to,next, val;
}G[maxm];
inline void add(int u, int v, int w) { G[++cnt].next = head[u], head[u] = cnt, G[cnt].to = v, G[cnt].val = w; }
void dfs(int u)
{
    vis[u] = 1;
    for (int p = head[u]; p; p = G[p].next)
    {
        int v = G[p].to;
        if (v == fa[u]) continue;
        if(vis[v]) continue;
        dep[v] = dep[u] + 1, w[v] = G[p].val, fa[v] = u, dfs(v);
    }
}
int minn[maxn][21], anc[maxn][21];
int ask(int a, int b)
{
    if(find(a) != find(b)) return -1;
    if(dep[a] < dep[b]) std::swap(a,b);
    int res = 1 << 30;
    for (int i = 20; i >= 0; --i)
        if (dep[anc[a][i]] >= dep[b])
            res = std::min(res, minn[a][i]), a = anc[a][i];
    if(a == b) return res;
    for (int i = 20; i >= 0; --i)
        if (anc[a][i] != anc[b][i])
            res = std::min(res, std::min(minn[a][i], minn[b][i])), a = anc[a][i], b = anc[b][i];
    res = std::min(res, std::min(minn[a][0], minn[b][0]));
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);
    std::sort(E + 1, E + 1 + m, cmp);
    for (int i = 1; i <= n; ++i) bel[i] = i;
    for (int i = 1; i <= m; ++i)
        if (find(E[i].u) != find(E[i].v)) unite(E[i].u, E[i].v), add(E[i].u, E[i].v, E[i].w), add(E[i].v, E[i].u, E[i].w);
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) dep[i] = 1, w[i] = 1 << 30, dfs(i);
    std::memset(minn, 0x3f, sizeof(minn));
    for (int i = 1; i <= n; ++i) minn[i][0] = w[i], anc[i][0] = fa[i];
    for (int k = 1; (1 << k) <= n; ++k)
        for (int i = 1; i <= n; ++i)
        {
            anc[i][k] = anc[anc[i][k - 1]][k - 1];
            minn[i][k] = std::min(minn[i][k - 1], minn[anc[i][k - 1]][k - 1]);
        }
    scanf("%d",&q);
    for (int i = 1; i <= q; ++i)
    {
        int x, y, res = 1 << 30;
        scanf("%d%d", &x, &y);
        printf("%d\n",ask(x,y));
    }
    return 0;
}