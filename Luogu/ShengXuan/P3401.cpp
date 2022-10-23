#include <cstdio>
#include <algorithm>
const int maxn = 3e4 + 10;
template <typename T>
inline void _swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}
int n, m;
namespace Graph
{
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x, const int &y, const int &val)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].val = val;
    E[tot].next = head[x];
    head[x] = tot;
}
} // namespace Graph
namespace Decomposition
{
int w[maxn], tur[maxn];
}
namespace SegmentTree
{
int sum[12][maxn << 2], tag[12][maxn << 2];
inline void push_up(const int &p, const int &bit)
{
    sum[bit][p] = sum[bit][p << 1] + sum[bit][p << 1 | 1];
}
inline void push_down(const int &l, const int &r, const int &p, const int &bit)
{
    if (!tag[bit][p])
        return;
    int mid = l + r >> 1;
    sum[bit][p << 1] = (mid - l + 1) - sum[bit][p << 1];
    tag[bit][p << 1] ^= 1;
    sum[bit][p << 1 | 1] = (r - mid) - sum[bit][p << 1 | 1];
    tag[bit][p << 1 | 1] ^= 1;
    tag[bit][p] = 0;
}
void reverse(const int &l, const int &r, const int &p, const int &ll, const int &rr, const int &bit)
{
    if (ll <= l && rr >= r)
    {
        sum[bit][p] = r - l + 1 - sum[bit][p];
        tag[bit][p] ^= 1;
        return;
    }
    push_down(l, r, p, bit);
    int mid = l + r >> 1;
    if (ll <= mid)
        reverse(l, mid, p << 1, ll, rr, bit);
    if (rr > mid)
        reverse(mid + 1, r, p << 1 | 1, ll, rr, bit);
    push_up(p, bit);
}
int ask(const int &l, const int &r, const int &p, const int &ll, const int &rr, const int &bit)
{
    if (ll <= l && rr >= r)
        return sum[bit][p];
    push_down(l, r, p, bit);
    int mid = l + r >> 1;
    int res = 0;
    if (ll <= mid)
        res += ask(l, mid, p << 1, ll, rr, bit);
    if (rr > mid)
        res += ask(mid + 1, r, p << 1 | 1, ll, rr, bit);
    return res;
}
void build(const int &l, const int &r, const int &p)
{
    if (l == r)
    {
        for (int i = 0; i <= 10; ++i)
            sum[i][p] = (Decomposition::w[Decomposition::tur[l]] >> i) & 1;
        return;
    }
    int mid = l + r >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
    for (int i = 0; i <= 10; ++i)
        push_up(p, i);
}
} // namespace SegmentTree
namespace Decomposition
{
int vf[maxn], top[maxn], fa[maxn], size[maxn], son[maxn], dep[maxn], cnt;
void dfs(int u)
{
    size[u] = 1;
    int v;
    for (int p = Graph::head[u]; p; p = Graph::E[p].next)
    {
        v = Graph::E[p].to;
        if (v == fa[u])
            continue;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        w[v] = w[u] ^ Graph::E[p].val;
        vf[v] = Graph::E[p].val;
        dfs(v);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
int id[maxn];
void dfs2(int u)
{
    tur[id[u] = ++cnt] = u;
    if (!son[u])
        return;
    top[son[u]] = top[u];
    dfs2(son[u]);
    int v;
    for (int p = Graph::head[u]; p; p = Graph::E[p].next)
    {
        v = Graph::E[p].to;
        if (v == fa[u] || v == son[u])
            continue;
        top[v] = v;
        dfs2(v);
    }
}
long long askSum(int x, int y)
{
    int sx = x, sy = y;
    long long res = 0;
    for (int i = 0; i <= 10; ++i)
    {
        long long one = 0, all = 0;
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                _swap(x, y);
            one += SegmentTree::ask(1, n, 1, id[top[x]], id[x], i);
            all += id[x] - id[top[x]] + 1;
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            _swap(x, y);
        one += SegmentTree::ask(1, n, 1, id[x], id[y], i);
        all += id[y] - id[x] + 1;
        res += one * (all - one) * (1 << i);
        x = sx, y = sy;
    }
    return res;
}
void update(int u, int v, int w)
{
    int x = dep[u] < dep[v] ? v : u;
    for (int i = 0; i <= 10; ++i)
        if ((vf[x] ^ w) & (1 << i))
            SegmentTree::reverse(1, n, 1, id[x], id[x] + size[x] - 1, i);
    vf[x] = w;
}
} // namespace Decomposition
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
int main()
{
    read(n);
    read(m);
    int x, y, z;
    for (int i = 1; i < n; ++i)
    {
        read(x);
        read(y);
        read(z);
        Graph::add(x, y, z);
        Graph::add(y, x, z);
    }
    Decomposition::dfs(1);
    Decomposition::top[1] = 1;
    Decomposition::dfs2(1);
    SegmentTree::build(1, n, 1);
    while (m--)
    {
        read(x);
        read(y);
        read(z);
        if (x == 1)
        {
            printf("%lld\n", Decomposition::askSum(y, z));
        }
        else
        {
            int k;
            read(k);
            Decomposition::update(y, z, k);
        }
    }
    return 0;
}