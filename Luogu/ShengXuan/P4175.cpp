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
const int maxn = 3e5 + 100;
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
int n, m, ans[maxn], size[maxn], fa[maxn], son[maxn], top[maxn], dep[maxn], dfn[maxn], ind, cnt, w[maxn];
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
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v);
    }
}
inline int lca(int x, int y)
{
    for (; top[x] != top[y]; x = fa[top[x]]) if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    return dep[x] < dep[y] ? x : y;
}
namespace Bit
{
int sum[maxn], vis[maxn], tim;
inline void clear() { ++tim; }
inline void check(int x) { if (vis[x] != tim) sum[x] = 0, vis[x] = tim; }
inline void add(int x, int k) { for (; x <= n; x += x & -x) check(x), sum[x] += k; }
inline void addrange(int l, int r, int k) { add(l, k), add(r + 1, -k); }
inline int ask(int x)
{
    int res = 0;
    for (; x > 0; x -= x & -x) check(x),res += sum[x];
    return res;
}
}  // namespace Bit
struct query
{
    int type, u, v, val, id, l;
} Q[maxn], q1[maxn], q2[maxn];
int tsum[maxn], tvis[maxn], tim, H[maxn], tot;
void solve(int l, int r, int L, int R)
{
    if(L > R) return;
    if(l == r)
    {
        for (int i = L; i <= R; ++i) ans[Q[i].id] = l;
        return;
    }
    int mid = l + r >> 1, cnt1 = 0, cnt2 = 0;
    bool flag = 0;
    for (int i = L; !flag && i <= R; ++i) if(Q[i].type == 3) flag = 1;
    if(!flag) return;
    for (int i = L; i <= R; ++i)
    {
        if(Q[i].type <= 2)
        {
            if (Q[i].val > H[mid]) 
            {
                int t = Q[i].type == 1 ? 1 : -1;
                Bit::addrange(dfn[Q[i].u], dfn[Q[i].u] + size[Q[i].u] - 1, Q[i].type == 1 ? 1 : -1);
                if(tvis[Q[i].u] != tim) tsum[Q[i].u] = 0,tvis[Q[i].u] = tim;
                tsum[Q[i].u] += t, q2[++cnt2] = Q[i];
            }
            else q1[++cnt1] = Q[i];
        }
        else
        {
            if (tvis[Q[i].l] != tim) tsum[Q[i].l] = 0, tvis[Q[i].l] = tim;
            int num = Bit::ask(dfn[Q[i].u]) + Bit::ask(dfn[Q[i].v]) - Bit::ask(dfn[Q[i].l]) * 2 + tsum[Q[i].l];
            if (num >= Q[i].val) q2[++cnt2] = Q[i];
            else Q[i].val -= num, q1[++cnt1] = Q[i];
        }
    }
    Bit::clear(), ++tim;
    for (int i = 1; i <= cnt1; ++i) Q[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i) Q[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1), solve(mid + 1, r, L + cnt1, R);
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(w[i]), Q[++cnt].type = 1, Q[cnt].u = i, Q[cnt].val = w[i], H[++tot] = Q[cnt].val;
    for (int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u);
    dep[1] = 1, dfs1(1), top[1] = 1, dfs2(1);
    int qnum = 0;
    for (int i = 1, k, a, b; i <= m; ++i)
    {
        read(k), read(a), read(b);
        if (k == 0) Q[++cnt].type = 2, Q[cnt].u = a, Q[cnt].val = w[a], w[a] = b, Q[++cnt].type = 1, Q[cnt].u = a, Q[cnt].val = w[a],H[++tot] = w[a];
        else Q[++cnt].type = 3, Q[cnt].u = a, Q[cnt].v = b, Q[cnt].val = k, Q[cnt].l = lca(a, b), Q[cnt].id = ++qnum;
    }
    std::sort(H + 1, H + 1 + tot), tot = std::unique(H + 1, H + 1 + tot) - H - 1;
    solve(0, tot, 1, cnt);
    for (int i = 1; i <= qnum; ++i) if (ans[i]) printf("%d\n", H[ans[i]]); else puts("invalid request!");
    return 0;
}