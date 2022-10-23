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
int k,cant[210][210],put[210][210],rel[210][210],cnt;
int dx[8] = {-1, -1, -3, -3, +1, +1, +3, +3};
int dy[8] = {-3, -3, -1, -1, +3, +3, +1, +1};
int main()
{
    scanf("%d %d %d",&n,&m,&k);
    for (int i = 1, x, y; i <= k; ++i) scanf("%d %d", &x, &y), cant[x][y] = 1;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) put[i][j] = ++cnt;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) rel[i][j] = ++cnt;
    s = ++cnt, t = ++cnt;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            for (int k = 0; k < 8; ++k)
            {
                int nx = i + dx[k],ny = j + dy[k];
                if(nx < 0 || nx > n || ny < 0 || ny > m) continue;
                add(id[i][j],id[nx][ny],inf),add(id[nx][ny],id[i][j],0);
            }
        }
    return 0;
}