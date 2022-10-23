#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
int n, m, a[maxn], H[maxn], cnt;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(const int& x, const int& y) { E[++tot].next = head[x], E[tot].to = y, head[x] = tot; }
int root[maxn], L[maxn << 5], R[maxn << 5], sum[maxn << 5], ind;
int modify(int l, int r, int p, int pos)
{
    int now = ++ind;
    L[now] = L[p], R[now] = R[p], sum[now] = sum[p] + 1;
    if(l == r) return now;
    int mid = l + r >> 1;
    if (pos <= mid) L[now] = modify(l, mid, L[now], pos);
    else R[now] = modify(mid + 1, r, R[now], pos);
    return now;
}
int ask(int l, int r, int x, int y, int lca, int falca, int k)
{
    if (l == r) return l;
    int mid = l + r >> 1, lres = sum[L[x]] + sum[L[y]] - sum[L[lca]] - sum[L[falca]];
    if (k <= lres) return ask(l, mid, L[x], L[y], L[lca], L[falca], k);
    else return ask(mid + 1, r, R[x], R[y], R[lca], R[falca], k - lres);
}
int size[maxn], son[maxn], dep[maxn], fa[maxn], top[maxn];
void dfs1(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    root[u] = modify(1, cnt, root[fa[u]], a[u]);
    if(!son[u]) return;
    top[son[u]] = top[u],dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(top[v] = v);
    }
}
inline int lca(int x, int y)
{
    for (; top[x] != top[y]; x = fa[top[x]]) if (dep[top[x]] < dep[top[y]]) swap(x, y);
    return dep[x] < dep[y] ? x : y;
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]), H[++cnt] = a[i];
    sort(H + 1, H + 1 + cnt), cnt = unique(H + 1, H + 1 + cnt) - H - 1;
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(H + 1, H + 1 + cnt, a[i]) - H;
    for (int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u);
    dfs1(1), top[1] = 1, dfs2(1);
    int last = 0;
    for (int i = 1, x, y, k; i <= m; ++i)
    {
        read(x), read(y), read(k);
        int l = lca(x ^= last, y);
        printf("%d\n", last = H[ask(1, cnt, root[x], root[y], root[l], root[fa[l]], k)]);
    }
    return 0;
}