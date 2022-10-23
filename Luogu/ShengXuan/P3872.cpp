#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000, maxm = 5200;
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
    for (int i = 1; i <= n + 2; ++i) dep[i] = 0;
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
int main()
{
    scanf("%d %d",&n,&m);
    s = n + 1 ,t = n + 2;
    int res = 0;
    for (int i = 1,x; i <= n; ++i)
    {
        scanf("%d", &x);
        if (x >= 0) add(s, i, x), add(i, s, 0),res += x;
        else add(i, t, -x), add(t, i, 0);
    }
    for (int i = 1,a,b,c; i <= m; ++i) scanf("%d %d %d",&a,&b,&c),add(a,b,c),add(b,a,0);
    while(bfs()) res -= dfs(s,1<<30);
    printf("%d\n",res);
    return 0;
}