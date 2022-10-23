#include <cstdio>
#include <algorithm>
#include <set>
#include <ctype.h>
using std::max;
using std::multiset;
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
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y) { E[++tot].next = head[x], E[tot].to = y, head[x] = tot; }
int n, m, w[maxn], size[maxn], son[maxn], dep[maxn], fa[maxn], top[maxn], dfn[maxn], id[maxn], ind;
struct node2
{
    int maxx,secx;
}A[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(node2& now, const node2 l, const node2 r)
{
    if (l.maxx > r.maxx) now.maxx = l.maxx, now.secx = max(l.secx, r.maxx);
    else if (l.maxx < r.maxx) now.maxx = r.maxx, now.secx = max(r.secx, l.maxx);
    else now.maxx = l.maxx, now.secx = max(l.secx, r.secx);
}
void build(int l,int r,int p)
{
    if (l == r) return (void)(A[p].maxx = w[id[l]], A[p].secx = 0);
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(A[p], A[ls], A[rs]);
}
void modify(int l,int r,int p,int pos,int k)
{
    if (l == r) return (void)(A[p].maxx += k);
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, ls, pos, k);
    else modify(mid + 1, r, rs, pos, k);
    pushup(A[p], A[ls], A[rs]);
}
node2 ask(int l, int r, int p, int ll, int rr)
{
    if(l >= ll && r <= rr) return A[p];
    int mid = l + r >> 1;
    if(ll <= mid && rr > mid)
    {
        node2 lnode = ask(l, mid, ls, ll, rr), rnode = ask(mid + 1, r, rs, ll, rr), now;
        pushup(now, lnode, rnode);
        return now;
    }
    else if(ll <= mid) return ask(l,mid,ls,ll,rr);
    else return ask(mid + 1,r,rs,ll,rr);
}
void dfs1(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    dfn[u] = ++ind, id[ind] = u;
    if (!son[u]) return;
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v);
    }
}
node2 treeask(int x, int y)
{
    node2 res;
    res.maxx = res.secx = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
        pushup(res, res, ask(1, n, 1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) std::swap(x, y);
    pushup(res, res, ask(1, n, 1, dfn[x], dfn[y]));
    return res;
}
multiset<int> s;
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    for (int i = 1; i <= n; ++i) read(w[i]), s.insert(w[i]);
    dep[1] = 1, dfs1(1), top[1] = 1, dfs2(1), build(1, n, 1);
    read(m);
    for (int i = 1, opt, x, y; i <= m; ++i)
    {
        read(opt),read(x),read(y);
        if (opt == 0) s.erase(s.find(w[x])), w[x] += y, s.insert(w[x]), modify(1, n, 1, dfn[x], y);
        else 
        {
            node2 t = treeask(x, y);
            if (t.maxx == 0 || t.secx == 0) { puts("-1"); continue; }
            s.erase(s.find(t.maxx)), s.erase(s.find(t.secx));
            printf("%d %d\n", t.secx, *--s.lower_bound(*--s.end()));
            s.insert(t.maxx), s.insert(t.secx);
        }
    }
    return 0;
}