#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
template <typename T>
inline T _max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
inline void _swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}
template <typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar()) if (c == '-') flag = -1;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
    return r *= flag;
}
const int maxn = 3e5 + 1000;
int n, m;
namespace Graph
{
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
int w[maxn];
int tot;
inline void add(const int &x, const int &y)
{
    E[++tot] = (node){y, head[x]}, head[x] = tot;
}
} // namespace Graph
namespace Decomposition
{
int wt[maxn];
}
namespace SegTree
{
int sum[maxn << 2], maxx[maxn << 2];
inline void push_up(const int &p)
{
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
    maxx[p] = _max(maxx[p << 1], maxx[p << 1 | 1]);
}
void build(const int &l, const int &r, const int &p)
{
    if (l == r)
    {
        sum[p] = maxx[p] = Decomposition::wt[l];
        return;
    }
    int mid = l + r >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
    push_up(p);
}
int target, val;
void change(const int &l, const int &r, const int &p)
{
    if (l == r)
    {
        sum[p] = maxx[p] = val;
        return;
    }
    int mid = l + r >> 1;
    if (target <= mid)
        change(l, mid, p << 1);
    else
        change(mid + 1, r, p << 1 | 1);
    push_up(p);
}
int ll, rr;
int askSum(const int &l, const int &r, const int &p)
{
    if (ll <= l && rr >= r)
        return sum[p];
    int mid = l + r >> 1;
    int ans = 0;
    if (ll <= mid)
        ans = askSum(l, mid, p << 1);
    if (rr > mid)
        ans += askSum(mid + 1, r, p << 1 | 1);
    return ans;
}
int askMax(const int &l, const int &r, const int &p)
{
    if (ll <= l && rr >= r)
        return maxx[p];
    int mid = l + r >> 1;
    int ans = -(1 << 30);
    if (ll <= mid)
        ans = askMax(l, mid, p << 1);
    if (rr > mid)
        ans = _max(ans, askMax(mid + 1, r, p << 1 | 1));
    return ans;
}
} // namespace SegTree
namespace Decomposition
{
using namespace Graph;
int fa[maxn], size[maxn], son[maxn], dep[maxn];
void dfs1(const int &u)
{
    size[u] = 1;
    int v;
    for (int p = head[u]; p; p = E[p].next)
    {
        v = E[p].to;
        if (v == fa[u])
            continue;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs1(v);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
int id[maxn], top[maxn], cnt;
void dfs2(int u, int topf)
{
    id[u] = ++cnt;
    wt[cnt] = Graph::w[u];
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
using namespace SegTree;
inline int QMAX(int x, int y)
{
    int ans = -(1 << 30);
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            _swap(x, y);
        ll = id[top[x]];
        rr = id[x];
        ans = _max(ans, askMax(1, n, 1));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        _swap(x, y);
    ll = id[x];
    rr = id[y];
    ans = _max(ans, askMax(1, n, 1));
    return ans;
}
inline int QSUM(int x, int y)
{
    int ans = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            _swap(x, y);
        ll = id[top[x]];
        rr = id[x];
        ans += askSum(1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        _swap(x, y);
    ll = id[x];
    rr = id[y];
    ans += askSum(1, n, 1);
    return ans;
}
} // namespace Decomposition
int main()
{
    read(n);
    int a, b;
    for (int i = 1; i < n; ++i)
        read(a), read(b), Graph::add(a, b), Graph::add(b, a);
    for (int i = 1; i <= n; ++i)
        read(Graph::w[i]);
    Decomposition::dfs1(1);
    Decomposition::dfs2(1, 1);
    SegTree::build(1, n, 1);
    read(m);
    string opt;
    while (m--)
    {
        cin >> opt;
        read(a);
        read(b);
        if (opt == "CHANGE")
        {
            SegTree::target = Decomposition::id[a];
            SegTree::val = b;
            SegTree::change(1, n, 1);
        }
        else if (opt == "QMAX")
        {
            printf("%d\n", Decomposition::QMAX(a, b));
        }
        else
            printf("%d\n", Decomposition::QSUM(a, b));
    }
    return 0;
}