#include <cstdio>
#include <algorithm>
#include <ctype.h>
#include <cstring>
const int bufSize = 1e6;
using std::min;
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
const int maxn = 1e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n, m, w[maxn];
char types[10];
int size[maxn], fa[maxn], son[maxn], top[maxn], dfn[maxn], id[maxn], down[maxn], ind;
long long f[maxn][2];
const long long inf = 1ll << 40;
struct matrix
{
    long long g[2][2];
    matrix(){std::memset(g,0x3f,sizeof(g));}
    matrix operator*(const matrix b) const
    {
        matrix c;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k) c.g[i][k] = min(c.g[i][k], g[i][j] + b.g[j][k]);
        return c;
    }
} A[maxn << 2], G[maxn];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(int p) { A[p] = A[ls] * A[rs]; }
void build(int l,int r,int p)
{
    if(l == r) return (void)(A[p] = G[id[l]]);
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(p);
}
void modify(int l,int r,int p,int pos)
{
    if (l == r) return (void)(A[p] = G[id[l]]);
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, ls, pos);
    else modify(mid + 1, r, rs, pos);
    pushup(p);
}
matrix ask(int l,int r,int p,int ll,int rr)
{
    if (l >= ll && r <= rr) return A[p];
    int mid = l + r >> 1;
    if (ll <= mid && rr > mid) return ask(l, mid, ls, ll, rr) * ask(mid + 1, r, rs, ll, rr);
    if (ll <= mid) return ask(l, mid, ls, ll, rr);
    return ask(mid + 1, r, rs, ll, rr);
}
void dfs1(int u)
{
    size[u] = 1, f[u][1] = w[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u, dfs1(v), size[u] += size[v];
        f[u][0] += f[v][1], f[u][1] += min(f[v][0], f[v][1]);
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    id[dfn[u] = ++ind] = u,down[top[u]] = ind;
    if (son[u]) top[son[u]] = top[u], dfs2(son[u]);
    else
    {
        //特判叶子
        G[u].g[0][0] = 0,G[u].g[1][0] = w[u];
        return;
    }
    G[u].g[0][0] = inf, G[u].g[0][1] = 0, G[u].g[1][0] = w[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == son[u] || v == fa[u]) continue;
        top[v] = v, dfs2(v), G[u].g[0][1] += f[v][1], G[u].g[1][0] += min(f[v][0], f[v][1]);
    }
    G[u].g[1][1] = G[u].g[1][0];
}
void treeupdate(int x)
{
    while(x)
    {
        matrix old = ask(1, n, 1, dfn[top[x]], down[top[x]]);
        modify(1, n, 1, dfn[x]);
        matrix now = ask(1, n, 1, dfn[top[x]], down[top[x]]);
        x = fa[top[x]];
        G[x].g[0][1] += now.g[1][0] - old.g[1][0];
        G[x].g[1][0] += min(now.g[0][0], now.g[1][0]) - min(old.g[0][0], old.g[1][0]);
        G[x].g[1][1] = G[x].g[1][0];
    }
}
inline void change(int a, int x, int val)
{
    if(son[a])
    {
        if (x) G[a].g[0][1] += val * inf;
        else G[a].g[1][0] += val * inf, G[a].g[1][1] += val * inf;
    }
    else
    {
        //叶子结点，修改f矩阵
        if (x) G[a].g[0][0] += val * inf;
        else G[a].g[1][0] += val * inf;
    }
}
long long update(int a, int x, int b, int y)
{
    change(a, x, 1), change(b, y, 1);
    treeupdate(a), treeupdate(b);
    matrix t = ask(1, n, 1, 1, down[1]);
    long long res = min(t.g[0][0], t.g[1][0]);
    change(a, x, -1), change(b, y, -1);
    treeupdate(a), treeupdate(b);
    return res;
}
int main()
{
    read(n), read(m), read(types);
    for (int i = 1; i <= n; ++i) read(w[i]);
    for (int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u);
    dfs1(1), top[1] = 1, dfs2(1), build(1, n, 1);
    for (int i = 1, a, x, b, y; i <= m; ++i)
    {
        read(a), read(x), read(b), read(y);
        long long res = update(a, x, b, y);
        if (res >= inf) puts("-1");
        else printf("%lld\n", res);
    }
    return 0;
}