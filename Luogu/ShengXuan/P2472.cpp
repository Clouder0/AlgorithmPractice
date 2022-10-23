#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 1e4, maxm = 1e7;
struct node
{
    int to, next, cap;
} E[maxm];
int head[maxn], tot = 1;
inline void add(const int& x, const int& y, const int& cap)
{
    E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].cap = cap;
}
int d,n, m, s, t;
int inid[40][40],outid[40][40],cnt;
int dep[maxn], q[maxn], qt, qh, cur[maxn];
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
int h[40][40];
double dis(int x,int y,int a,int b)
{
    return sqrt((x - a) * (x - a) + (y - b) * (y - b));
}
int main()
{
    scanf("%d %d %d",&n,&m,&d);
    for (int i = 1; i <= n; ++i) for(int j = 1;j<=m;++j) inid[i][j] = ++cnt,outid[i][j] = ++cnt;
    s = ++cnt,t = ++cnt;
    for (int i = 1; i <= n; ++i) 
    {
        char s[40]; scanf("%s", s + 1);
        for (int j = 1; j <= m; ++j) h[i][j] = s[j] - 48;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (h[i][j])
            {
                add(inid[i][j], outid[i][j], h[i][j]), add(outid[i][j], inid[i][j], 0);
                if (i <= d || j <= d || i + d > n || j + d > m)
                    add(outid[i][j], t, 1 << 30), add(t, outid[i][j], 0);
            }
    int totalnum = 0;
    for (int i = 1; i <= n; ++i) 
    {
        char s[40]; scanf("%s", s + 1);
        for (int j = 1; j <= m; ++j)
            if (s[j] == 'L') 
            {
            add(::s, inid[i][j], 1), add(inid[i][j], ::s, 0),++totalnum;
            }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) if (h[i][j])
                for (int l = 1; l <= n; ++l)
                    for (int r = 1; r <= m; ++r)
                        if (h[l][r] && dis(i, j, l, r) <= d)
                            add(outid[i][j], inid[l][r], 1 << 30), add(inid[l][r], outid[i][j], 0);
    int res = 0;
    while(bfs()) res += dfs(s,1<<30);
    printf("%d\n",totalnum - res);
    return 0;
}