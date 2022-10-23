#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
const int maxn = 8e6 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], head2[maxn], tot;
inline void add(int x, int y) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y; }
inline void addg(int x, int y) { E[++tot].next = head2[x], head2[x] = tot, E[tot].to = y; }
int n, id[maxn], L[maxn], R[maxn];
long long pos[maxn], range[maxn];
#define ls p << 1
#define rs p << 1 | 1
void build(int l, int r, int p)
{
    L[p] = l, R[p] = r;
    if(l == r) return (void)(id[l] = p);
    int mid = (l + r) >> 1;
    build(l, mid, ls), build(mid + 1, r, rs);
    add(p, ls), add(p, rs);
}
void modify(int l, int r, int p, long long ll, long long rr, int k)
{
    if(l > r) return;
    if (pos[l] >= ll && pos[r] <= rr) return (void)(add(k, p));
    int mid = (l + r) >> 1;
    if (ll <= pos[mid]) modify(l, mid, ls, ll, rr, k);
    if (rr >= pos[mid + 1]) modify(mid + 1, r, rs, ll, rr, k);
}
int dfn[maxn], low[maxn], ind;
int s[maxn], top, ins[maxn];
int sccnum, bel[maxn];
int sccl[maxn], sccr[maxn];
void dfs(int u)
{
    dfn[u] = low[u] = ++ind;
    s[++top] = u,ins[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (!dfn[v]) dfs(v), low[u] = std::min(low[u], low[v]);
        else if (ins[v]) low[u] = std::min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        bel[u] = ++sccnum, sccl[sccnum] = L[u], sccr[sccnum] = R[u];
        while (s[top] != u) 
        {
            int v = s[top--];
            bel[v] = sccnum, ins[v] = 0;
            sccl[sccnum] = std::min(sccl[sccnum], L[v]), sccr[sccnum] = std::max(sccr[sccnum], R[v]);
        }
        ins[s[top--]] = 0;
    }
}
bool vis[maxn];
void dfs2(int u)
{
    if (vis[u]) return;
    vis[u] = 1;
    for (int p = head2[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dfs2(v), sccl[u] = std::min(sccl[u], sccl[v]), sccr[u] = std::max(sccr[u], sccr[v]);
    }
}
const int mod = 1e9 + 7;
inline int madd(int a, int b)
{
    int t = a + b;
    return t >= mod ? t - mod : t;
}
inline int mul(int a, int b)
{
    long long t = 1ll * a * b;
    return t >= mod ? t % mod : t;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(pos[i]), read(range[i]);
    build(1, n, 1);
    for (int i = 1; i <= n; ++i) modify(1, n, 1, pos[i] - range[i], pos[i] + range[i], id[i]);
    int num = id[n];
    for (int i = 1; i <= num; ++i) if(!dfn[i]) dfs(i);
    for (int u = 1; u <= tot; ++u)
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (bel[u] != bel[v]) addg(bel[u], bel[v]);
        }
    for (int i = 1; i <= sccnum; ++i) dfs2(i);
    int res = 0;
    for (int i = 1; i <= n; ++i) res = madd(res, mul(i, sccr[bel[id[i]]] - sccl[bel[id[i]]] + 1));
    printf("%d\n", res);
    return 0;
}