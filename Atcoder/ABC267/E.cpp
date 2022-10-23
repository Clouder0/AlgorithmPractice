#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <queue>
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc())
        ;
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 4e5 + 100;
struct node
{
    int to, next;
} E[maxn];
int head[maxn], cnt;
inline void add(int u, int v)
{
    E[++cnt].next = head[u], head[u] = cnt, E[cnt].to = v;
}
long long ans, b[maxn];
int n, m, a[maxn], vis[maxn];
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1, u, v; i <= m; ++i) read(u), read(v), add(u, v), add(v, u), b[u] += a[v], b[v] += a[u];
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> q;
    for (int i = 1; i <= n; ++i) q.push(std::make_pair(b[i], i));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        long long res = 0;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (!vis[v]) b[v] -= a[u], q.push(std::make_pair(b[v], v)), res += a[v];
        }
        ans = std::max(ans, res);
    }
    printf("%lld\n", ans);
    return 0;
}