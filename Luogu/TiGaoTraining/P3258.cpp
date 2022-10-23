#include <cstdio>
#include <algorithm>
const int maxn = 5e5 + 10;
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
    E[++tot].next = head[x];
    E[tot].to = y;
    head[x] = tot;
}
} // namespace Graph
int n, m;
namespace SegmentTree
{
int sum[maxn << 2], tag[maxn << 2];
inline void push_up(const int &p)
{
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}
inline void push_down(const int &l, const int &r, const int &p)
{
    if (!tag[p])
        return;
    int mid = l + r >> 1;
    sum[p << 1] += (mid - l + 1) * tag[p];
    tag[p << 1] += tag[p];
    sum[p << 1 | 1] += (r - mid) * tag[p];
    tag[p << 1 | 1] += tag[p];
    tag[p] = 0;
}
void modify(const int &l, const int &r, const int &p, const int &ll, const int &rr, const int &k)
{
    if (ll <= l && rr >= r)
    {
        sum[p] += (r - l + 1) * k;
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
int ask(const int &l, const int &r, const int &p, const int &tar)
{
    if (l == r)
        return sum[p];
    push_down(l, r, p);
    int mid = l + r >> 1;
    if (tar <= mid)
        return ask(l, mid, p << 1, tar);
    else
        return ask(mid + 1, r, p << 1 | 1, tar);
}
} // namespace SegmentTree
namespace Decomposition
{
int son[maxn], fa[maxn], top[maxn], size[maxn], dep[maxn], id[maxn], cnt;
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
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
void dfs2(int u, int topfa)
{
    id[u] = ++cnt;
    top[u] = topfa;
    if (!son[u])
        return;
    dfs2(son[u], topfa);
    int v;
    for (int p = Graph::head[u]; p; p = Graph::E[p].next)
    {
        v = Graph::E[p].to;
        if (v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
}
void add(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            std::swap(x, y);
        SegmentTree::modify(1, n, 1, id[top[x]], id[x], 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        std::swap(x, y);
    SegmentTree::modify(1, n, 1, id[x], id[y], 1);
}
} // namespace Decomposition
const int bufSize = 100000;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = nc(); c > '9' || c < '0'; c = nc());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = nc());
}
int a[maxn];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    int x, y;
    for (int i = 1; i < n; ++i)
    {
        read(x);
        read(y);
        Graph::add(x, y);
        Graph::add(y, x);
    }
    Decomposition::dfs1(1);
    Decomposition::dfs2(1, 1);
    for (int i = 1; i < n; ++i)
        Decomposition::add(a[i], a[i + 1]), SegmentTree::modify(1, n, 1, Decomposition::id[a[i + 1]], Decomposition::id[a[i + 1]], -1);
    for (int i = 1; i <= n; ++i)
        printf("%d\n", SegmentTree::ask(1, n, 1, Decomposition::id[i]));
    return 0;
}