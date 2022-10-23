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
const int maxn = 1e5 + 100,maxm = 2e5 + 100;
struct node
{
    int to, next;
} E[maxm];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n, m, fa[maxn], top[maxn], size[maxn], son[maxn], dfn[maxn], dep[maxn], ind,ans[maxm];
struct query
{
    int type, u, v, val, id, l;
} Q[maxm], q1[maxm], q2[maxm];
void dfs1(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        dep[v] = dep[u] + 1, fa[v] = u, dfs1(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    dfn[u] = ++ind;
    if(!son[u]) return;
    top[son[u]] = top[u] ,dfs2(son[u]);
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
        if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
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
    for (; x > 0; x -= x & -x) check(x),res += sum[x];
    return res;
}
}  // namespace Bit
int H[maxn], hcnt;
void solve(int l, int r, int L, int R)
{
    if (L > R) return;
    if (l == r)
    {
        for (int i = L; i <= R; ++i) ans[Q[i].id] = l;
        return;
    }
    bool flag = 0;
    for (int i = L; !flag && i <= R; ++i) if (Q[i].type == 2) flag = 1;
    if(!flag) return;
    int mid = l + r >> 1, cnt1 = 0, cnt2 = 0, edgenum = 0;
    for (int i = L; i <= R; ++i)
    {
        if(Q[i].type == 2)
        {
            int num = Bit::ask(dfn[Q[i].u] + size[Q[i].u] - 1) - Bit::ask(dfn[Q[i].u] - 1);
            if (num == edgenum) q1[++cnt1] = Q[i];
            else q2[++cnt2] = Q[i];
        }
        else
        {
            int t = Q[i].type == 0 ? 1 : -1;
            if(Q[i].val > H[mid])
            {
                Bit::add(dfn[Q[i].u], t), Bit::add(dfn[Q[i].v], t), Bit::add(dfn[Q[i].l], -t);
                if (fa[Q[i].l]) Bit::add(dfn[fa[Q[i].l]], -t);
                q2[++cnt2] = Q[i], edgenum += t;
            }
            else q1[++cnt1] = Q[i];
        }
    }
    Bit::clear();
    for (int i = 1; i <= cnt1; ++i) Q[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i) Q[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1), solve(mid + 1, r, L + cnt1, R);
}
int main()
{
    read(n), read(m);
    for (int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u);
    dep[1] = 1, dfs1(1), top[1] = 1, dfs2(1);
    int qnum = 0;
    for (int i = 1,t; i <= m; ++i) 
    {
        read(Q[i].type);
        if (Q[i].type == 0) read(Q[i].u), read(Q[i].v), read(Q[i].val), Q[i].l = lca(Q[i].u, Q[i].v), H[++hcnt] = Q[i].val;
        else if (Q[i].type == 1) read(t), Q[i].u = Q[t].u, Q[i].v = Q[t].v, Q[i].val = Q[t].val, Q[i].l = Q[t].l;
        else Q[i].id = ++qnum, read(Q[i].u);
    }
    std::sort(H + 1, H + 1 + hcnt), hcnt = std::unique(H + 1, H + 1 + hcnt) - H - 1;
    solve(0, hcnt, 1, m);
    for (int i = 1; i <= qnum; ++i) if (ans[i]) printf("%d\n", H[ans[i]]); else puts("-1");
    return 0;
}