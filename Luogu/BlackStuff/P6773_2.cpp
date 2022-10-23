#include <algorithm>
#include <cctype>
#include <cstdio>
const int maxn = 1e6 + 100;
const int mod = 998244353;
inline int add(int x, int y) { int res = x + y; return res >= mod ? res - mod : res; }
inline int mul(int x, int y) { return 1ll * x * y % mod; }
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
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
struct node
{
    int to, next;
} E[maxn << 2];
int Eh[maxn], Gh[maxn], tot;
inline void addE(int x, int y) { E[++tot].next = Eh[x], Eh[x] = tot, E[tot].to = y; }
inline void addG(int x, int y) { E[++tot].next = Gh[x], Gh[x] = tot, E[tot].to = y; }
int n, m, dep[maxn], up[maxn], size[maxn], son[maxn], maxdep;
void dfs1(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    for (int p = Gh[u]; p; p = E[p].next) up[u] = std::max(up[u], dep[E[p].to]);
    size[u] = 1;
    for (int p = Eh[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs1(v, u), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
namespace seg
{
int root[maxn], L[maxn * 10], R[maxn * 10], sum[maxn * 10], multag[maxn * 10], s[maxn * 10], top, ind;
inline int newnode()
{
    int id = top > 0 ? s[top--] : ++ind;
    L[id] = R[id] = sum[id] = 0, multag[id] = 1;
    return id;
}
inline void delnode(int x) { if (x) s[++top] = x; }
inline void pushdown(int p)
{
    if (multag[p] != 1)
    {
        if (L[p])
        {
            sum[L[p]] = mul(sum[L[p]], multag[p]);
            multag[L[p]] = mul(multag[L[p]], multag[p]);
        }
        if (R[p])
        {
            sum[R[p]] = mul(sum[R[p]], multag[p]);
            multag[R[p]] = mul(multag[R[p]], multag[p]);
        }
        multag[p] = 1;
    }
}
inline void pushup(int p) { sum[p] = add(sum[L[p]], sum[R[p]]); }
void modify(int l, int r, int& p, int pos, int k)
{
    if (!p) p = newnode();
    if (l == r) return (void)(sum[p] += k);
    int mid = (l + r) >> 1;
    pushdown(p);
    if (pos <= mid) modify(l, mid, L[p], pos, k); else modify(mid + 1, r, R[p], pos, k);
    pushup(p);
}
int ask(int l, int r, int p, int ll, int rr)
{
    if (!p) return 0;
    if (l >= ll && r <= rr) return sum[p];
    int mid = (l + r) >> 1, res = 0;
    pushdown(p);
    if (ll <= mid) res = ask(l, mid, L[p], ll, rr);
    if (rr > mid) res = add(res, ask(mid + 1, r, R[p], ll, rr));
    return res;
}
int merge(int l, int r, int x, int y, int& xsum, int& ysum)  //ysum is originally depval
{
    if (!x && !y) return 0;
    if (!x || !y)
    {
        if (!x)
        {
            ysum = add(ysum, sum[y]);
            sum[y] = mul(sum[y], xsum), multag[y] = mul(multag[y], xsum);
            return y;
        }
        xsum = add(xsum, sum[x]);
        sum[x] = mul(sum[x], ysum), multag[x] = mul(multag[x], ysum);
        return x;
    }
    if (l == r)
    {
        ysum = add(ysum, sum[y]);
        int oldx = sum[x];
        sum[x] = add(mul(sum[y], xsum), mul(sum[x], ysum));
        xsum = add(xsum, oldx);
        delnode(y);
        return x;
    }
    int mid = (l + r) >> 1;
    pushdown(x), pushdown(y);
    L[x] = merge(l, mid, L[x], L[y], xsum, ysum);
    R[x] = merge(mid + 1, r, R[x], R[y], xsum, ysum);
    pushup(x), delnode(y);
    return x;
}
}  // namespace seg
void dfs2(int u, int fa)
{
    seg::modify(0, maxdep, seg::root[u], up[u], 1);
    if (son[u])
    {
        dfs2(son[u], u);
        int xsum = 0, ysum = seg::ask(0, maxdep, seg::root[son[u]], 0, dep[u]);
        seg::root[u] = seg::merge(0, maxdep, seg::root[u], seg::root[son[u]], xsum, ysum);
    }
    for (int p = Eh[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa || v == son[u]) continue;
        dfs2(v, u);
        int xsum = 0, ysum = seg::ask(0, maxdep, seg::root[v], 0, dep[u]);
        seg::root[u] = seg::merge(0, maxdep, seg::root[u], seg::root[v], xsum, ysum);
    }
}
signed main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), addE(a, b), addE(b, a);
    read(m);
    for (int i = 1, a, b; i <= m; ++i) read(a), read(b), addG(a, b), addG(b, a);
    dfs1(1, 0);
    for (int i = 1; i <= n; ++i) maxdep = std::max(maxdep, dep[i]);
    dfs2(1, 0);
    printf("%d\n", seg::ask(0, maxdep, seg::root[1], 0, 0));
    return 0;
}