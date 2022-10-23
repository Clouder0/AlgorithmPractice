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
int a[50][50],inid[50][50],outid[50][50],cnt;
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
const int inf = 1 << 30;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1; i <= n; ++i) for(int j = 1;j<=m;++j) inid[i][j] = ++cnt,outid[i][j] = ++cnt;
    s = ++cnt,t = ++cnt;
    for (int i = 1; i <= n; ++i)
        for (int j = 1, x; j <= m; ++j)
        {
            scanf("%d", &x);
            if (x == 0) add(s, inid[i][j], inf), add(inid[i][j], s, 0), add(inid[i][j], outid[i][j], inf), add(outid[i][j], inid[i][j], 0);
            else if (x != -1) add(inid[i][j], outid[i][j], x), add(outid[i][j], inid[i][j], 0);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 0; k < 4; ++k)
            {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
                add(outid[i][j], inid[nx][ny], inf), add(inid[nx][ny], outid[i][j], 0);
            }
    for (int i = 1; i <= n; ++i) add(outid[i][1], t, inf), add(t, outid[i][1], 0), add(outid[i][m], t, inf), add(t, outid[i][m], 0);
    for (int i = 1; i <= m; ++i) add(outid[1][i], t, inf), add(t, outid[1][i], 0), add(outid[n][i], t, inf), add(t, outid[n][i], 0);
    int res = 0;
    while(bfs()) res += dfs(s,inf);
    printf("%d\n",res);
    return 0;
}