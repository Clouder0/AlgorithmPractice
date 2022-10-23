#include <cstdio>
using namespace std;
const int maxn = 2e5 + 100;
template <typename T>
inline void swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}
template <typename T>
inline void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
struct node
{
    int to, next;
} E[maxn];
int head[maxn];
inline void addEdge(const int &x, const int &y)
{
    static int tot = 0;
    E[++tot] = (node){y, head[x]}, head[x] = tot;
}
int n, m, r, mod;
int w[maxn], deep[maxn], fa[maxn], size[maxn], son[maxn];
int sum[maxn << 2], tag[maxn << 2];
int id[maxn], wt[maxn], top[maxn], cnt;
int ll, rr, k;
inline void push_up(const int &p)
{
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
    sum[p] %= mod;
}
inline void push_down(const int &l, const int &r, const int &p)
{
    if (!tag[p])
        return;
    int mid = (l + r) >> 1;
    tag[p << 1] += tag[p];
    sum[p << 1] += (mid - l + 1) * tag[p];
    tag[p << 1 | 1] += tag[p];
    sum[p << 1 | 1] += (r - mid) * tag[p];
    tag[p] = 0;
    sum[p << 1] %= mod;
    sum[p << 1 | 1] %= mod;
}
void build(const int &l, const int &r, const int &p)
{
    if (l == r)
    {
        sum[p] = wt[l];
        if (sum[p] > mod)
            sum[p] %= mod;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
    push_up(p);
}
int ask(const int &l, const int &r, const int &p)
{
    if (ll <= l && rr >= r)
        return sum[p];
    push_down(l, r, p);
    int mid = (l + r) >> 1;
    int ans = 0;
    if (ll <= mid)
        ans = ask(l, mid, p << 1) % mod;
    if (rr > mid)
        ans = (ans + ask(mid + 1, r, p << 1 | 1)) % mod;
    return ans;
}
void add(const int &l, const int &r, const int &p)
{
    if (ll <= l && rr >= r)
    {
        sum[p] += k * (r - l + 1);
        tag[p] += k;
        sum[p] %= mod;
        tag[p] %= mod;
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
void dfs1(int u, int from, int depth)
{
    deep[u] = depth;
    fa[u] = from;
    size[u] = 1;
    int v, maxx = -1;
    for (int p = head[u]; p; p = E[p].next)
    {
        v = E[p].to;
        if (v == from)
            continue;
        dfs1(v, u, depth + 1);
        size[u] += size[v];
        if (size[v] > maxx)
            maxx = size[v], son[u] = v;
    }
}
void dfs2(int u, int topfa)
{
    id[u] = ++cnt;
    wt[cnt] = w[u];
    top[u] = topfa;
    if (!son[u])
        return;
    dfs2(son[u], topfa);
    int v;
    for (int p = head[u]; p; p = E[p].next)
    {
        v = E[p].to;
        if (v == son[u] || v == fa[u])
            continue;
        dfs2(v, v);
    }
}
inline int qRange(int x, int y)
{
    int ans = 0;
    while (top[x] != top[y])
    {
        if (deep[top[x]] < deep[top[y]])
            swap(x, y);
        ll = id[top[x]];
        rr = id[x];
        ans += ask(1, n, 1);
        ans %= mod;
        x = fa[top[x]];
    }
    if (deep[x] > deep[y])
        swap(x, y);
    ll = id[x];
    rr = id[y];
    ans += ask(1, n, 1);
    return ans % mod;
}
inline int qSon(int x)
{
    ll = id[x];
    rr = id[x] + size[x] - 1;
    return ask(1, n, 1) % mod;
}
inline void updateRange(int x, int y, int val)
{
    val %= mod;
    while (top[x] != top[y])
    {
        if (deep[top[x]] < deep[top[y]])
            swap(x, y);
        ll = id[top[x]];
        rr = id[x];
        k = val;
        add(1, n, 1);
        x = fa[top[x]];
    }
    if (deep[x] > deep[y])
        swap(x, y);
    ll = id[x];
    rr = id[y];
    k = val;
    add(1, n, 1);
}
inline void updateSon(int x, int val)
{
    val %= mod;
    ll = id[x];
    rr = id[x] + size[x] - 1;
    k = val;
    add(1, n, 1);
}
int main()
{
    read(n);
    read(m);
    read(r);
    read(mod);
    for (int i = 1; i <= n; ++i)
        read(w[i]);
    int a, b;
    for (int i = 1; i < n; ++i)
    {
        read(a);
        read(b);
        addEdge(a, b);
        addEdge(b, a);
    }
    dfs1(r, 0, 1);
    dfs2(r, r);
    build(1, n, 1);
    int opt;
    for (int i = 1; i <= m; ++i)
    {
        read(opt);
        read(a);
        if (opt == 1)
        {
            read(b);
            read(k);
            updateRange(a, b, k);
        }
        else if (opt == 2)
        {
            read(b);
            printf("%d\n", qRange(a, b));
        }
        else if (opt == 3)
        {
            read(k);
            updateSon(a, k);
        }
        else
            printf("%d\n", qSon(a));
    }
    return 0;
}