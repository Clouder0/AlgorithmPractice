#include <algorithm>
#include <cstdio>

const int maxn = 1e5 + 10;
int n, m, mod;
namespace Graph
{
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], w[maxn];
int Enum;
inline void add(const int& x, const int& y)
{
    E[++Enum].to = y;
    E[Enum].next = head[x];
    head[x] = Enum;
}
}  // namespace Graph
namespace Decomposition
{
int dep[maxn], top[maxn], fa[maxn], size[maxn], son[maxn], wt[maxn];
}
namespace SegmentTree
{
long long sum[maxn << 2], tag[maxn << 2];
inline void push_up(const int& p)
{
    sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % mod;
}
inline void push_down(const int& l, const int& r, const int& p)
{
    if (!tag[p])
        return;
    int mid = l + r >> 1;
    sum[p << 1] += (mid - l + 1) * tag[p];
    sum[p << 1] %= mod;
    sum[p << 1 | 1] += (r - mid) * tag[p];
    sum[p << 1 | 1] %= mod;
    tag[p << 1] += tag[p];
    tag[p << 1] %= mod;
    tag[p << 1 | 1] += tag[p];
    tag[p << 1 | 1] %= mod;
    tag[p] = 0;
}
void build(const int& l, const int& r, const int& p)
{
    if (l == r)
    {
        sum[p] = Decomposition::wt[l];
        return;
    }
    int mid = l + r >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
    push_up(p);
}
long long ask(const int& l, const int& r, const int& p, const int& ll, const int& rr)
{
    if (ll <= l && rr >= r)
        return sum[p];
    push_down(l, r, p);
    int mid = l + r >> 1;
    long long ans = 0;
    if (ll <= mid)
        ans += ask(l, mid, p << 1, ll, rr);
    if (rr > mid)
        ans += ask(mid + 1, r, p << 1 | 1, ll, rr);
    return ans % mod;
}
void modify(const int& l, const int& r, const int& p, const int& ll, const int& rr, const int& k)
{
    if (ll <= l && rr >= r)
    {
        sum[p] += k * (r - l + 1);
        tag[p] += k;
        return;
    }
    push_down(l, r, p);
    int mid = l + r >> 1;
    if (ll <= mid)
        modify(l, mid, p << 1, ll, rr, k);
    if (rr > mid)
        modify(mid + 1, r, p << 1 | 1, ll, rr, k);
    push_up(p);
}
}  // namespace SegmentTree
namespace Decomposition
{
void dfs1(int u)
{
    dep[u] = dep[fa[u]] + 1;
    size[u] = 1;
    int v;
    for (int p = Graph::head[u]; p; p = Graph::E[p].next)
    {
        v = Graph::E[p].to;
        if (v == fa[u])
            continue;
        fa[v] = u;
        dfs1(v);
        size[u] += size[v];
        if (size[v] > size[son[u]])
            son[u] = v;
    }
}
int id[maxn], cnt;
void dfs2(int u, int topf)
{
    id[u] = ++cnt;
    wt[cnt] = Graph::w[u];
    top[u] = topf;
    if (!son[u])
        return;
    dfs2(son[u], topf);
    int v;
    for (int p = Graph::head[u]; p; p = Graph::E[p].next)
    {
        v = Graph::E[p].to;
        if (v == son[u] || v == fa[u])
            continue;
        dfs2(v, v);
    }
}
inline void addRange(int x, int y, int k)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            std::swap(x, y);
        SegmentTree::modify(1, n, 1, id[top[x]], id[x], k);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        std::swap(x, y);
    SegmentTree::modify(1, n, 1, id[x], id[y], k);
}
inline long long askRange(int x, int y)
{
    long long res = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            std::swap(x, y);
        res += SegmentTree::ask(1, n, 1, id[top[x]], id[x]);
        res %= mod;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        std::swap(x, y);
    res += SegmentTree::ask(1, n, 1, id[x], id[y]);
    return res % mod;
}
inline void addSon(int x, int k)
{
    SegmentTree::modify(1, n, 1, id[x], id[x] + size[x] - 1, k);
}
inline long long askSon(int x)
{
    return SegmentTree::ask(1, n, 1, id[x], id[x] + size[x] - 1);
}
}  // namespace Decomposition
template <typename T>
void read(T& r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
int root;
int main()
{
    read(n);
    read(m);
    read(root);
    read(mod);
    for (int i = 1; i <= n; ++i)
        read(Graph::w[i]);
    int x, y;
    for (int i = 1; i < n; ++i)
    {
        read(x);
        read(y);
        Graph::add(x, y);
        Graph::add(y, x);
    }
    Decomposition::dfs1(root);
    Decomposition::dfs2(root, root);
    SegmentTree::build(1, n, 1);
    int t, z;
    while (m--)
    {
        read(t);
        read(x);
        if (t == 1)
        {
            read(y);
            read(z);
            Decomposition::addRange(x, y, z % mod);
        }
        else if (t == 2)
        {
            read(y);
            printf("%lld\n", Decomposition::askRange(x, y));
        }
        else if (t == 3)
        {
            read(z);
            Decomposition::addSon(x, z % mod);
        }
        else
            printf("%lld\n", Decomposition::askSon(x));
    }
    return 0;
}