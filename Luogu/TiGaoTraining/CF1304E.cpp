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
const int maxn = 1e5 + 100;
int n, m;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int size[maxn], son[maxn], fa[maxn], dep[maxn], top[maxn];
void dfs1(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1, fa[v] = u, dfs1(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    if (!son[u]) return;
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(top[v] = v);
    }
}
inline int lca(int x, int y)
{
    for (; top[x] != top[y]; x = fa[top[x]]) if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    return dep[x] < dep[y] ? x : y;
}
inline int getdis(int x, int y) { return dep[x] + dep[y] - (dep[lca(x, y)] << 1); }
inline bool check(int x, int y) { return x <= y && (x & 1) == (y & 1); }
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dfs1(1), top[1] = 1, dfs2(1);
    read(m);
    for (int i = 1, x, y, a, b, k; i <= m; ++i)
    {
        read(x), read(y), read(a), read(b), read(k);
        //not passing
        int d = getdis(a, b);
        if (check(d,k)) { puts("YES"); continue; }
        //goto x
        d = getdis(a, x) + 1 + getdis(y, b);
        if (check(d, k)) { puts("YES"); continue; }
        //goto y
        d = getdis(a, y) + 1 + getdis(x, b);
        if (check(d, k)) { puts("YES"); continue; }
        puts("NO");
    }
    return 0;
}