#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
const int maxn = 1e4, maxm = 1e5;
struct node
{
    int from,to, next, cap;
} E[maxm];
int head[maxn], tot = 1;
inline void add(const int& x, const int& y, const int& cap)
{
    E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].cap = cap,E[tot].from = x;
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
int U[maxm], V[maxm];
int fa[maxn];
int find(const int &x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
inline void unite(int x,int y)
{
    x = find(x),y = find(y);
    if(x == y) return;
    fa[x] = y;
}
void output(int u)
{
    printf("%d ",u);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v > n && E[p].cap == 0) output(v - n);
    }
}
int main()
{
    scanf("%d %d", &n, &m);
    s = 0, t = n * 2 + 1;
    for (int i = 1, a, b; i <= m; ++i)
        scanf("%d %d", &a, &b), add(a, b + n, 1), add(b + n, a, 0);
    for (int i = 1; i <= n; ++i) add(s, i, 1), add(i, s, 0);
    for (int i = 1; i <= n; ++i) add(i + n, t, 1), add(t, i + n, 0);
    while (bfs()) dfs(s, 1 << 30);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 2; i <= tot; ++i) 
        if(E[i].from >= 1 && E[i].from <= n && E[i].to > n && E[i].to < t && E[i].cap == 0)
            unite(E[i].to - n,E[i].from);
    int t= 0 ;
    for (int i = 1; i <= n; ++i)
        if (find(i) == i) output(i), puts(""), ++t;
    printf("%d\n", t);
    return 0;
}