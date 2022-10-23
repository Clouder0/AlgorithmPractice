#include <cstdio>
#include <algorithm>
#include <queue>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
#define int long long
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
int T, n, m, k, mod;
const int maxn = 2e5 + 100, maxm = 6e5 + 100;
struct node
{
    int to, next, val;
} E[maxm];
int head[maxn], rhead[maxn], tot;
inline void add(const int& x, const int& y, const int& val) { E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot; }
inline void addr(const int& x, const int& y, const int& val) { E[++tot].next = rhead[x], E[tot].to = y, E[tot].val = val, rhead[x] = tot; }
inline int add(int x, int y)
{
    int res = x + y;
    if (res >= mod) res -= mod;
    return res;
}
int f[maxn][60], dis[maxn], rdis[maxn]; 
bool vis[maxn];
void dij()
{
    for (int i = 1; i <= n + 1; ++i) dis[i] = 1 << 30, vis[i] = 0;
    dis[1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    q.push(make_pair(dis[1], 1));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if(!vis[v] && dis[v] > dis[u] + E[p].val) dis[v] = dis[u] + E[p].val, q.push(make_pair(dis[v], v));
        }
    }
}
void rdij()
{
    for (int i = 1; i <= n + 1; ++i) rdis[i] = 1 << 30, vis[i] = 0;
    rdis[n + 1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    q.push(make_pair(rdis[n + 1], n + 1));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for (int p = rhead[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (!vis[v] && rdis[v] > rdis[u] + E[p].val) rdis[v] = rdis[u] + E[p].val, q.push(make_pair(rdis[v], v));
        }
    }
}
bool failed, vvis[maxn][60];
int dfs(int u, int pre)
{
    if (failed) return 0;
    int ad = rdis[u] + pre - dis[n + 1];
    if (ad > k) return 0;
    if (f[u][ad] != -1) return f[u][ad];
    if (u == n + 1) return f[u][ad] = 1;
    if (vvis[u][ad]) { failed = 1; return 0; }
    vvis[u][ad] = 1;
    int res = 0;
    for (int p = head[u]; p; p = E[p].next) res = add(res, dfs(E[p].to, pre + E[p].val));
    return f[u][ad] = res;
}
inline void init()
{
    for (int i = 1; i <= n + 1; ++i) head[i] = rhead[i] = 0;
    for (int i = 1; i <= n + 1; ++i)
        for (int j = 0; j <= k; ++j) f[i][j] = -1, vvis[i][j] = 0;
    tot = failed = 0;
}
signed main()
{
    read(T);
    while(T--)
    {
        read(n), read(m), read(k), read(mod), init();
        for (int i = 1, a, b, c; i <= m; ++i) read(a), read(b), read(c), add(a, b, c), addr(b, a, c);
        add(n, n + 1, 0), addr(n + 1, n, 0);
        dij(), rdij();
        for (int i = 1; i <= n; ++i) vis[i] = 0;
        int res = dfs(1, 0);
        if (failed)
            puts("-1");
        else printf("%lld\n", res);
    }
    return 0;
}