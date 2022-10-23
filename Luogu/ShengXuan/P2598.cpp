#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e6, maxm = 1e7;
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
int id[110][110],cnt;
inline bool bfs()
{
    for (int i = 1; i <= cnt; ++i) dep[i] = 0;
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
int a[110][110];
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
const int inf = 1<<30;
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1; i <= n; ++i) for(int j = 1;j<=m;++j) id[i][j] = ++cnt;
    s = ++cnt,t = ++cnt;
    for (int i = 1; i <= n; ++i)  for(int j = 1;j<=m;++j) scanf("%d",a[i] + j);
    for (int i = 1; i <= n; ++i) for(int j = 1;j<=m;++j)
    {
        if (a[i][j] == 1) add(s, id[i][j], inf), add(id[i][j], s, 0);
        else if (a[i][j] == 2) add(id[i][j], t, inf), add(t, id[i][j], 0);
        for (int k = 0; k < 4; ++k)
        {
            int nx = i + dx[k], ny = j + dy[k];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            add(id[i][j], id[nx][ny], 1), add(id[nx][ny], id[i][j], 0);
        }
    }
    int res = 0;
    while(bfs()) res += dfs(s,inf);
    printf("%d\n",res);
    return 0;
}