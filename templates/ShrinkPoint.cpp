#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 1e4 + 100, maxm = 1e5 + 100;
struct node
{
    int from, to, next;
} E[maxm];
int head[maxn], tot;
inline void add(int x, int y) { E[++tot].next = head[x], head[x] = tot, E[tot].from = x, E[tot].to = y; }
int n, m, w[maxn], f[maxn], vis[maxn];
int dfn[maxn], low[maxn], ind, ins[maxn], s[maxn], top, bel[maxn], sccnum, sccw[maxn], in[maxn];
void tarjan(int u)
{
    dfn[u] = low[u] = ++ind;
    ins[u] = 1, s[++top] = u;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++sccnum;
        while (s[top] != u) ins[s[top]] = 0, bel[s[top--]] = sccnum;
        --top, ins[u] = 0, bel[u] = sccnum;
    }
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", w + i);
    for (int i = 1, a, b; i <= m; ++i) scanf("%d %d", &a, &b), add(a, b);
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);
    tot = 0;
    for (int i = 1; i <= sccnum; ++i) head[i] = 0;
    for (int i = 1; i <= m; ++i)
    {
        int u = E[i].from, v = E[i].to;
        if (bel[u] == bel[v]) continue;
        add(bel[u], bel[v]), in[bel[v]]++;
    }
    static int q[maxn], qt = 0, qh = 1;
    for (int i = 1; i <= n; ++i) sccw[bel[i]] += w[i];
    for (int i = 1; i <= sccnum; ++i)
        if (!in[i]) q[++qt] = i;
    int res = 0;
    while (qt >= qh)
    {
        int u = q[qh++];
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            f[v] = max(f[u] + sccw[u], f[v]);
            if (--in[v] == 0) q[++qt] = v;
        }
        res = max(res, f[u] + sccw[u]);
    }
    printf("%d\n", res);
    return 0;
}