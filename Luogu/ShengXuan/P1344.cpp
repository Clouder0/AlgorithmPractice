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
const int maxn = 1000, maxm = 5200;
struct node
{
    int to, next;
    long long cap;
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
long long dfs(int u, long long flow)
{
    if (u == t || !flow) return flow;
    long long sumflow = 0,vflow;
    for (int &p = cur[u], v; p; p = E[p].next)
        if (dep[v = E[p].to] == dep[u] + 1 && (vflow = dfs(v, min(E[p].cap, flow))))
        {
            flow -= vflow, sumflow += vflow, E[p].cap -= vflow, E[p ^ 1].cap += vflow;
            if(!vflow) dep[v] = 0;
            if (!flow) break;
        }
    return sumflow;
}
struct dat
{
    int a,b,c;
}EE[maxm];
int main()
{
    read(n),read(m);
    s = 1,t = n;
    for (int i = 1; i <= m; ++i) read(EE[i].a),read(EE[i].b),read(EE[i].c),add(EE[i].a,EE[i].b,1ll * EE[i].c * (m + 1) + 1),add(EE[i].b,EE[i].a,0);
    long long res = 0;
    while (bfs()) res += dfs(s, 1ll << 60);
    printf("%lld %lld", res / (m + 1),res % (m + 1));
    return 0;
}