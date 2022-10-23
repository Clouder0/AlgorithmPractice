#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 1e6, maxm = 1e6;
struct node
{
    int to, next, cap;
} E[maxm];
int head[maxn], tot = 1;
inline void add(const int& x, const int& y, const int& cap)
{
    E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].cap = cap;
}
int m, s, t;
int n1, n2, n3;
int dep[maxn], q[maxn], qt, qh, cur[maxn];
inline bool bfs()
{
    for (int i = 1; i <= n1 + 2 * n2 + n3 + 1; ++i) dep[i] = 0;
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
            if (!vflow) dep[v] = 0;
            if (!flow) break;
        }
    return sumflow;
}
int main()
{
    scanf("%d %d %d", &n1, &n2, &n3);
    s = 0, t = n1 + 2 * n2 + n3 + 1;
    for (int i = 1; i <= n1; ++i) add(s, i, 1), add(i, s, 0);
    for (int i = 1; i <= n3; ++i) add(n1 + 2 * n2 + i, t, 1), add(t, n1 + 2 * n2 + i, 0);
    for (int i = 1; i <= n2; ++i) add(n1 + i, n1 + i + n2, 1), add(n1 + i + n2, n1 + i, 0);
    scanf("%d", &m);
    for (int i = 1, a, b; i <= m; ++i)
        scanf("%d %d", &a, &b), add(b, n1 + a, 1), add(n1 + a, b, 0);
    scanf("%d", &m);
    for (int i = 1, a, b; i <= m; ++i)
        scanf("%d %d", &a, &b), add(n1 + n2 + a, n1 + 2 * n2 + b, 1), add(n1 + 2 * n2 + b, n1 + n2 + a, 0);
    int res = 0;
    while (bfs()) res += dfs(s, 1 << 30);
    printf("%d\n", res);
    return 0;
}