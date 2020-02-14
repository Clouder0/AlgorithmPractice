#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;
int cnt, fst[MAXN], nxt[MAXN << 1], to[MAXN << 1], w[MAXN << 1], fr[MAXN << 1];
int n, a[MAXN], t[MAXN << 2], tag[MAXN << 2], cov[MAXN << 2];
int siz[MAXN], son[MAXN], dfn[MAXN], Index, top[MAXN], rk[MAXN], dep[MAXN], faz[MAXN];
string s;
void AddEdge(int u, int v, int c)
{
    to[++cnt] = v;
    nxt[cnt] = fst[u];
    fst[u] = cnt;
    w[cnt] = c;
    fr[cnt] = u;
}
void Dfs1(int u)
{
    siz[u] = 1;
    son[u] = 0;
    for (int i = fst[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == faz[u])
            continue;
        faz[v] = u;
        dep[v] = dep[u] + 1;
        rk[v] = w[i];
        Dfs1(v);
        siz[u] += siz[v];
        if (siz[son[u]] < siz[v])
            son[u] = v;
    }
}
void Dfs2(int u, int rt)
{
    dfn[u] = ++Index;
    top[u] = rt;
    a[Index] = rk[u];
    if (son[u])
        Dfs2(son[u], rt);
    for (int i = fst[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == faz[u] || v == son[u])
            continue;
        Dfs2(v, v);
    }
}
void PushUp(int rt)
{
    t[rt] = max(t[rt << 1], t[rt << 1 | 1]);
}
void PushDown(int rt)
{
    if (~cov[rt])
    {
        cov[rt << 1] = cov[rt << 1 | 1] = cov[rt];
        t[rt << 1] = t[rt << 1 | 1] = cov[rt];
        tag[rt << 1] = tag[rt << 1 | 1] = 0;
        cov[rt] = -1;
    }
    tag[rt << 1] += tag[rt];
    tag[rt << 1 | 1] += tag[rt];
    t[rt << 1] += tag[rt];
    t[rt << 1 | 1] += tag[rt];
    tag[rt] = 0;
}
void BuildSegmentTree(int rt, int l, int r)
{
    cov[rt] = -1;
    if (l == r)
    {
        t[rt] = a[l];
        return;
    }
    int mid = l + r >> 1;
    BuildSegmentTree(rt << 1, l, mid);
    BuildSegmentTree(rt << 1 | 1, mid + 1, r);
    PushUp(rt);
}
void ModifyCover(int rt, int l, int r, int tl, int tr, int val)
{
    if (tl <= l && r <= tr)
    {
        t[rt] = cov[rt] = val;
        tag[rt] = 0;
        return;
    }
    PushDown(rt);
    int mid = l + r >> 1;
    if (tl <= mid)
        ModifyCover(rt << 1, l, mid, tl, tr, val);
    if (tr > mid)
        ModifyCover(rt << 1 | 1, mid + 1, r, tl, tr, val);
    PushUp(rt);
}
void ModifyAdd(int rt, int l, int r, int tl, int tr, int val)
{
    if (tl <= l && r <= tr)
    {
        t[rt] += val;
        tag[rt] += val;
        return;
    }
    PushDown(rt);
    int mid = l + r >> 1;
    if (tl <= mid)
        ModifyAdd(rt << 1, l, mid, tl, tr, val);
    if (tr > mid)
        ModifyAdd(rt << 1 | 1, mid + 1, r, tl, tr, val);
    PushUp(rt);
}
int Query(int rt, int l, int r, int tl, int tr)
{
    if (tl <= l && r <= tr)
        return t[rt];
    PushDown(rt);
    int mid = l + r >> 1, res = 0;
    if (tl <= mid)
        res = max(res, Query(rt << 1, l, mid, tl, tr));
    if (tr > mid)
        res = max(res, Query(rt << 1 | 1, mid + 1, r, tl, tr));
    return res;
}
void ModifyCoverOnTree(int u, int v, int val)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ModifyCover(1, 1, n, dfn[top[u]], dfn[u], val);
        u = faz[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    ModifyCover(1, 1, n, dfn[u] + 1, dfn[v], val);
}
void ModifyAddOnTree(int u, int v, int val)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ModifyAdd(1, 1, n, dfn[top[u]], dfn[u], val);
        u = faz[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    ModifyAdd(1, 1, n, dfn[u] + 1, dfn[v], val);
}
int QueryMaxnOnTree(int u, int v)
{
    int res = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        res = max(res, Query(1, 1, n, dfn[top[u]], dfn[u]));
        u = faz[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    res = max(res, Query(1, 1, n, dfn[u] + 1, dfn[v]));
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        AddEdge(x, y, z);
        AddEdge(y, x, z);
    }
    Dfs1(1);
    Dfs2(1, 1);
    BuildSegmentTree(1, 1, n);
    while (1)
    {
        int x, y, z;
        cin >> s;
        if (s == "Stop")
            break;
        else
        {
            scanf("%d %d", &x, &y);
            if (s == "Change")
            {
                x <<= 1;
                int u = fr[x], v = to[x];
                if (dep[u] > dep[v])
                    swap(u, v);
                ModifyCoverOnTree(u, v, y);
            }
            else if (s == "Cover")
            {
                scanf("%d", &z);
                ModifyCoverOnTree(x, y, z);
            }
            else if (s == "Add")
            {
                scanf("%d", &z);
                ModifyAddOnTree(x, y, z);
            }
            else if (s == "Max")
                printf("%d\n", QueryMaxnOnTree(x, y));
        }
    }
    return 0;
}