#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 100;
struct node { int to, next; } E[maxn];
int head[maxn], tot;
inline void add(const int& x, const int& y) { E[++tot].next = head[x], E[tot].to = y, head[x] = tot; }
int n, m, fa[maxn][23], treeroot[maxn], treecnt;
int dep[maxn];
void dfs(int u)
{
    for (int i = 1; i < 23; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u][0]) continue;
        dep[v] = dep[u] + 1, dfs(v);
    }
}
struct query { int next, id, dep; } Q[maxn];
int Qhead[maxn], qcnt;
inline void addQ(const int& x, const int& id, const int& dep)
{
    Q[++qcnt].next = Qhead[x], Qhead[x] = qcnt, Q[qcnt].id = id, Q[qcnt].dep = dep;
}
int ANS[maxn];
inline int kth(int x, int k)
{
    for (int i = 0; i < 23; ++i) if (k & (1 << i)) x = fa[x][i];
    return x;
}
int root[maxn], sum[maxn << 5], L[maxn << 5], R[maxn << 5], ind;
void modify(int l, int r, int& p, int pos, int k)
{
    if (!p) p = ++ind;
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
int merge(int l, int r, int x, int y)
{
    if (!x || !y) return x + y;
    if (l == r) { sum[x] += sum[y]; return x; }
    int mid = l + r >> 1;
    L[x] = merge(l, mid, L[x], L[y]), R[x] = merge(mid + 1, r, R[x], R[y]);
    return x;
}
void dfs2(int u)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u][0]) continue;
        dfs2(v), root[u] = merge(1, n, root[u], root[v]);
    }
    for (int p = Qhead[u]; p; p = Q[p].next) ANS[Q[p].id] = ask(1, n, root[u], Q[p].dep + dep[u]) - 1;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; ++i)
    {
        scanf("%d", &x);
        if (x) add(x, i), fa[i][0] = x;
        else treeroot[++treecnt] = i;
    }
    for (int i = 1; i <= treecnt; ++i) dep[treeroot[i]] = 1, dfs(treeroot[i]);
    scanf("%d", &m);
    for (int i = 1, v, k; i <= m; ++i) scanf("%d %d", &v, &k), addQ(kth(v, k), i, k);
    for (int i = 1; i <= n; ++i) modify(1, n, root[i], dep[i], 1);
    for (int i = 1; i <= treecnt; ++i) dfs2(treeroot[i]);
    for (int i = 1; i <= m; ++i) printf("%d ", ANS[i]);
    return 0;
}