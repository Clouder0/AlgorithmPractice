#include <cstdio>
#include <algorithm>
#include <ctype.h>
#include <cstring>
const int bufSize = 1e6;
using std::max;
#define DEBUG
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 5e5 + 100;
int n, m, a[maxn];
struct matrix
{
    int g[2][2];
    matrix() { memset(g, 0, sizeof(g)); }
    matrix operator*(const matrix b) const
    {
        matrix c;
        for (int i = 0; i <= 1; ++i)
            for (int j = 0; j <= 1; ++j)
                for (int k = 0; k <= 1; ++k) c.g[i][k] = max(c.g[i][k], g[i][j] + b.g[j][k]);
        return c;
    }
} A[maxn], g[maxn];
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int fa[maxn], size[maxn], son[maxn], dep[maxn], top[maxn], bot[maxn], dfn[maxn], id[maxn], ind;
int f[maxn][2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(int p) { A[p] = A[ls] * A[rs]; }
void build(int l, int r, int p)
{
    if(l == r) return (void)(A[p] = g[id[l]]);
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(p);
}
void modify(int l, int r, int p, int pos)
{
    if(l == r) return (void)(A[p] = g[id[l]]);
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, ls, pos);
    else modify(mid + 1, r, rs, pos);
    pushup(p);
}
matrix ask(int l, int r, int p, int ll, int rr)
{
    if (l >= ll && r <= rr) return A[p];
    int mid = l + r >> 1;
    if (ll <= mid && rr > mid) return ask(l, mid, ls, ll, rr) * ask(mid + 1, r, rs, ll, rr);
    else if (ll <= mid) return ask(l, mid, ls, ll, rr);
    else return ask(mid + 1, r, rs, ll, rr);
}
void dfs(int u)
{
    size[u] = 1, f[u][1] = a[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1, dfs(v), size[u] += size[v], f[u][1] += f[v][0], f[u][0] += max(f[v][0], f[v][1]);
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    id[dfn[u] = ++ind] = u, bot[top[u]] = u;
    g[u].g[1][0] = a[u], g[u].g[1][1] = -(1 << 30);
    if (!son[u]) return;
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v), g[u].g[0][0] += max(f[v][0], f[v][1]),g[u].g[1][0] += f[v][0];
    }
    g[u].g[0][1] = g[u].g[0][0];
}
void update(int x, int val)
{
    g[x].g[1][0] += val - a[x], a[x] = val;
    while(x)
    {
        matrix old = ask(1, n, 1, dfn[top[x]], dfn[bot[top[x]]]);
        modify(1,n,1,dfn[x]);
        matrix now = ask(1, n, 1, dfn[top[x]], dfn[bot[top[x]]]);
        x = fa[top[x]];
        g[x].g[0][0] += max(now.g[0][0], now.g[1][0]) - max(old.g[0][0],old.g[1][0]);
        g[x].g[0][1] = g[x].g[0][0];
        g[x].g[1][0] += now.g[0][0] - old.g[0][0];
    }
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dep[1] = 1, dfs(1), top[1] = 1, dfs2(1), build(1, n, 1);
    for (int i = 1, x, val; i <= m; ++i)
    {
        read(x),read(val),update(x,val);
        matrix res = ask(1,n,1,1,dfn[bot[1]]);
        printf("%d\n", max(res.g[0][0], res.g[1][0]));
    }
    return 0;
}