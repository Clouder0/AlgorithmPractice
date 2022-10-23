#include <algorithm>
#include <cstdio>
#include <queue>
#include <ctype.h>
#define int long long
const int maxn = 1e6;
const int inf = 1ll << 60;
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
template<typename T>
inline T read(T &r)
{
    static char c;
    for (r = 0, c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
struct node
{
    int to, next, val;
} E[maxn];
int head[maxn], cnt;
inline void add(int u, int v, int w)
{
    E[++cnt].next = head[u], head[u] = cnt, E[cnt].to = v, E[cnt].val = w;
}
int T, n, m, C, bel[maxn];
int vis[maxn], dis[maxn];
void dij()
{
    for (int i = 1; i <= n * 2 + 10; ++i) vis[i] = 0, dis[i] = inf;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    q.push(std::make_pair(0, 1)), dis[1] = 0;
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (dis[v] > dis[u] + E[p].val)
                dis[v] = dis[u] + E[p].val, q.push(std::make_pair(dis[v], v));
        }
    }
}
signed main()
{
    read(T);
    for (int t = 1; t <= T; ++t)
    {
        read(n), read(m), read(C);
        cnt = 0;
        for (int i = 1; i <= 10 + n * 2; ++i) head[i] = 0;
        for (int i = 1; i <= n; ++i) 
        {
            read(bel[i]);
            add(bel[i] + n, i, 0);
            if (n + bel[i] + 1 <= 2 * n) add(i, n + bel[i] + 1, C);
            if (n + bel[i] - 1 > n) add(i, n + bel[i] - 1, C);
        }
        for (int i = 1, a, b, c; i <= m; ++i) read(a), read(b), read(c), add(a, b, c), add(b, a, c);
        dij();
        if (dis[n] == inf) dis[n] = -1;
        printf("Case #%lld: %lld\n", t, dis[n]);
    }
    return 0;
}
