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
const int maxn = 2e5;
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
int n, m, q, dep[maxn], size[maxn], son[maxn], fa[maxn], top[maxn], dfn[maxn], ed[maxn], id[maxn],ind, cnt, ans[maxn];
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
    id[dfn[u] = ++ind] = u;
    if (!son[u]) return (void)(ed[u] = ind);
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v);
    }
    ed[u] = ind;
}
inline int getz(int x, int y)
{
    int pre = 0;
    while (top[x] != top[y]) pre = y, y = fa[top[y]];
    if (dfn[x] + 1 <= dfn[y]) return id[dfn[x] + 1];  //heavy son
    else return pre;
}
struct query
{
    int x, type, l, r, val, id;
} Q[maxn], q1[maxn], q2[maxn];
bool cmp(const query& a, const query& b)
{
    if (a.x != b.x) return a.x < b.x;
    return a.type < b.type;
}
namespace Bit
{
int sum[maxn], vis[maxn], tim;
inline void clear() { ++tim; }
inline void check(int x) { if (vis[x] != tim) sum[x] = 0, vis[x] = tim; }
inline void add(int x, int k) { for (; x <= n; x += x & -x) check(x), sum[x] += k; }
inline int ask(int x)
{
    int res = 0;
    for (; x > 0; x -= x & -x) check(x), res += sum[x];
    return res;
}
inline void addrange(int l, int r, int k) { if (l <= r) add(l, k), add(r + 1, -k); }
}  // namespace Bit
int H[maxn], hcnt;
void solve(int l, int r, int L, int R)
{
    if(L > R) return;
    if(l == r)
    {
        for (int i = L; i <= R; ++i) if (Q[i].type == 3) ans[Q[i].id] = l;
        return;
    }
    bool flag = 0;
    for (int i = L; !flag && i <= R; ++i) flag |= (Q[i].type == 3);
    if (!flag) return;
    int mid = l + r >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = L; i <= R; ++i)
    {
        if(Q[i].type <= 2)
        {
            int t = (Q[i].type == 1 ? 1 : -1);
            if (Q[i].val <= H[mid]) Bit::add(Q[i].l, t), Bit::add(Q[i].r + 1, -t), q1[++cnt1] = Q[i];
            else q2[++cnt2] = Q[i];
        }
        else
        {
            int num = Bit::ask(Q[i].l);
            if (num >= Q[i].val) q1[++cnt1] = Q[i];
            else Q[i].val -= num, q2[++cnt2] = Q[i];
        }
    }
    Bit::clear();
    for (int i = 1; i <= cnt1; ++i) Q[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i) Q[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1), solve(mid + 1, r, L + cnt1, R);
}
int main()
{
    read(n), read(m), read(q);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dep[1] = 1, dfs1(1), top[1] = 1, dfs2(1);
    for (int i = 1, u, v, k; i <= m; ++i) 
    {
        read(u), read(v), read(k), H[++hcnt] = k;
        if (dfn[u] > dfn[v]) std::swap(u, v);
        if(dfn[v] >= dfn[u] && ed[v] <= ed[u])
        {
            int z = getz(u, v);
            if(dfn[z] > 1)
            {
                Q[++cnt].type = 1, Q[cnt].x = 1, Q[cnt].l = dfn[v], Q[cnt].r = ed[v], Q[cnt].val = k;
                Q[++cnt].type = 2, Q[cnt].x = dfn[z], Q[cnt].l = dfn[v], Q[cnt].r = ed[v], Q[cnt].val = k;
            }
            if(ed[z] < n)
            {
                Q[++cnt].type = 1, Q[cnt].x = dfn[v], Q[cnt].l = ed[z] + 1, Q[cnt].r = n, Q[cnt].val = k;
                Q[++cnt].type = 2, Q[cnt].x = ed[v] + 1, Q[cnt].l = ed[z] + 1, Q[cnt].r = n, Q[cnt].val = k;
            }
        }
        else
        {
            Q[++cnt].type = 1, Q[cnt].x = dfn[u], Q[cnt].l = dfn[v], Q[cnt].r = ed[v], Q[cnt].val = k;
            Q[++cnt].type = 2, Q[cnt].x = ed[u] + 1, Q[cnt].l = dfn[v], Q[cnt].r = ed[v], Q[cnt].val = k;
        }
    }
    for (int i = 1, u, v, k; i <= q; ++i)
    {
        read(u), read(v), read(k);
        if (dfn[u] > dfn[v]) std::swap(u, v);
        Q[++cnt].type = 3, Q[cnt].x = dfn[u], Q[cnt].l = dfn[v], Q[cnt].val = k, Q[cnt].id = i;
    }
    std::sort(H + 1, H + 1 + hcnt), hcnt = std::unique(H + 1, H + 1 + hcnt) - H - 1;
    std::sort(Q + 1, Q + 1 + cnt, cmp);
    solve(1, hcnt, 1, cnt);
    for (int i = 1; i <= q; ++i) printf("%d\n",H[ans[i]]);
    return 0;
}