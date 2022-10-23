#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
const int maxn = 2e6 + 100;
struct node { int to, next, val; } E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y, const int& val) { static int tot = 0; E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot; }
int n, vis[maxn], fa[maxn], maxsiz[maxn], siz[maxn], rt, total;
long long a[maxn], sum[maxn], dis[maxn], res;
void findroot(int u)
{
    siz[u] = 1, maxsiz[u] = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || vis[v]) continue;
        fa[v] = u, findroot(v), siz[u] += siz[v];
        maxsiz[u] = std::max(maxsiz[u], siz[v]);
    }
    maxsiz[u] = std::max(maxsiz[u], total - siz[u]);
    if (maxsiz[u] < maxsiz[rt]) rt = u;
}
long long H[maxn], cnt;
inline int get(long long x) { return std::lower_bound(H + 1, H + 1 + cnt, x) - H; }
int s[maxn], top;
long long need[maxn], need2[maxn];
void dfs(int u)
{
    siz[u] = 1, s[++top] = u;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || vis[v]) continue;
        fa[v] = u;
        dis[v] = dis[u] + E[p].val;
        sum[v] = sum[u] + a[v];
        need[v] = std::max(0ll, need[u] + E[p].val - a[v]);
        need2[v] = std::max(need2[u], dis[v] - sum[u]);
        dfs(v), siz[u] += siz[v];
    }
}
void dfs2(int u)
{
    s[++top] = u;
    for (int p = head[u]; p; p = E[p].next) { int v = E[p].to; if (v == fa[u] || vis[v]) continue; dfs2(v); }
}
namespace Bit
{
int sum[maxn], tim[maxn], ind;
inline void clear() { ++ind; }
inline void check(int x) { if (tim[x] != ind) sum[x] = 0, tim[x] = ind; }
inline void add(int x, int k) { for (; x <= cnt; x += x & -x) check(x), sum[x] += k; }
inline int ask(int x) { int res = 0; for (; x; x -= x & -x) check(x), res += sum[x]; return res; }
}  // namespace Bit
int tops[maxn], topnum;
void solve(int u)
{
    maxsiz[rt = 0] = 1 << 30, findroot(u);
    top = 0, cnt = 0, vis[rt] = 1, fa[rt] = dis[rt] = 0, need[rt] = need2[rt] = 0, sum[rt] = a[rt];
    dfs(rt);
    while (top)
    {
        int v = s[top--];
        if (need[v] == 0) H[++cnt] = sum[v] - dis[v] - a[rt];
        H[++cnt] = need2[v];
    }
    std::sort(H + 1, H + 1 + cnt), cnt = std::unique(H + 1, H + 1 + cnt) - H - 1;
    Bit::clear(), Bit::add(get(0), 1);
    topnum = 0;
    for (int p = head[rt], v, oldtop; p; p = E[p].next)
    {
        if (vis[v = E[p].to]) continue;
        oldtop = top, dfs2(v);
        for (int i = oldtop + 1; i <= top; ++i) if (need[s[i]] == 0) res += Bit::ask(get(sum[s[i]] - a[rt] - dis[s[i]]));
        for (int i = oldtop + 1; i <= top; ++i) Bit::add(get(need2[s[i]]), 1);
        tops[++topnum] = top;
    }
    Bit::clear();
    for (int t = topnum; t; --t)
    {
        int oldtop = tops[t - 1];
        for (int i = oldtop + 1; i <= tops[t]; ++i) if (need[s[i]] == 0) res += Bit::ask(get(sum[s[i]] - a[rt] - dis[s[i]]));
        for (int i = oldtop + 1; i <= tops[t]; ++i) Bit::add(get(need2[s[i]]), 1);
    }
    res += Bit::ask(get(0));
    for (int p = head[rt], v; p; p = E[p].next) if (!vis[v = E[p].to]) total = siz[v], solve(v);
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1, a, b, c; i < n; ++i) read(a), read(b), read(c), add(a, b, c), add(b, a, c);
    total = n, solve(1);
    printf("%lld\n", res);
    return 0;
}