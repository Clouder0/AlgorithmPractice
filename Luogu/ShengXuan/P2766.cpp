#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn  = 1e4 + 100,maxm = 1e6;
int a[maxn];
int f[maxn];
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
    for (int i = 0; i <= 2 * n + 1; ++i) dep[i] = 0;
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
    scanf("%d", &n);
    if(n == 1) {printf("1\n1\n1");return 0;}
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) f[i] = 1;
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
            if (a[i] >= a[j]) f[i] = max(f[i], f[j] + 1);
    for (int i = 1; i <= n; ++i) ans = max(ans,f[i]);
    printf("%d\n",ans);
    s = 0,t = 2 * n + 1;
    for (int i = 1; i <= n; ++i) add(i,i + n,1),add(i + n,i,0);
    for (int i = 1; i <= n; ++i) if(f[i] == 1) add(s,i,1),add(i,s,0);
    for (int i = 1; i <= n; ++i) if(f[i] == ans) add(i + n,t,1),add(t,i + n,0);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
            if (a[i] >= a[j] && f[j] + 1 == f[i]) add(j + n, i, 1), add(i, j + n, 0);
    int res = 0;
    while(bfs()) res += dfs(s,inf);
    printf("%d\n",res);
    for (int i = 0; i <= 2 * n + 1; ++i)  head[i] = 0;
    tot = 1;
    for (int i = 2; i < n; ++i) add(i, i + n, 1), add(i + n, i, 0);
    add(1, 1 + n, inf), add(1 + n, 1, 0), add(n, n + n, inf), add(n + n, n, 0);
    add(s,1,inf),add(1,s,0);
    if(f[n] == ans) add(n + n,t,inf),add(t,n + n,0);
    for (int i = 1; i <= n; ++i) if (f[i] == 1) add(s, i, 1), add(i, s, 0);
    for (int i = 1; i <= n; ++i) if(f[i] == ans) add(i + n,t,1),add(t,i + n,0);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
            if (a[i] >= a[j] && f[j] + 1 == f[i]) add(j + n, i, 1), add(i, j + n, 0);
    res = 0;
    while(bfs()) res += dfs(s,inf);
    printf("%d\n",res);
    return 0;
}