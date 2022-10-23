#include <cstdio>
#include <algorithm>
#include <ctype.h>
using std::swap;
const int bufSize = 1e6;
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
const int maxn = 1e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int n, m, w[maxn], size[maxn], dep[maxn], son[maxn], top[maxn], fa[maxn], dfn[maxn], ind;
int root[maxn], sum[maxn * 30], L[maxn * 30], R[maxn * 30], cnt;
void modify(int l, int r, int& p, int pos)
{
    if(!p) p = ++cnt;
    sum[p]++;
    if (l == r) return;
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, L[p], pos);
    else modify(mid + 1, r, R[p], pos);
}
int ask(int l, int r, int p, int ll, int rr)
{
    if (!p) return 0;
    if (l >= ll && r <= rr) return sum[p];
    int mid = l + r >> 1, ans = 0;
    if (ll <= mid) ans = ask(l, mid, L[p], ll, rr);
    if (rr > mid) ans += ask(mid + 1, r, R[p], ll, rr);
    return ans;
}
void dfs(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1, dfs(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    dfn[u] = ++ind;
    if (!son[u]) return;
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v);
    }
}
bool treeask(int x,int y,int c)
{
    int t = 0;
    while(top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        t += ask(1, n, root[c], dfn[top[x]], dfn[x]);
        if(t) return 1;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return ask(1, n, root[c], dfn[x], dfn[y]);
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(w[i]);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dep[1] = 1, dfs(1), top[1] = 1, dfs2(1);
    for (int i = 1; i <= n; ++i) modify(1, n, root[w[i]], dfn[i]);
    for (int i = 1, a, b, c; i <= m; ++i) read(a), read(b), read(c), printf("%d", treeask(a, b, c));
    return 0;
}