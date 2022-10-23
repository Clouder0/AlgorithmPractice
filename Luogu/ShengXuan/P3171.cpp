#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1e5, maxm = 1e6;
#define int long long
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
    for (int i = 1; i <= 2 * n; ++i) dep[i] = 0;
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
int dis[610][610];
int U[maxm],V[maxm],C[maxm];
const int inf = 1ll<<62;
signed main()
{
    scanf("%lld %lld",&n,&m);
    s = 1 + n,t = n;
    memset(dis,0x3f,sizeof(dis));
    for (int i = 1,a,b,c; i <= m; ++i) 
        scanf("%lld %lld %lld",&a,&b,&c),dis[a][b] = min(dis[a][b],c),dis[b][a] = min(dis[b][a],c),
        U[i] = a,V[i] = b,C[i] = c;
    for (int i = 1; i <= n; ++i) dis[i][i] = 0;
    for(int k = 1;k<=n;++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
    for (int i = 1, x; i <= n; ++i) scanf("%lld", &x), add(i, i + n, x), add(i + n, i, 0);
    for (int i = 1; i <= m; ++i) 
    {
        if (dis[1][U[i]] + dis[V[i]][n] + C[i] == dis[1][n])
            add(U[i] + n, V[i], inf), add(V[i], U[i] + n, 0);
        if (dis[1][V[i]] + dis[U[i]][n] + C[i] == dis[1][n])    
            add(V[i] + n, U[i], inf), add(U[i], V[i] + n, 0);            
    }
    int res = 0;
    while (bfs()) res += dfs(s, inf);
    printf("%lld\n", res);
    return 0;
}