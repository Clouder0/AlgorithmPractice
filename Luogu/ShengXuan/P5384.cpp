#include <algorithm>
#include <cstdio>
#include <ctype.h>
using namespace std;
const int maxn = 1e6 + 100;
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
int n, m;
struct node
{
    int to, next;
} E[maxn];
int head[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
struct Q
{
    int next, ans, dep;
} Q[maxn];
int Qh[maxn];
inline void addQ(int u, int dep)
{
    static int tot = 0;
    Q[++tot].next = Qh[u], Qh[u] = tot, Q[tot].dep = dep;
}
int dep[maxn], size[maxn], son[maxn];
namespace Kth
{
struct kfaq
{
    int next, fa, kth;
} K[maxn];
int Kh[maxn];
inline void addK(int u, int kth)
{
    static int tot = 0;
    K[++tot].next = Kh[u], Kh[u] = tot, K[tot].kth = kth;
}
int s[maxn], top;
void dfs(int u)
{
    size[u] = 1, s[++top] = u;
    for (int p = Kh[u]; p; p = K[p].next)
        if (top - K[p].kth > 0) K[p].fa = s[top - K[p].kth];
        else K[p].fa = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dep[v] = dep[u] + 1, dfs(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    --top;
}
}  // namespace Kth
int root[maxn], L[maxn * 5], R[maxn * 5], sum[maxn * 5], bin[maxn * 5], top, ind;
inline int newnode() { return top ? bin[top--] : ++ind; }
inline void delnode(int x) { L[x] = R[x] = sum[x] = 0, bin[++top] = x; }
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
int merge(int l, int r, int x, int y)
{
    if (!x || !y) return x + y;
    if (l == r) return sum[x] += sum[y], delnode(y), x;
    int mid = l + r >> 1;
    L[x] = merge(l, mid, L[x], L[y]), R[x] = merge(mid + 1, r, R[x], R[y]), delnode(y);
    return x;
}
void dfs(int u)
{
    if (son[u]) dfs(son[u]), root[u] = merge(1, n, root[u], root[son[u]]);
    for (int p = head[u]; p; p = E[p].next)
        if (E[p].to != son[u]) dfs(E[p].to), root[u] = merge(1, n, root[u], root[E[p].to]);
    modify(1, n, root[u], dep[u], 1);
    for (int p = Qh[u]; p; p = Q[p].next) Q[p].ans = max(0, ask(1, n, root[u], Q[p].dep + dep[u]) - 1);
}
int main()
{
    read(n), read(m);
    for (int i = 2, x; i <= n; ++i) read(x), add(x, i);
    for (int i = 1, u, k; i <= m; ++i) read(u), read(k), Kth::addK(u, k);
    dep[1] = 1, Kth::dfs(1);
    for (int i = 1; i <= m; ++i) addQ(Kth::K[i].fa, Kth::K[i].kth);
    dfs(1);
    for (int i = 1; i <= m; ++i) printf("%d ", Q[i].ans);
    return 0;
}