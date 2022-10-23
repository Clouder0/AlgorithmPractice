#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
const int maxn = 5e4 + 100;
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
    r = 0;
    for (c = nc(); !isdigit(c); c = nc()) ;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}

struct node
{
    int to, next,id;
} E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y, int id) { E[++tot].next = head[x], E[tot].to = y, E[tot].id = id, head[x] = tot; }
struct edge
{
    int u, v, w;
} G[maxn];
bool cmp(const edge& a, const edge& b) { return a.w < b.w; }

//you can skip this part
int dep[maxn], size[maxn], son[maxn], top[maxn], fa[maxn], id[maxn], ANS[maxn];
void dfs1(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        id[v] = E[p].id, fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), size[u] += size[v];
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
    for (; top[x] != top[y]; x = fa[top[x]]) if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    return dep[x] < dep[y] ? x : y;
}
//region end

int bel[maxn], up[maxn];
int find(int x) { return x == up[x] ? x : up[x] = find(up[x]); }
void update(int x, int y, int c)  //y is the ancestor of x
{
    //update from x to y (excluding y) with color c
    for (x = find(x); dep[x] > dep[y]; x = find(x)) bel[x] = c, up[x] = fa[x];
    //only set up[x] to fa[x], then leave it to path compression
}
int n, m;
int main()
{
    read(n), read(m);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b, i), add(b, a, i);
    dep[1] = 1, dfs1(1), top[1] = 1, dfs2(1);
    for (int i = 1; i <= m; ++i) read(G[i].u), read(G[i].v), read(G[i].w);
    std::sort(G + 1, G + 1 + m, cmp);
    for (int i = 1; i <= n; ++i) up[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        int l = lca(G[i].u, G[i].v);
        update(G[i].u, l, i), update(G[i].v, l, i);
    }
    for (int i = 2; i <= n; ++i) ANS[id[i]] = bel[i] ? G[bel[i]].w : -1;
    for (int i = 1; i < n; ++i) printf("%d\n", ANS[i]);
    return 0;
}