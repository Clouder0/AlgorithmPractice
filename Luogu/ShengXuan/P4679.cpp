#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <queue>
const int bufSize = 1e6;
using std::max;
#define DEBUG
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; c != 'Q' && c != 'C' && c != '.' && c != '#'; c = nc());
    for (; c == 'Q' || c == 'C' || c == '.' || c == '#'; c = nc()) *s++ = c;
    *s = '\0';
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
const int maxn = 5e4 + 100;
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
int n, m, w[maxn];
int dep[maxn], fa[maxn], size[maxn], son[maxn], top[maxn], dfn[maxn], id[maxn], ind;
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
    if(!son[u]) return;
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u] || v == son[u]) continue;
        dfs2(top[v] = v);
    }
}
struct segnode
{
    int d[2][2], maxx[2][2];
    segnode() { d[0][0] = d[0][1] = d[1][0] = d[1][1] = maxx[0][0] = maxx[1][0] = maxx[0][1] = maxx[1][1] = 0; }
    bool isEmpty() const
    {
        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) if (d[i][j] != 0 || maxx[i][j] != 0) return 0;
        return 1;
    }
} A[maxn << 2];
const int inf = 1 << 30;
inline segnode pushup(const segnode ls, const segnode rs)
{
    if(ls.isEmpty()) return rs;
    if(rs.isEmpty()) return ls;
    segnode res;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) res.d[i][j] = max(-inf,max(ls.d[i][0] + rs.d[0][j], ls.d[i][1] + rs.d[1][j]));
    res.maxx[0][0] = max(-inf, max(ls.maxx[0][0], max(ls.d[0][0] + rs.maxx[0][0], ls.d[0][1] + rs.maxx[0][1])));
    res.maxx[0][1] = max(-inf, max(ls.maxx[0][1], max(ls.d[1][0] + rs.maxx[0][0], ls.d[1][1] + rs.maxx[0][1])));
    res.maxx[1][0] = max(-inf, max(rs.maxx[1][0], max(ls.maxx[1][0] + rs.d[0][0], ls.maxx[1][1] + rs.d[1][0])));
    res.maxx[1][1] = max(-inf, max(rs.maxx[1][1], max(ls.maxx[1][0] + rs.d[0][1], ls.maxx[1][1] + rs.d[1][1])));
    return res;
}
inline void make(int x,int p)
{
    if(x == 3)
    {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) A[p].maxx[i][j] = 2;
        A[p].d[0][0] = A[p].d[1][1] = 1, A[p].d[0][1] = A[p].d[1][0] = 2;
    }
    else if(x == 1)
    {
        A[p].maxx[0][0] = A[p].maxx[1][0] = A[p].d[0][0] = 1;
        A[p].maxx[0][1] = A[p].maxx[1][1] = A[p].d[0][1] = A[p].d[1][1] = A[p].d[1][0] = -inf;
    }
    else if(x == 2)
    {
        A[p].maxx[1][1] = A[p].maxx[0][1] = A[p].d[1][1] = 1;
        A[p].maxx[0][0] = A[p].maxx[1][0] = A[p].d[0][0] = A[p].d[0][1] = A[p].d[1][0] = -inf;
    }
    else
    {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) A[p].maxx[i][j] = A[p].d[i][j] = -inf;
    }
}
#define ls p << 1
#define rs p << 1 | 1
void build(int l, int r, int p)
{
    if (l == r) return (void)(make(w[id[l]], p));
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), A[p] = pushup(A[ls], A[rs]);
}
void modify(int l, int r, int p, int pos,int k)
{
    if (l == r) return (void)(make(k, p));
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, ls, pos,k);
    else modify(mid + 1, r, rs, pos,k);
    A[p] = pushup(A[ls], A[rs]);
}
segnode ask(int l,int r,int p,int ll,int rr)
{
    if(l >= ll && r <= rr) return A[p];
    int mid = l + r >> 1;
    if(ll <= mid && rr > mid) return pushup(ask(l,mid,ls,ll,rr),ask(mid + 1,r,rs,ll,rr));
    if(ll <= mid) return ask(l,mid,ls,ll,rr);
    return ask(mid + 1,r,rs,ll,rr);
}
inline segnode rev(segnode x)
{
    std::swap(x.maxx[0][0],x.maxx[1][0]),std::swap(x.maxx[0][1],x.maxx[1][1]);
    std::swap(x.d[0][1], x.d[1][0]);
    //std::swap(x.d[0][0], x.d[1][1]);
    return x;
}
int treeask(int x,int y)
{
    segnode lres, rres;
    while (top[x] != top[y])
    {
        if (dep[top[x]] > dep[top[y]]) lres = pushup(ask(1, n, 1, dfn[top[x]], dfn[x]), lres), x = fa[top[x]];
        else rres = pushup(ask(1, n, 1, dfn[top[y]], dfn[y]), rres), y = fa[top[y]];
    }
    if (dep[x] > dep[y]) lres = pushup(ask(1, n, 1, dfn[y], dfn[x]), lres);
    else rres = pushup(ask(1, n, 1, dfn[x], dfn[y]), rres);
    lres = pushup(rev(lres), rres);
    return max(0, max(lres.maxx[0][0], lres.maxx[0][1]));
}
int main()
{
    read(n),read(m);
    for (int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u);
    dfs1(1), top[1] = 1, dfs2(1);
    for (int i = 1; i <= n; ++i)
    {
        static char s[10];
        read(s);
        if (s[0] == '.') w[i] |= 1;
        if (s[1] == '.') w[i] |= 2;
    }
    build(1, n, 1);
    for (int i = 1, x, y; i <= m; ++i)
    {
        static char OPT[10],S[10];
        read(OPT);
        if (OPT[0] == 'Q') read(x), read(y), printf("%d\n", treeask(x, y));
        else
        {
            read(x), read(S);
            w[x] = 0;
            if (S[0] == '.') w[x] |= 1;
            if (S[1] == '.') w[x] |= 2;
            modify(1, n, 1, dfn[x], w[x]);
        }
    }
    return 0;
}
