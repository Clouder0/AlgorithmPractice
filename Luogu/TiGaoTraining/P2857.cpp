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
    for (int i = 1; i <= n + m + 2; ++i) dep[i] = 0;
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
int like[maxn][30],siz[30];
inline bool check(int x)
{
    for (int k = 1; k + x - 1 <= m; ++k)
    {
        for (int i = 1; i <= n + m + 2; ++i) head[i] = 0;
        tot = 1;
        for (int i = 1; i <= n; ++i) add(s, i, 1), add(i, s, 0);
        for (int i = 1; i <= m; ++i) add(n + i, t, siz[i]), add(t, n + i, 0);
        for (int i = 1; i <= n; ++i)
            for (int j = k; j <= k + x - 1; ++j)
                add(i, n + like[i][j], 1), add(n + like[i][j], i, 0);
        int res = 0;
        while (bfs()) res += dfs(s, 1 << 30);
        if(res == n) return 1;
    }
    return 0;
}
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) scanf("%d", like[i] + j);
    s = n + m + 1,t = n + m + 2;
    for (int i = 1; i <= m; ++i) scanf("%d",siz + i);
    int l = 1, r = m, mid, ans = m;
    while (l <= r)
    {
        mid = l + r >> 1;
        if(check(mid)) ans = mid,r = mid - 1;
        else l = mid + 1;
    }
    printf("%d\n",ans);
    return 0;
}