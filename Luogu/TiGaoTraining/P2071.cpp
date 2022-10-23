#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e4, maxm = 1e5;
struct node
{
    int to, next, cap;
} E[maxm];
int head[maxn], tot = 1;
inline void add(const int& x, const int& y, const int& cap)
{
    E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].cap = cap;
}
int n, m, s, t;
int dep[maxn], q[maxn], qt, qh, cur[maxn];
inline bool bfs()
{
    for (int i = 1; i <= n; ++i) dep[i] = 0;
    dep[s] = 1, cur[s] = head[s], qh = 1, q[qt = 1] = s;
    while (qt >= qh)
    {
        int u = q[qh++];
        if (u == t) return 1;
        for (int p = head[u], v; p; p = E[p].next)
            if (E[p].cap && !dep[v = E[p].to]) dep[v] = dep[u] + 1, cur[v] = head[v], q[++qt] = v;
    }
    return 0;
}
int dfs(int u, int flow)
{
    if (u == t || !flow) return flow;
    int sumflow = 0;
    for (int &p = cur[u], v, vflow; p; p = E[p].next)
        if (dep[v = E[p].to] == dep[u] + 1 && (vflow = dfs(v, min(E[p].cap, flow))))
        {
            flow -= vflow, sumflow += vflow, E[p].cap -= vflow, E[p ^ 1].cap += vflow;
            if(!vflow) dep[v] = 0;
            if (!flow) break;
        }
    return sumflow;
}
const int inf = 1<<30;
int main()
{
    scanf("%d",&n);
    s = 3 * n + 1,t = 3 * n + 2;
    for (int i = 1; i <= n * 2; ++i) add(s, i, 1), add(i, s, 0);
    for (int i = 2 * n + 1; i <= 3 * n; ++i) add(i, t, 2), add(t, i, 0);
    for (int i = 1, x, y; i <= n * 2; ++i)
    {
        scanf("%d %d", &x, &y), x += 2 * n, y += 2 * n;
        add(i, x, 1), add(x, i, 0), add(i, y, 1), add(y, i, 0);
    }
    n = n * 3 + 2;
    int ans = 0;
    while(bfs()) ans += dfs(s,inf);
    printf("%d\n",ans);
    return 0;
}