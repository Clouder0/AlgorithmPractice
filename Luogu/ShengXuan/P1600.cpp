#include <algorithm>
#include <cstdio>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 3e5 + 100;
int n, m;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y; }
int w[maxn];
int size[maxn], fa[maxn], dep[maxn], son[maxn], top[maxn];
void dfs(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1, fa[v] = u, dfs(v), size[u] += size[v];
        if (size[son[u]] < size[v]) son[u] = v;
    }
}
void dfs2(int u)
{
    if (!son[u]) return;
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v);
    }
}
int lca(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
int root[maxn], sum[maxn << 5], L[maxn << 5], R[maxn << 5], st[maxn << 5], stop, ind;
inline int newnode() { return stop ? st[stop--] : ++ind; }
inline void delnode(int x)
{
    if (x) L[x] = R[x] = sum[x] = 0, st[++stop] = x;
}
void modify(int l, int r, int& p, int pos, int k)
{
    if (!p) p = newnode();
    if (l == r) return (void)(sum[p] += k);
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, L[p], pos, k);
    else modify(mid + 1, r, R[p], pos, k);
}
int ask(int l, int r, int p, int pos)
{
    if (!p) return 0;
    if (l == r) return sum[p];
    int mid = l + r >> 1;
    if (pos <= mid) return ask(l, mid, L[p], pos);
    else return ask(mid + 1, r, R[p], pos);
}
void merge(int& x, int y)
{
    if (!x || !y) return (void)(x += y);
    merge(L[x], L[y]), merge(R[x], R[y]), sum[x] += sum[y], delnode(y);
}
int ANS[maxn];
void output(int l, int r, int p)
{
    if (l == r) return (void)(printf("[%d,%d] ", l, sum[p]));
    int mid = l + r >> 1;
    output(l, mid, L[p]), output(mid + 1, r, R[p]);
}
void dfs3(int u)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        dfs3(v), merge(root[u], root[v]);
    }
    //    printf("u:%d :", u), output(-n, n, root[u]), puts("");
    if (dep[u] + w[u] <= n) ANS[u] = ask(-n, n, root[u], dep[u] + w[u]);
    if (w[u]) ANS[u] += ask(-n, n, root[u], dep[u] - w[u]);
}
int main()
{
    read(n), read(m);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    for (int i = 1; i <= n; ++i) read(w[i]);
    dfs(1), top[1] = 1, dfs2(1);
    for (int i = 1, a, b; i <= m; ++i)
    {
        read(a), read(b);
        int l = lca(a, b);
        modify(-n, n, root[a], dep[a], 1);
        modify(-n, n, root[b], dep[l] * 2 - dep[a], 1);
        modify(-n, n, root[l], dep[a], -1);
        modify(-n, n, root[fa[l]], dep[l] * 2 - dep[a], -1);
    }
    dfs3(1);
    for (int i = 1; i <= n; ++i) printf("%d ", ANS[i]);
    return 0;
}