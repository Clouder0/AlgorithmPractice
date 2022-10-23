#include <cstdio>
#include <algorithm>
#include <ctype.h>
using std::swap;
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
const int mod = 998244353;
const int maxn = 3e5 + 100;
struct node
{
    int to,next;
}E[maxn << 1];
int head[maxn];
inline void addE(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
inline int add(int x,int y)
{
    int res = x + y;
    if (res >= mod) res -= mod;
    return res;
}
inline int mul(int x, int y) { return (1ll * x * y) % mod; }
int n, m, dep[maxn], f[maxn][52], size[maxn], son[maxn], top[maxn],fa[maxn];
void dfs(int u)
{
    int t = dep[u];
    for (int i = 1; i <= 50; ++i) f[u][i] = add(f[fa[u]][i], t), t = mul(t, dep[u]);
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next) 
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1, dfs(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    if(!son[u]) return;
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v);
    }
}
int lca(int x, int y)
{
    while(top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), addE(a, b), addE(b, a);
    dfs(1), top[1] = 1, dfs2(1);
    read(m);
    for (int i = 1,a,b,c; i <= m; ++i) 
    {
        read(a), read(b), read(c);
        int l = lca(a,b);
        printf("%d\n", add(add(f[a][c], f[b][c]), add(mod - f[l][c], mod - f[fa[l]][c])));
    }
    return 0;
}