#include <cstdio>
#include <algorithm>
#include <cctype>
using std::max;
using std::min;
//#define DEBUG
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
const int maxn = 5e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y; }
int n, m, fa[maxn], siz[maxn], son[maxn], top[maxn], dfn[maxn], id[maxn], ind;
#define ls p << 1
#define rs p << 1 | 1
namespace T
{
int csum[maxn << 2], addval[maxn << 2], addtag[maxn << 2], maxx[maxn << 2], maxid[maxn << 2], minn[maxn << 2], minid[maxn << 2];
inline void pushup(int p)
{
    csum[p] = csum[ls] + csum[rs];
    maxx[p] = max(maxx[ls], maxx[rs]);
    if (maxx[p] == maxx[ls]) maxid[p] = maxid[ls]; else maxid[p] = maxid[rs];
    minn[p] = min(minn[ls], minn[rs]);
    if (minn[p] == minn[ls]) minid[p] = minid[ls]; else minid[p] = minid[rs];
}
inline void pushdown(int p)
{
    if(!addtag[p]) return;
    addval[ls] += addtag[p], addtag[ls] += addtag[p];
    if (maxid[ls]) maxx[ls] += addtag[p];
    if (minid[ls]) minn[ls] += addtag[p];
    addval[rs] += addtag[p], addtag[rs] += addtag[p];
    if (maxid[rs]) maxx[rs] += addtag[p];
    if (minid[rs]) minn[rs] += addtag[p];
    addtag[p] = 0;
}
void add(int l, int r, int p, int ll, int rr, int k) //sequence add
{
    if(l >= ll && r <= rr)
    {
        addval[p] += k, addtag[p] += k;
        if (maxid[p]) maxx[p] += k;
        if (minid[p]) minn[p] += k;
        return;
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (ll <= mid) add(l, mid, ls, ll, rr, k);
    if (rr > mid) add(mid + 1, r, rs, ll, rr, k);
    pushup(p);
}
void addpointD(int l, int r, int p, int x)  //point add
{
    if (l == r) return (void)(maxx[p] = addval[p], maxid[p] = l);
    pushdown(p);
    int mid = (l + r) >> 1;
    if (x <= mid) addpointD(l, mid, ls, x);
    else addpointD(mid + 1, r, rs, x);
    pushup(p);
}
void delpointD(int l, int r, int p, int x)
{
    if(l == r) return (void)(maxx[p] = maxid[p] = 0);
    pushdown(p);
    int mid = (l + r) >> 1;
    if (x <= mid) delpointD(l, mid, ls, x);
    else delpointD(mid + 1, r, rs, x);
    pushup(p);
}
const int INF = 1 << 30;
void build(int l, int r, int p)
{
    if(l == r) return (void)(minn[p] = INF);
    int mid = (l + r) >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(p);
}
void addpointC(int l,int r,int p,int x)
{
    if (l == r) return (void)(csum[p] = 1,minn[p] = addval[p], minid[p] = l);
    pushdown(p);
    int mid = (l + r) >> 1;
    if (x <= mid) addpointC(l, mid, ls, x);
    else addpointC(mid + 1, r, rs, x);
    pushup(p);
}
void delpointC(int l, int r, int p, int x)
{
    if (l == r) return (void)(csum[p] = 0,minn[p] = INF, minid[p] = 0);
    pushdown(p);
    int mid = (l + r) >> 1;
    if (x <= mid) delpointC(l, mid, ls, x);
    else delpointC(mid + 1, r, rs, x);
    pushup(p);
}
}  // namespace T
namespace HD  //Heavy Decomposition
{
void dfs1(int u)
{
    siz[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        fa[v] = u, dfs1(v), siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
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
        if (v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v);
    }
}
void treeadd(int x, int k) { for (; x; x = fa[top[x]]) T::add(1, n, 1, dfn[top[x]], dfn[x], k); }
}
int bel[maxn];
void insertC(int x) { if(x) bel[x] = 1, T::addpointC(1, n, 1, dfn[x]); }
void insertD(int x) { if(x) bel[x] = 2, T::addpointD(1, n, 1, dfn[x]); }
void delC(int x) { if(x) bel[x] = 0, T::delpointC(1, n, 1, dfn[x]); }
void delD(int x) { if(x) bel[x] = 0, T::delpointD(1, n, 1, dfn[x]); }
void addpoint(int x) { if (x) HD::treeadd(x, 1), insertD(x); }
void delpoint(int x) { if (x) HD::treeadd(x, -1); }
void maintain()
{
    again:
    if (T::csum[1] < T::maxx[1])
    {
        int x = id[T::maxid[1]];
        delD(x), insertC(x);
        goto again;
    }
    if (T::csum[1] > T::minn[1])
    {
        int x = id[T::minid[1]];
        delC(x), insertD(x);
        goto again;
    }
}
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    HD::dfs1(1), top[1] = 1, HD::dfs2(1);
    T::build(1, n, 1);
    read(m);
    for (int i = 1, opt, x; i <= m; ++i)
    {
        read(opt), read(x);
        if (opt == 1) addpoint(x);
        else
        {
            if (bel[x] == 1) delC(x);
            else if(bel[x] == 2) delD(x);
            delpoint(x);
        }
        maintain();
        printf("%d\n", T::csum[1]);
    }
    return 0;
}