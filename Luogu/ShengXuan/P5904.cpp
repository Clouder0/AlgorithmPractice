#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
const int maxn = 2e5 + 100;
int n;
struct node
{
    int to,next;
}E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
long long fbuf[maxn*4],gbuf[maxn * 4], *f[maxn], *g[maxn], *indf = fbuf,*indg = gbuf;
int dep[maxn], son[maxn];
void dfs1(int u, int fa)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs1(v,u);
        if (dep[son[u]] < dep[v]) son[u] = v;
    }
    dep[u] = dep[son[u]] + 1;
}
long long ans;
void dfs2(int u,int fa)
{
    f[u][0] = 1;
    if (son[u]) f[son[u]] = f[u] + 1, g[son[u]] = g[u] - 1, dfs2(son[u], u);
    ans += g[u][0];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa || v == son[u]) continue;
        f[v] = indf, indf += dep[v], indg += dep[v] + 10, g[v] = indg, indg += dep[v] + 10;
        dfs2(v, u);
        for (int i = 1; i <= dep[v]; ++i) ans += g[v][i] * f[u][i - 1], ans += 1ll * g[u][i] * f[v][i - 1];
        for (int i = 1; i <= dep[v]; ++i) g[u][i] += 1ll * f[u][i] * f[v][i - 1];
        for (int i = 0; i < dep[v]; ++i) g[u][i] += g[v][i + 1];
        for (int i = 1; i <= dep[v]; ++i) f[u][i] += f[v][i - 1];
    }
}
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dep[1] = 1, dfs1(1, 0), f[1] = indf, indf += dep[1], indg += dep[1] + 10, g[1] = indg, indg += dep[1] + 10, dfs2(1, 0);
    printf("%lld\n", ans);
    return 0;
}