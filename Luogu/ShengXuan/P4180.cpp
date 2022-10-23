#include <cstdio>
#include <queue>
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
template <typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100, maxm = 3e5 + 100;
struct node
{
    int to, next, val;
} E[maxm];
int head[maxn];
inline void add(const int &x, const int &y, const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot;
}
int n, m;
namespace Dec
{
    int w[maxn], id[maxn];
}
namespace Seg
{
    struct node
    {
        int maxx, secx;
        node(){maxx = secx = 0;}
    } A[maxn << 2];
    using namespace std;
    inline void pushup(node &now,node &ls,node &rs)
    {
        if(ls.maxx > rs.maxx) now.maxx = ls.maxx,now.secx = max(ls.secx,rs.maxx);
        else if(ls.maxx < rs.maxx) now.maxx = rs.maxx,now.secx = max(ls.maxx,rs.secx);
        else now.maxx = ls.maxx,now.secx = max(ls.secx,rs.secx);
    }
    void build(int l, int r, int p)
    {
        node &now = A[p],&ls = A[p<<1],&rs = A[p<<1|1];
        if (l == r) return (void)(now.maxx = Dec::w[Dec::id[l]],now.secx = 0);
        int mid = l + r >> 1;
        build(l, mid, p<<1), build(mid + 1, r, p<<1|1);
        pushup(now,ls,rs);
    }
    node ask(int l, int r, int p, int ll, int rr)
    {
        node &now = A[p];
        if (l >= ll && r <= rr) return now;
        int mid = l + r >> 1;
        if (ll <= mid && rr > mid)
        {
            node ans, la = ask(l, mid, p << 1, ll, rr), ra = ask(mid + 1, r, p << 1 | 1, ll, rr);
            pushup(ans, la, ra);
            return ans;
        }
        else if (ll <= mid) return ask(l, mid, p << 1, ll, rr);
        else return ask(mid + 1, r, p << 1 | 1, ll, rr);
    }
} // namespace Seg
namespace Dec
{
    int son[maxn], fa[maxn], size[maxn], dep[maxn], top[maxn], dfn[maxn], cnt;
    void dfs1(int u)
    {
        size[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (v == fa[u]) continue;
            dep[v] = dep[u] + 1, fa[v] = u, w[v] = E[p].val, dfs1(v), size[u] += size[v];
            if (size[v] > size[son[u]]) son[u] = v;
        }
    }
    void dfs2(int u)
    {
        dfn[u] = ++cnt, id[cnt] = u;
        if (!son[u]) return;
        top[son[u]] = top[u], dfs2(son[u]);
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (v == fa[u] || v == son[u]) continue;
            top[v] = v, dfs2(v);
        }
    }
    using namespace std;
    inline Seg::node askmax(int x, int y)
    {
        Seg::node ans;
        for (; top[x] != top[y]; x = fa[top[x]])
        {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            Seg::node res = Seg::ask(1, n, 1, dfn[top[x]], dfn[x]), tmp = ans;
            Seg::pushup(ans, tmp, res);
        }
        if(x == y) return ans;
        if (dep[x] > dep[y]) swap(x, y);
        Seg::node res = Seg::ask(1, n, 1, dfn[x] + 1, dfn[y]), tmp = ans;
        Seg::pushup(ans, tmp, res);
        return ans;
    }
} // namespace Dec
namespace Kruskal
{
    struct edge
    {
        int from, to, val, used;
    } A[maxm];
    bool cmp(const edge &a, const edge &b)
    {
        return a.val < b.val;
    }
    int fa[maxn];
    inline int find(const int &x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    inline void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y) return;
        fa[x] = y;
    }
    long long treeans;
    inline void solve()
    {
        treeans = 0;
        for (int i = 1; i <= n; ++i) fa[i] = i, head[i] = 0;
        std::sort(A + 1, A + 1 + m, cmp);
        for (int i = 1; i <= m; ++i)
        {
            int u = A[i].from, v = A[i].to;
            if (find(u) == find(v)) continue;
            treeans += A[i].val;
            add(u, v, A[i].val), add(v, u, A[i].val);
            merge(u, v);
            A[i].used = 1;
        }
    }
} // namespace Kruskal
int main()
{
    read(n), read(m);
    for (int i = 1; i <= m; ++i) read(Kruskal::A[i].from), read(Kruskal::A[i].to), read(Kruskal::A[i].val), Kruskal::A[i].used = 0;
    Kruskal::solve();
    Dec::cnt = 0, Dec::dfs1(1), Dec::top[1] = 1, Dec::dfs2(1);
    Seg::build(1, n, 1);
    using namespace Kruskal;
    int tans = 1<<30;
    for (int i = 1; i <= m; ++i)
    {
        if (A[i].used) continue;
        int u = A[i].from, v = A[i].to;
        if(u == v) continue;
        Seg::node res = Dec::askmax(u,v);
        if (res.maxx == A[i].val && res.secx != 0) tans = std::min(tans, A[i].val - res.secx);
        else if (res.maxx != A[i].val) tans = std::min(tans, A[i].val - res.maxx);
    }
    printf("%lld\n", treeans + tans);
    return 0;
}