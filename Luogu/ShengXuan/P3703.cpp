#include <algorithm>
#include <cstdio>
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
template <typename T>
inline T read(T& r)
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
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int n, m;
int fa[maxn], size[maxn], son[maxn], top[maxn], dep[maxn], dfn[maxn], id[maxn], ind;
void dfs1(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    id[dfn[u] = ++ind] = u;
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
namespace Seg
{
int maxx[maxn << 2], col[maxn << 2], coltag[maxn << 2], addtag[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
using std::max;
inline void pushup(int p) { maxx[p] = max(maxx[ls], maxx[rs]); }
inline void pushdown(int p)
{
    if (coltag[p]) col[ls] = col[rs] = coltag[ls] = coltag[rs] = coltag[p], coltag[p] = 0;
    if (addtag[p]) maxx[ls] += addtag[p], maxx[rs] += addtag[p], addtag[ls] += addtag[p], addtag[rs] += addtag[p], addtag[p] = 0;
}
void modify(int l, int r, int p, int ll, int rr, int k)
{
    if (l >= ll && r <= rr) return (void)(maxx[p] += k, addtag[p] += k);
    int mid = (l + r) >> 1;
    pushdown(p);
    if (ll <= mid) modify(l, mid, ls, ll, rr, k);
    if (rr > mid) modify(mid + 1, r, rs, ll, rr, k);
    pushup(p);
}
void modifycol(int l, int r, int p, int ll, int rr, int k)
{
    if (l >= ll && r <= rr) return (void)(col[p] = coltag[p] = k);
    int mid = (l + r) >> 1;
    pushdown(p);
    if (ll <= mid) modifycol(l, mid, ls, ll, rr, k);
    if (rr > mid) modifycol(mid + 1, r, rs, ll, rr, k);
}
int askmax(int l, int r, int p, int ll, int rr)
{
    if (l >= ll && r <= rr) return maxx[p];
    int mid = (l + r) >> 1, res = 0;
    pushdown(p);
    if (ll <= mid) res = askmax(l, mid, ls, ll, rr);
    if (rr > mid) res = std::max(res, askmax(mid + 1, r, rs, ll, rr));
    return res;
}
int askcol(int l, int r, int p, int pos)
{
    if (l == r) return col[p];
    int mid = (l + r) >> 1;
    pushdown(p);
    return pos <= mid ? askcol(l, mid, ls, pos) : askcol(mid + 1, r, rs, pos);
}
void build(int l, int r, int p)
{
    if (l == r) return (void)(maxx[p] = dep[id[l]], col[p] = id[l]);
    int mid = (l + r) >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(p);
}
}  // namespace Seg
int st[maxn], ed[maxn], cnt;
void treecol(int x, int k)
{
    for (; top[x] > 1; x = fa[top[x]]) Seg::modifycol(1, n, 1, dfn[top[x]], dfn[x], k);
    Seg::modifycol(1, n, 1, 1, dfn[x], k);
}
int upjump(int x, int limit)
{
    int last = 0;
    while (top[x] != top[limit]) last = top[x], x = fa[top[x]];
    if (x == limit) return last;  // if x belongs to light son, then it will jump from its top to limit
    return son[limit];            //or x is the heavyson
}
void treemodify(int x)
{
    int nowcol = ++cnt;
    st[nowcol] = 1, ed[nowcol] = x;
    int p = x;
    while (p)
    {
        int col = Seg::askcol(1, n, 1, dfn[p]);
        int up = st[col], down = ed[col];
        Seg::modify(1, n, 1, dfn[up], dfn[up] + size[up] - 1, -1);
        if (p != down)
        {
            st[col] = upjump(down, p);
            Seg::modify(1, n, 1, dfn[st[col]], dfn[st[col]] + size[st[col]] - 1, 1);  //some extra subtree
        }
        p = fa[up];  //go next
    }
    Seg::modify(1, n, 1, 1, n, 1);
    treecol(x, nowcol);  //update color by decompositoin
}
int main()
{
    read(n), read(m);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dep[1] = 1, dfs1(1), top[1] = 1, dfs2(1);
    cnt = n;  //color cnt set to n, as each point has its original color
    for (int i = 1; i <= n; ++i) st[i] = ed[i] = i;
    Seg::build(1, n, 1);
    for (int i = 1, opt, x, y; i <= m; ++i)
    {
        read(opt), read(x);
        if (opt == 1) treemodify(x);
        else if (opt == 2)
        {
            read(y);
            int res = Seg::askmax(1, n, 1, dfn[x], dfn[x]) + Seg::askmax(1, n, 1, dfn[y], dfn[y]);
            int l = lca(x, y);
            res = res - 2 * Seg::askmax(1, n, 1, dfn[l], dfn[l]) + 1;
            printf("%d\n", res);
        }
        else printf("%d\n", Seg::askmax(1, n, 1, dfn[x], dfn[x] + size[x] - 1));
    }
    return 0;
}