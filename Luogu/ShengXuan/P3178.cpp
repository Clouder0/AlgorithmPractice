#include <cstdio>
using namespace std;
const int maxn = 5e5 + 100;
int w[maxn];
int n, m;
namespace SegmentTree
{
long long sum[maxn << 2], tag[maxn << 2];
int ll, rr, k;
} // namespace SegmentTree
namespace HeavyDecomposition
{
int nw[maxn], fa[maxn], dep[maxn], son[maxn], size[maxn];
}
template <typename T>
inline void read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar()) if (c == '-') flag = -1;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
    r *= flag;
}
template <typename T>
inline void swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}
namespace Graph
{
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
int tot = 0;
inline void add(const int &x, const int &y)
{
    E[++tot] = (node){y, head[x]}, head[x] = tot;
}
} // namespace Graph
namespace SegmentTree
{
inline void push_up(const int &p)
{
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}
inline void push_down(const int &l, const int &r, const int &p)
{
    if (!tag[p])
        return;
    int ls = p << 1, rs = p << 1 | 1;
    int mid = (l + r) >> 1;
    tag[ls] = tag[ls] + tag[p];
    tag[rs] = tag[rs] + tag[p];
    sum[ls] = sum[ls] + (mid - l + 1) * tag[p];
    sum[rs] = sum[rs] + (r - mid) * tag[p];
    tag[p] = 0;
}
void build(const int &l, const int &r, const int &p)
{
    if (l == r)
    {
        sum[p] = HeavyDecomposition::nw[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
    push_up(p);
}
void add(const int &l, const int &r, const int &p)
{
    if (ll <= l && rr >= r)
    {
        tag[p] = tag[p] + k;
        sum[p] = sum[p] + (long long)(r - l + 1) * k;
        return;
    }
    push_down(l, r, p);
    int mid = (l + r) >> 1;
    if (ll <= mid)
        add(l, mid, p << 1);
    if (rr > mid)
        add(mid + 1, r, p << 1 | 1);
    push_up(p);
}
long long ask(const int &l, const int &r, const int &p)
{
    if (ll <= l && rr >= r)
        return sum[p];
    push_down(l, r, p);
    int mid = (l + r) >> 1;
    long long ans = 0;
    if (ll <= mid)
        ans = ask(l, mid, p << 1);
    if (rr > mid)
        ans += ask(mid + 1, r, p << 1 | 1);
    return ans;
}
} // namespace SegmentTree
namespace HeavyDecomposition
{
using namespace Graph;
void dfs1(int u, int from, int deep)
{
    dep[u] = deep;
    fa[u] = from;
    size[u] = 1;
    int v, maxx = -1;
    for (int p = head[u]; p; p = E[p].next)
    {
        v = E[p].to;
        if (v == from)
            continue;
        dfs1(v, u, deep + 1);
        size[u] += size[v];
        if (size[v] > maxx)
            son[u] = v, maxx = size[v];
    }
}
int top[maxn], id[maxn], cnt;
void dfs2(int u, int topf)
{
    id[u] = ++cnt;
    nw[cnt] = w[u];
    top[u] = topf;
    if (!son[u])
        return;
    dfs2(son[u], topf);
    int v;
    for (int p = head[u]; p; p = E[p].next)
    {
        v = E[p].to;
        if (v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
}
using namespace SegmentTree;
inline void addPoint(int x, int val)
{
    ll = id[x], rr = id[x], k = val;
    add(1, n, 1);
}
inline long long askRange(int x, int y)
{
    long long ans = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ll = id[top[x]];
        rr = id[x];
        ans += ask(1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ll = id[x];
    rr = id[y];
    ans += ask(1, n, 1);
    return ans;
}
inline void addSon(int x, int val)
{
    ll = id[x];
    rr = id[x] + size[x] - 1;
    k = val;
    add(1, n, 1);
}
} // namespace HeavyDecomposition
int main()
{
    read(n);
    read(m);
    int opt, a, b, c;
    for (int i = 1; i <= n; ++i)
        read(w[i]);
    for (int i = 1; i < n; ++i)
        read(a), read(b), Graph::add(a, b), Graph::add(b, a);
    HeavyDecomposition::dfs1(1, 1, 1);
    HeavyDecomposition::dfs2(1, 1);
    SegmentTree::build(1, n, 1);
    while (m--)
    {
        read(opt);
        read(a);
        if (opt == 1)
            read(b), HeavyDecomposition::addPoint(a, b);
        else if (opt == 2)
            read(b), HeavyDecomposition::addSon(a, b);
        else
            printf("%lld\n", HeavyDecomposition::askRange(1, a));
    }
    return 0;
}