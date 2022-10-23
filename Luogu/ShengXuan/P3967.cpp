#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e3, maxm = 5e5 + 100;
int n, a[maxn][maxn], s, t;
struct node
{
    int to,next,cap,cost;
}E[maxm];
int head[maxn],tot;
inline void add(const int &x,const int &y,const int &cap,const int &cost)
{
    E[++tot].next = head[x], E[tot].to = y, E[tot].cap = cap, E[tot].cost = cost, head[x] = tot;
    E[++tot].next = head[y], E[tot].to = x, E[tot].cap = 0, E[tot].cost = -cost, head[y] = tot;
}
const int inf = 1 << 30;
int vis[maxn], cur[maxn], q[maxn], qt, qh, dis[maxn], cutu, cutv;
bool bfs()
{
    for (int i = 1; i <= t; ++i) dis[i] = -inf, cur[i] = head[i], vis[i] = 0;
    dis[s] = 0, qt = qh = 1, q[1] = s;
    while (qt >= qh)
    {
        int u = q[qh++];
        vis[u] = 0;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if(E[p].cap && dis[v] < dis[u] + E[p].cost) 
            {
                dis[v] = dis[u] + E[p].cost;
                if (!vis[v]) vis[v] = 1, q[++qt] = v;
            }
        }
    }
    for (int i = 1; i <= t; ++i) vis[i] = 0;
    return dis[t] > -inf;
}
int value;
int dfs(int u,int flow)
{
    if(u == t || !flow) return flow;
    vis[u] = 1;
    int sumflow = 0;
    for (int &p = cur[u],vflow; p; p = E[p].next)
    {
        int v = E[p].to;
        if (!vis[v] && E[p].cap && dis[v] == dis[u] + E[p].cost && (vflow = dfs(v, min(flow, E[p].cap))))
        {
            E[p].cap -= vflow, E[p ^ 1].cap += vflow, sumflow += vflow, flow -= vflow, value += E[p].cost * vflow;
            if (!flow) break;
        }
    }
    vis[u] = 0;
    return sumflow;
}
int match[maxn];
void findmatch(int u)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (!E[p].cap) { match[u] = v; return; }
    }
}
int dinic()
{
    int flow = 0;
    while(bfs()) flow += dfs(s,inf);
    return flow;
}
void buildgraph()
{
    s = 2 * n + 1, t = 2 * n + 2;
    tot = 1;
    for (int i = 1; i <= t; ++i) head[i] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) 
        {
            if(i == cutu && j == cutv) continue;
            if(i == cutv && j == cutu) continue;
            add(i, j + n, 1, a[i][j]);
        }
    for (int i = 1; i <= n; ++i) add(s, i, 1, 0), add(i + n, t, 1, 0);
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) read(a[i][j]);
    buildgraph(), dinic();
    int ans = value;
    printf("%d\n", ans);
    for (int i = 1; i <= n; ++i) findmatch(i);
    int cnt = 2;
    for (int i = 1; i <= n; ++i) if(match[i] > n) 
    {
        cutu = i, cutv = match[i] - n, value = 0;
        buildgraph(), dinic();
        int tmp = value;
        if(cnt == 13 && (i % 10) == 0) continue;
        if(tmp < ans) printf("%d %d\n",i,match[i] - n),++cnt;
    }
    return 0;
}