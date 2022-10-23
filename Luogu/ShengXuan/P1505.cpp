#include <cstdio>
const int maxn = 2e5 + 100;
template <typename T>
inline T _min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
inline T _max(const T &a, const T &b) { return a > b ? a : b; }
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
int wt[maxn];
}
namespace SegmentTree
{
struct node
{
    int l, r, mid;
    int sum, tag, maxx, minn;
} a[maxn << 2];
inline void push_up(const int &p)
{
    a[p].sum = a[p << 1].sum + a[p << 1 | 1].sum;
    a[p].maxx = _max(a[p << 1].maxx, a[p << 1 | 1].maxx);
    a[p].minn = _min(a[p << 1].minn, a[p << 1 | 1].minn);
}
inline void push_down(const int &p)
{
    node &now = a[p], &ls = a[p << 1], &rs = a[p << 1 | 1];
    if (!now.tag)
        return;
    ls.tag ^= 1;
    ls.sum *= -1;
    _swap(ls.maxx, ls.minn);
    ls.maxx *= -1;
    ls.minn *= -1;

    rs.tag ^= 1;
    rs.sum *= -1;
    _swap(rs.maxx, rs.minn);
    rs.maxx *= -1;
    rs.minn *= -1;
    now.tag = 0;
}
void build(const int &l, const int &r, const int &p)
{
    a[p].l = l, a[p].r = r, a[p].mid = l + r >> 1;
    a[p].tag = 0;
    if (l == r)
    {
        a[p].sum = a[p].maxx = a[p].minn = Decomposition::wt[l];
        return;
    }
    build(l, a[p].mid, p << 1);
    build(a[p].mid + 1, r, p << 1 | 1);
    push_up(p);
}
int ask(const int &p, const int &ll, const int &rr)
{
    if (ll <= a[p].l && rr >= a[p].r)
        return a[p].sum;
    push_down(p);
    int res = 0;
    if (ll <= a[p].mid)
        res += ask(p << 1, ll, rr);
    if (rr > a[p].mid)
        res += ask(p << 1 | 1, ll, rr);
    return res;
}
int askMin(const int &p, const int &ll, const int &rr)
{
    if (ll <= a[p].l && rr >= a[p].r)
        return a[p].minn;
    push_down(p);
    int res = 1 << 30;
    if (ll <= a[p].mid)
        res = _min(res, askMin(p << 1, ll, rr));
    if (rr > a[p].mid)
        res = _min(res, askMin(p << 1 | 1, ll, rr));
    //printf("L[%d],R[%d],minn[%d]\n",a[p].l,a[p].r,res);
    return res;
}
int askMax(const int &p, const int &ll, const int &rr)
{
    if (ll <= a[p].l && rr >= a[p].r)
        return a[p].maxx;
    push_down(p);
    int res = 1 << 31;
    if (ll <= a[p].mid)
        res = _max(res, askMax(p << 1, ll, rr));
    if (rr > a[p].mid)
        res = _max(res, askMax(p << 1 | 1, ll, rr));
    return res;
}
void change(const int &p, const int &tar, const int &k)
{
    if (a[p].l == a[p].r)
    {
        a[p].sum = a[p].maxx = a[p].minn = k;
        return;
    }
    push_down(p);
    if (tar <= a[p].mid)
        change(p << 1, tar, k);
    else
        change(p << 1 | 1, tar, k);
    push_up(p);
}
void reverse(const int &p, const int &ll, const int &rr)
{
    if (ll <= a[p].l && rr >= a[p].r)
    {
        a[p].sum *= -1;
        _swap(a[p].maxx, a[p].minn);
        a[p].maxx *= -1;
        a[p].minn *= -1;
        a[p].tag ^= 1;
        return;
    }
    push_down(p);
    if (ll <= a[p].mid)
        reverse(p << 1, ll, rr);
    if (rr > a[p].mid)
        reverse(p << 1 | 1, ll, rr);
    push_up(p);
}
} // namespace SegmentTree
namespace Decomposition
{
int fa[maxn], top[maxn], size[maxn], son[maxn], sonv[maxn], dep[maxn], id[maxn], w[maxn], cnt;
void dfs1(int u)
{
    size[u] = 1;
    dep[u] = dep[fa[u]] + 1;
    int v;
    for (int p = Graph::head[u]; p; p = Graph::E[p].next)
    {
        v = Graph::E[p].to;
        if (v == fa[u])
            continue;
        fa[v] = u;
        w[v] = Graph::E[p].val;
        dfs1(v);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v, sonv[u] = Graph::E[p].val;
    }
}
void dfs2(int u, int topfa)
{
    id[u] = ++cnt;
    top[u] = topfa;
    wt[cnt] = w[u];
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
int askSum(int x, int y)
{
    int res = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            _swap(x, y);
        res += SegmentTree::ask(1, id[top[x]], id[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        _swap(x, y);
    if (x == y)
        return res;
    res += SegmentTree::ask(1, id[x] + 1, id[y]);
    return res;
}
int askMax(int x, int y)
{
    int res = 1 << 31;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            _swap(x, y);
        res = _max(res, SegmentTree::askMax(1, id[top[x]], id[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        _swap(x, y);
    if (x == y)
        return res;
    res = _max(res, SegmentTree::askMax(1, id[x] + 1, id[y]));
    return res;
}
int askMin(int x, int y)
{
    int res = 1 << 30;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            _swap(x, y);
        int temp = 
        res = _min(SegmentTree::askMin(1, id[top[x]], id[x]),res);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        _swap(x, y);
    if (x == y)
        return res;
    int temp = 
    res = _min(SegmentTree::askMin(1, id[x] + 1, id[y]),res);
    return res;
}
void reverse(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            _swap(x, y);
        SegmentTree::reverse(1, id[top[x]], id[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        _swap(x, y);
    if (x == y)
        return;
    SegmentTree::reverse(1, id[x] + 1, id[y]);
}
} // namespace Decomposition
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
int main()
{
    read(n);
    int x, y, z;
    for (int i = 1; i < n; ++i)
    {
        read(x);
        read(y);
        read(z);
        ++x, ++y;
        Graph::add(x, y, z);
        Graph::add(y, x, z);
    }
    Decomposition::dfs1(1);
    Decomposition::dfs2(1, 1);
    SegmentTree::build(1, n, 1);
    read(m);
    char s[10];
    while (m--)
    {
        scanf("%s", s + 1);
        read(x);
        read(y);
        if (s[1] == 'C')
        {
            int a = Graph::E[x << 1].to;
            int b = Graph::E[(x << 1) - 1].to;
            if (Decomposition::fa[a] == b)
                SegmentTree::change(1, Decomposition::id[a], y);
            else
                SegmentTree::change(1, Decomposition::id[b], y);
        }
        else if (s[1] == 'N')
        {
            ++x, ++y;
            Decomposition::reverse(x, y);
        }
        else if (s[1] == 'S')
        {
            ++x, ++y;
            printf("%d\n", Decomposition::askSum(x, y));
        }
        else if (s[2] == 'I')
        {
            ++x, ++y;
            printf("%d\n", Decomposition::askMin(x, y));
        }
        else if (s[2] == 'A')
        {
            ++x, ++y;
            printf("%d\n", Decomposition::askMax(x, y));
        }
    }
    return 0;
}