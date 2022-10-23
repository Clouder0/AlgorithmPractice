#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
template<typename T>
inline T _max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
inline void _swap(T &a,T &b)
{
    T t = a;
    a = b;
    b = t;
}
template<typename T>
inline T read(T &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
    return r;
}
const int maxn = 5e5 + 1000;
int n, m;
namespace Graph
{
    struct node
    {
        int to, next, val;
    } E[maxn << 1];
    int head[maxn];
    int tot;
    inline void add(const int &x, const int &y, const int &val)
    {
        E[++tot] = (node){y, head[x], val}, head[x] = tot;
    }
} // namespace Graph
namespace HeavyDecomposition
{
    int wt[maxn];
}
namespace SegmentTree
{
    struct node
    {
        int max, add, set;
    } a[maxn << 2];
    inline void push_up(const int &p)
    {
        a[p].max = _max(a[p << 1].max, a[p << 1 | 1].max);
    }
    inline void push_down(const int &p)
    {
        node &now = a[p], &ls = a[p << 1], &rs = a[p << 1 | 1];
        if (now.set != -1)
        {
            ls.set = rs.set = now.set;
            ls.max = rs.max = now.set;
            ls.add = rs.add = 0;
            now.set = -1;
        }
        if (now.add != 0)
        {
            ls.add += now.add;
            rs.add += now.add;
            ls.max += now.add;
            rs.max += now.add;
            now.add = 0;
        }
    }
    void build(const int &l, const int &r, const int &p)
    {
        a[p].set = -1;
        if (l == r)
        {
            a[p].max = HeavyDecomposition::wt[l];
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
        push_up(p);
    }
    int ll, rr, k;
    int ask(const int &l, const int &r, const int &p)
    {
        if (ll <= l && rr >= r)
            return a[p].max;
        push_down(p);
        int mid = l + r >> 1;
        int ans = -(1 << 30);
        if (ll <= mid)
            ans = ask(l, mid, p << 1);
        if (rr > mid)
            ans = _max(ans, ask(mid + 1, r, p << 1 | 1));
        return ans;
    }
    void modify(const int &l, const int &r, const int &p)
    {
        push_down(p);
        if (ll <= l && rr >= r)
        {
            a[p].max = k;
            a[p].set = k;
            a[p].add = 0;
            return;
        }
        int mid = l + r >> 1;
        if (ll <= mid)
            modify(l, mid, p << 1);
        if (rr > mid)
            modify(mid + 1, r, p << 1 | 1);
        push_up(p);
    }
    void add(const int &l, const int &r, const int &p)
    {
        if (ll <= l && rr >= r)
        {
            a[p].max += k;
            a[p].add += k;
            return;
        }
        push_down(p);
        int mid = l + r >> 1;
        if (ll <= mid)
            add(l, mid, p << 1);
        if (rr > mid)
            add(mid + 1, r, p << 1 | 1);
        push_up(p);
    }
} // namespace SegmentTree
namespace HeavyDecomposition
{
    using namespace Graph;
    int fa[maxn], size[maxn], son[maxn], dep[maxn], w[maxn];
    void dfs1(int u,int from,int deep)
    {
        fa[u] = from;
        dep[u] = deep;
        size[u] = 1;
        int v;
        for (int p = head[u]; p; p = E[p].next)
        {
            v = E[p].to;
            if (v == fa[u])
                continue;
            w[v] = E[p].val;
            dfs1(v,u,deep+1);
            size[u] += size[v];
            if (size[v] > size[son[u]])
                son[u] = v;
        }
    }
    int id[maxn], top[maxn], cnt;
    void dfs2(int u, int topf)
    {
        id[u] = ++cnt;
        wt[cnt] = w[u];
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
    inline void changeRange(int x, int y, int val)
    {
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                _swap(x, y);
            ll = id[top[x]];
            rr = id[x];
            k = val;
            modify(1, n, 1);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            _swap(x, y);
        ll = id[x] + 1;
        rr = id[y];
        k = val;
        modify(1, n, 1);
    }
    inline void addRange(int x, int y, int val)
    {
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                _swap(x, y);
            ll = id[top[x]];
            rr = id[x];
            k = val;
            SegmentTree::add(1, n, 1);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            _swap(x, y);
        ll = id[x] + 1;
        rr = id[y];
        k = val;
        SegmentTree::add(1, n, 1);
    }
    inline int askRange(int x, int y)
    {
        int ans = -(1 << 30);
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                _swap(x, y);
            ll = id[top[x]];
            rr = id[x];
            ans = max(ans, ask(1, n, 1));
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            _swap(x, y);
        ll = id[x] + 1;
        rr = id[y];
        ans = max(ans, ask(1, n, 1));
        return ans;
    }
} // namespace HeavyDecomposition
int X[maxn], Y[maxn];
int main()
{
    read(n);
    int temp;
    for (int i = 1; i < n; ++i)
        read(X[i]), read(Y[i]), read(temp), Graph::add(X[i], Y[i], temp), Graph::add(Y[i], X[i], temp);
    HeavyDecomposition::dfs1(1,1,1);
    HeavyDecomposition::dfs2(1, 1);
    SegmentTree::build(1, n, 1);
    int a, b, c;
    string s;
    using namespace HeavyDecomposition;
    while (true)
    {
        cin >> s;
        if(s == "Stop")
            return 0;
        read(a);
        read(b);
        if(s == "Change")
        {
            int u = X[a],v = Y[a];
            if(dep[u] > dep[v])
                swap(u,v);
            changeRange(u,v, b);
        }
        else if(s == "Cover")
        {
            read(c);
            changeRange(a, b, c);
        }
        else if(s == "Add")
        {
            read(c);
            addRange(a, b, c);
        }
        else
        {
            printf("%d\n", askRange(a, b));
        }
    }
    return 0;
}