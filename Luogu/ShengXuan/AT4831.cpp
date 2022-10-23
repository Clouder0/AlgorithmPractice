#include <algorithm>
#include <cstdio>
#include <ctype.h>
using namespace std;
#define int long long
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
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 4e5 + 100;
const int maxm = 4e5 + 100;
int n, m, cnt, d[maxn], p[maxn], s[maxn], fa[maxn], onenum, toid[maxn], vis[maxn];
struct light
{
    int pos, status;
} A[maxn];
inline bool cmp(const light& a, const light& b) { return a.pos < b.pos; }
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
void dfs(int u)
{
    if (s[u]) d[u] = 1, ++onenum;
    for (int p = head[u], v; p; p = E[p].next)
        if (!fa[v = E[p].to]) fa[v] = u, toid[v] = E[p].val, dfs(v), d[u] += d[v];
}
signed main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(A[i].pos), read(A[i].status);
    sort(A + 1, A + 1 + n,cmp);
    for (int i = 1; i <= n; ++i) p[i] = A[i].pos, s[i] = A[i].status;
    for (int i = n + 1; i; --i) s[i] = s[i] ^ s[i - 1];
    for (int i = 1, l, r; i <= m; ++i)
    {
        read(l), read(r), l = lower_bound(p + 1, p + 1 + n, l) - p, r = upper_bound(p + 1, p + 1 + n, r) - p - 1;
        if (l <= r) add(l, r + 1, i), add(r + 1, l, i);
    }
    for (int i = 1; i <= n + 1; ++i)
        if (!fa[i])
        {
            onenum = 0, fa[i] = i, dfs(i);
            if (onenum & 1) goto fail;
        }
    for (int i = 1; i <= n + 1; ++i) if (d[i] & 1) vis[toid[i]] = 1,++cnt;
    printf("%lld\n", cnt);
    for (int i = 1; i <= m; ++i) if(vis[i]) printf("%lld ",i);
    return 0;
fail:
    puts("-1");
    return 0;
}