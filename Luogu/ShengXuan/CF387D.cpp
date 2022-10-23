#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1e3 + 100,maxm = 1e4;
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
    for (int i = 0; i <= n * 2 + 1; ++i) dep[i] = 0;
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
int U[maxm],V[maxm];
int touch[maxn][maxn];
int main()
{
    scanf("%d %d",&n,&m);
    s = 0, t = n * 2 + 1;
    for (int i = 1; i <= m; ++i) scanf("%d %d",U + i,V + i),touch[U[i]][V[i]] = 1;
    int ans = 1<<30;
    for (int S = 1; S <= n; ++S) 
    {
        tot = 1;
        for (int i = 0; i <= 2 * n + 1; ++i) head[i] = 0;
        for (int i = 1; i <= n; ++i) add(s,i,1),add(i,s,0);
        for (int i = 1; i <= n; ++i) add(i + n,t,1),add(t,i + n,0);
        int all = 0;
        for (int i = 1; i <= m; ++i)
            if (U[i] != S && V[i] != S) add(U[i], V[i] + n, 1), add(V[i] + n, U[i], 0), ++all;
        for (int i = 1; i <= n; ++i) all += !touch[i][S] + !touch[S][i];
        if(!touch[S][S]) --all;
        int tmp = 0;
        while(bfs()) tmp += dfs(s,1<<30);
        ans = std::min(ans,n - tmp + all - 1 - tmp);
    }
    printf("%d\n",ans);
    return 0;
}