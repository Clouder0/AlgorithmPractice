#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5, maxm = 1e7;
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
inline bool BFS()
{
    for (int i = 0; i <= n; ++i) dep[i] = 0;
    qh = 1, q[qt = 1] = s, cur[s] = head[s], dep[s] = 1;
    while (qt >= qh)
    {
        int u = q[qh++];
        if (u == t) return 1;
        for (int p = head[u], v; p; p = E[p].next)
            if (E[p].cap && !dep[v = E[p].to])
                cur[v] = head[v], dep[v] = dep[u] + 1, q[++qt] = v;
    }
    return 0;
}
int dfs(int u, int flow)
{
    if (u == t || !flow) return flow;
    int sumflow = 0,vflow;
    for (int& p = cur[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (dep[v] == dep[u] + 1 && E[p].cap && (vflow = dfs(v, min(flow, E[p].cap))) > 0)
        {
            E[p].cap -= vflow, E[p ^ 1].cap += vflow, sumflow += vflow, flow -= vflow;
            if (flow == 0) break;
        }
    }
    return sumflow;
}
int sum;
const int inf = 1<<30;
int main()
{
    scanf("%d",&n);
    s = n + 1,t = n + 2;
    for (int i = 1,x; i <= n; ++i) scanf("%d", &x), add(s, i, x), add(i, s, 0),sum += x;
    for (int i = 1,x; i <= n; ++i) scanf("%d", &x), add(i, t, x), add(t, i, 0),sum += x;
    scanf("%d",&m);
    for (int i = 1,c1,c2,k,x; i <= m; ++i) 
    {
        scanf("%d %d %d",&k,&c1,&c2);
        sum += c1 + c2;
        int s1 = n + i + 2;
        int t1 = s1 + m;
        add(s,s1,c1),add(s1,s,0);
        add(t1,t,c2),add(t,t1,0);
        while (k--) scanf("%d", &x), add(s1, x, inf), add(x, s1, 0), add(x, t1, inf), add(t1, x, 0);
    }
    n = n + 2 + m * 2;
    int ans = 0, t;
    while (BFS()) ans += dfs(s, inf);
    printf("%d\n",sum - ans);
    return 0;
}