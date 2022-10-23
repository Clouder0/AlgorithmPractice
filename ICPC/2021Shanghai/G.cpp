#include <algorithm>
#include <cstdio>
#include <ctype.h>
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
const int maxn = 1e5 + 100;
const int mod = 998244353;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void addE(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int n, sonnum[maxn], f[maxn], left[maxn], fa[maxn];
int pre[maxn];
inline int mul(int a, int b) { return (1ll * a * b) % mod; }
inline int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
void dfs(int u)
{
    f[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        fa[v] = u, dfs(v);
        sonnum[u] += left[v];
        f[u] = mul(f[u], f[v]);
    }
    if (sonnum[u] & 1)
    {
        left[u] = 0;
        f[u] = mul(f[u], mul(sonnum[u], pre[(sonnum[u] - 1) / 2]));
    }
    else
    {
        left[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (v == fa[u]) continue;
        }
        f[u] = mul(f[u], pre[sonnum[u] / 2]);
    }
}
signed main()
{
    read(n);
    for (int i = 1, u, v; i < n; ++i) read(u), read(v), addE(u, v), addE(v, u);
    pre[0] = 1;
    for (int i = 1; i <= n; ++i) pre[i] = mul(pre[i - 1], 2 * i - 1);
    dfs(1);
    printf("%lld\n", f[1]);
    return 0;
}