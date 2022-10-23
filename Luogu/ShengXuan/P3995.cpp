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
const int maxn = 2e5 + 100;
struct node
{
    int to,next;
}E[maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int res[maxn], n, m, fa[maxn], siz[maxn], top[maxn], dep[maxn], son[maxn], d[maxn];
void dfs1(int u)
{
    siz[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u,dep[v] = dep[u] + 1,dfs1(v),siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    if(!son[u]) return;
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == son[u] || v == fa[u]) continue;
        dfs2(top[v] = v);
    }
}
int lca(int x, int y)
{
    for (; top[x] != top[y]; x = fa[top[x]])
        if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    return dep[x] < dep[y] ? x : y;
}
void dfs3(int u)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        dfs3(v), d[u] += d[v];
        if (d[v] >= d[res[u]]) res[u] = v;
    }
}
int main()
{
    read(n), read(m);
    for (int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u);
    dfs1(1), top[1] = 1, dfs2(1);
    for (int i = 1, x, y; i <= m; ++i)
    {
        read(x), read(y);
        int l = lca(x, y);
        if (fa[x] != l) d[x]++, d[l]--;
        if (fa[y] != l) d[y]++, d[l]--;
    }
    dfs3(1);
    for (int i = 1; i <= n; ++i) printf("%d\n",res[i]);
    return 0;
}