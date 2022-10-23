#include <cstdio>
#include <algorithm>
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar()) if (c == '-') flag = -1;
    for (; c >= '0' && c <= '9'; c = getchar()) r = r * 10 + c - 48;
    r *= flag;
}
const int maxn = 1e5 + 100;
int n, m;
int w[maxn];
namespace Graph
{
    struct node
    {
        int to, next;
    } E[maxn << 1];
    int head[maxn];
    inline void add(const int &x, const int &y)
    {
        static int tot = 0;
        E[++tot].next = head[x], head[x] = tot, E[tot].to = y;
    }
} // namespace Graph
namespace Dec
{
    int id[maxn];
}
namespace Seg
{
    struct node
    {
        int len, l, r, lmax, rmax, mmax, sum, tag;
        node() { len = l = r = lmax = rmax = mmax = sum = tag = 0; }
    } A[maxn << 2];
    inline void pushup(node &now, node ls, node rs)
    {
        now.sum = ls.sum + rs.sum;
        now.lmax = max(ls.lmax, ls.sum + rs.lmax);
        now.rmax = max(rs.rmax, rs.sum + ls.rmax);
        now.mmax = max(ls.mmax, rs.mmax);
        now.mmax = max(ls.rmax + rs.lmax, now.mmax);
    }
    inline void pushdown(node &now, node &ls, node &rs)
    {
        if (now.tag == -10001) return;
        ls.lmax = ls.rmax = ls.mmax = ls.sum = now.tag * ls.len;
        rs.lmax = rs.rmax = rs.mmax = rs.sum = now.tag * rs.len;
        ls.tag = rs.tag = now.tag;
        now.tag = -10001;
    }
    void build(const int &l, const int &r, const int &p)
    {
        A[p].l = l, A[p].r = r, A[p].tag = -10001, A[p].len = r - l + 1;
        if (l == r) return (void)(A[p].lmax = A[p].rmax = A[p].mmax = A[p].sum = w[Dec::id[l]]);
        int mid = l + r >> 1;
        build(l, mid, p << 1), build(mid + 1, r, p << 1 | 1);
        pushup(A[p], A[p << 1], A[p << 1 | 1]);
    }
    node ask(const int &p, const int &ll, const int &rr)
    {
        if(ll > rr) return node();
        node &now = A[p], &ls = A[p << 1], &rs = A[p << 1 | 1];
        if (now.l >= ll && now.r <= rr) return now;
        pushdown(now, ls, rs);
        if (ll <= ls.r && rr >= rs.l)
        {
            node left = ask(p << 1, ll, rr), right = ask(p << 1 | 1, ll, rr), ans;
            pushup(ans, left, right);
            return ans;
        }
        else if (ll <= ls.r) return ask(p << 1, ll, rr);
        return ask(p << 1 | 1, ll, rr);
    }
    void modify(const int &p, const int &ll, const int &rr, const int &k)
    {
        if(ll > rr) return;
        node &now = A[p], &ls = A[p << 1], &rs = A[p << 1 | 1];
        if (now.l >= ll && now.r <= rr)
        {
            now.lmax = now.rmax = now.mmax = now.sum = now.len * k;
            now.tag = k;
            return;
        }
        pushdown(now, ls, rs);
        if (ll <= ls.r) modify(p << 1, ll, rr, k);
        if (rr >= rs.l) modify(p << 1 | 1, ll, rr, k);
        pushup(now, ls, rs);
    }
} // namespace Seg
namespace Dec
{
    int size[maxn], fa[maxn], son[maxn], dep[maxn], top[maxn], dfn[maxn], cnt;
    using namespace Graph;
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
    void modify(int x, int y, int k)
    {
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
            Seg::modify(1, dfn[top[x]], dfn[x], k);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y]) std::swap(x, y);
        Seg::modify(1, dfn[x], dfn[y], k);
    }
    int ask(int x, int y)
    {
        Seg::node L,R;
        int p = 0;
        while (top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]])
            {
                Seg::pushup(R,Seg::ask(1,dfn[top[y]],dfn[y]),R);
                y = fa[top[y]];
            }
            else 
            {
                Seg::pushup(L, Seg::ask(1, dfn[top[x]], dfn[x]), L);
                x = fa[top[x]];
            }
        }
        if (dep[x] > dep[y]) Seg::pushup(L,Seg::ask(1,dfn[y],dfn[x]),L);
        else Seg::pushup(R,Seg::ask(1,dfn[x],dfn[y]),R);
        int ans = 0;
        ans = max(L.mmax,R.mmax);
        ans = max(L.lmax + R.lmax,ans);
        return ans;
    }
} // namespace Dec
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(w[i]);
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        read(x), read(y), Graph::add(x, y), Graph::add(y, x);
    }
    Dec::dfs1(1), Dec::top[1] = 1, Dec::dfs2(1);
    Seg::build(1, n, 1);
    read(m);
    while (m--)
    {
        int opt, a, b, c;
        read(opt), read(a), read(b);
        if (opt == 1) printf("%d\n", Dec::ask(a, b));
        else read(c), Dec::modify(a, b, c);
    }
    return 0;
}