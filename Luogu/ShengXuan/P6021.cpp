#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctype.h>
using std::min;
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
const int maxn = 2e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(const int& x, const int& y) { E[++tot].next = head[x], E[tot].to = y, head[x] = tot; }
struct matrix
{
    long long g[2][2];
    matrix() { memset(g, 0x3f, sizeof(g)); }
    matrix operator*(const matrix b) const
    {
        matrix c;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k) c.g[i][k] = min(c.g[i][k], g[i][j] + b.g[j][k]);
        return c;
    }
} A[maxn << 2], G[maxn];
int n, m, w[maxn], fa[maxn], size[maxn], son[maxn], top[maxn], end[maxn], dfn[maxn], id[maxn], ind;
long long f[maxn];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(int p) { A[p] = A[rs] * A[ls]; }
void build(int l, int r, int p)
{
    if(l == r) return (void)(A[p] = G[id[l]]);
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(p);
}
void modify(int l,int r,int p,int pos)
{
    if(l == r) return (void)(A[p] = G[id[l]]);
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, ls, pos);
    else modify(mid + 1, r, rs, pos);
    pushup(p);
}
matrix ask(int l,int r,int p,int ll,int rr)
{
    if(l >= ll && r <= rr) return A[p];
    int mid = l + r >> 1;
    if (ll <= mid && rr > mid) return ask(mid + 1, r, rs, ll, rr) * ask(l, mid, ls, ll, rr);
    if (ll <= mid) return ask(l, mid, ls, ll, rr);
    return ask(mid + 1, r, rs, ll, rr);
}
void dfs1(int u)
{
    size[u] = 1,f[u] = w[u];
    long long t = 0;
    bool flag = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        fa[v] = u, dfs1(v), size[u] += size[v], t += f[v], flag = 1;
        if (size[v] > size[son[u]]) son[u] = v;
    }
    if(flag) f[u] = min(f[u], t);
}
void dfs2(int u)
{
    id[dfn[u] = ++ind] = u, end[top[u]] = ind;
    if (son[u]) top[son[u]] = top[u], dfs2(son[u]);
    else return (void)(G[u].g[0][0] = w[u], G[u].g[0][1] = 0);
    G[u].g[0][0] = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v), G[u].g[0][0] += f[v];
    }
    G[u].g[1][0] = w[u], G[u].g[1][1] = 0;
}
long long treeask(int x)
{
    matrix t = ask(1, n, 1, dfn[x], end[top[x]]);
    return t.g[0][0];
}
void update(int x, long long val)
{
    if (son[x]) G[x].g[1][0] += val;
    else G[x].g[0][0] += val;
    while(x)
    {
        matrix old = ask(1, n, 1, dfn[top[x]], end[top[x]]);
        modify(1, n, 1, dfn[x]);
        matrix now = ask(1, n, 1, dfn[top[x]], end[top[x]]);
        x = fa[top[x]];
        G[x].g[0][0] += now.g[0][0] - old.g[0][0];
    }
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(w[i]);
    for (int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u);
    dfs1(1), top[1] = 1, dfs2(1), build(1, n, 1);
    read(m);
    for (int i = 1, x, val; i <= m; ++i)
    {
        char opt[10];
        read(opt);
        if (opt[0] == 'Q') read(x), printf("%lld\n", treeask(x));
        else read(x), read(val), update(x, val);
    }
    return 0;
}