#include <cstdio>
#include <queue>
template <typename T>
inline T min(const T& a, const T& b) { return a < b ? a : b; }
#define ll long long
const int maxn = 1e4 + 100, maxm = 2e4 + 100;
int n, m, S, T;
struct node
{
    int to, next, val;
} E[maxm];
int cur[maxn], head[maxn], tot = 1;
inline void add(const int& x, const int& y, const int& v)
{
    E[++tot].to = y, E[tot].next = head[x], E[tot].val = v, head[x] = tot;
}
int dep[maxn], q[maxn], qt, qh;
inline bool BFS()
{
    for (int i = 1; i <= n; ++i) dep[i] = 0;
    qh = 1, q[qt = 1] = S, cur[S] = head[S], dep[S] = 1;
    while (qt >= qh)
    {
        int u = q[qh++];
        if (u == T) return 1;
        for (int p = head[u], v; p; p = E[p].next)
            if (E[p].val && !dep[v = E[p].to])
                cur[v] = head[v], dep[v] = dep[u] + 1, q[++qt] = v;
    }
    return 0;
}
ll dfs(int u, ll flow)
{
    if (u == T || !flow) return flow;
    ll sumflow = 0, vflow;
    for (int& p = cur[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (dep[v] == dep[u] + 1 && E[p].val && (vflow = dfs(v, min(flow, 1ll * E[p].val))) > 0)
        {
            E[p].val -= vflow, E[p ^ 1].val += vflow, sumflow += vflow, flow -= vflow;
            if (flow == 0) break;
        }
    }
    return sumflow;
}
int main()
{
    scanf("%d %d %d %d", &n, &m, &S, &T);
    for (int i = 1, x, y, z; i <= m; ++i) scanf("%d %d %d", &x, &y, &z), add(x, y, z), add(y, x, 0);
    ll ans = 0;
    while (BFS()) ans += dfs(S, 1ll << 60);
    printf("%lld\n", ans);
    return 0;
}