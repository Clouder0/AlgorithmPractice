#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <vector>
#include <queue>
using namespace std;
const int bufSize = 1e6;
#define DEBUG
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e6, maxm = 5e6;
#define int long long
const int inf = 1ll << 60;
int n, m, s1, t1, s2, t2;
int U[maxn], V[maxn], W[maxn];
struct node
{
    int to, next, val;
} E[maxm];
int head[maxn];
inline void add(const int& x, const int& y, const int& val)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot;
}
int vis[maxn];
void dij(int s, int* dis)
{
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    for (int i = 1; i <= n; ++i) vis[i] = 0, dis[i] = inf;
    dis[s] = 0, q.push(make_pair(dis[s], s));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (dis[v] > dis[u] + E[p].val) dis[v] = dis[u] + E[p].val, q.push(make_pair(dis[v], v));
        }
    }
}
int dis1[maxn], dis2[maxn], rdis1[maxn], rdis2[maxn], in[maxn], f[maxn],ans;
struct node2
{
    int to,next,val,tag;
}G[maxm];
int R[maxn],tot2;
inline void Gadd(const int& x, const int& y, const int& val, const int& tag)
{
    G[++tot2].next = R[x],G[tot2].to = y,G[tot2].val = val,G[tot2].tag = tag,R[x] = tot2;
}
void topo()
{
    static int q[maxn], qt, qh;
    qt = 0, qh = 1;
    q[++qt] = s1;
    while(qt >= qh)
    {
        int u = q[qh++];
        for (int p = R[u]; p; p = G[p].next)
        {
            int v = G[p].to;
            f[v] = max(f[v],f[u] + G[p].val * G[p].tag);
            if(--in[v] == 0) q[++qt] = v;
        }
    }
    for (int i = 1; i <= n; ++i) ans = max(ans, f[i]);
}
signed main()
{
    read(n), read(m), read(s1), read(t1), read(s2), read(t2);
    for (int i = 1, a, b, c; i <= m; ++i) read(a), read(b), read(c), add(a, b, c), add(b, a, c), U[i] = a, V[i] = b, W[i] = c;
    dij(s1, dis1), dij(t1, rdis1), dij(s2, dis2), dij(t2, rdis2);
    for (int u = 1; u <= n; ++u)
        for (int p = head[u],v; p; p = E[p].next)
        {
            v = E[p].to;
            if (dis1[u] + rdis1[v] + E[p].val == dis1[t1])
                Gadd(u, v, E[p].val, (dis2[u] + rdis2[v] + E[p].val) == dis2[t2]),in[v]++;
        }
    topo();
    tot2 = 0;
    for (int i = 1; i <= n; ++i) R[i] = f[i] = in[i] = 0;
    for (int u = 1; u <= n; ++u)
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (dis1[u] + rdis1[v] + E[p].val == dis1[t1])
                Gadd(u, v, E[p].val, (dis2[v] + rdis2[u] + E[p].val) == dis2[t2]),in[v]++;
        }
    topo();
    printf("%lld\n", ans);
    return 0;
}
