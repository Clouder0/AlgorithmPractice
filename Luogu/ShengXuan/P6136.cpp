#include <cstdio>
#include <algorithm>
#include <cctype>
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
const int maxn = 2e6 + 100;
int n, m;
int fa[maxn], son[maxn][2], cnt[maxn], val[maxn], sz[maxn], tot, root;
inline void maintain(int x) { sz[x] = sz[son[x][0]] + sz[son[x][1]] + cnt[x]; }
inline bool get(int x) { return x == son[fa[x]][1]; }
inline void clear(int x) { son[x][0] = son[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0; }
void rotate(int x)
{
    int p = fa[x], isr = get(x);
    fa[x] = fa[p];
    if (fa[p]) son[fa[p]][get(p)] = x;
    fa[son[x][isr ^ 1]] = p, son[p][isr] = son[x][isr ^ 1];
    fa[p] = x, son[x][isr ^ 1] = p;
    maintain(p), maintain(x);
}
void splay(int x)
{
    for (int f = fa[x]; f; rotate(x), f = fa[x])
        if (fa[f]) rotate(get(x) == get(f) ? f : x);
    root = x;
}
void ins(int k)
{
    if (!root) return (void)(root = ++tot,val[root] = k, cnt[root] = 1, maintain(root));
    int p = root;
    while (1)
    {
        if (val[p] == k) return (void)(cnt[p]++, maintain(fa[p]), maintain(p), splay(p));
        int& t = son[p][k > val[p]];
        if (t) p = t;
        else return (void)(t = ++tot,fa[t] = p, val[t] = k, cnt[t] = 1, maintain(t), maintain(p), splay(t));
    }
}
int getrnk(int k)
{
    int p = root, res = 0;
    while (p)
    {
        if (k < val[p]) { p = son[p][0]; continue; }
        res += sz[son[p][0]];
        if (val[p] == k) return splay(p), res + 1;
        else res += cnt[p], p = son[p][1];
    }
    return res + 1;
}
int getbyrnk(int k)
{
    int p = root;
    while(1)
    {
        if (k <= sz[son[p][0]]) { p = son[p][0]; continue; }
        k -= sz[son[p][0]] + cnt[p];
        if (k <= 0) return splay(p), val[p];
        p = son[p][1];
    }
}
int pre()
{
    int p = son[root][0];
    while (son[p][1]) p = son[p][1];
    return splay(p), p;
}
int nxt()
{
    int p = son[root][1];
    while (son[p][0]) p = son[p][0];
    return splay(p), p;
}
void del(int k)
{
    getrnk(k);  //splay the node with val k to the root.
    if (cnt[root] > 1) return (void)(--cnt[root], maintain(root));
    if (!son[root][0] && !son[root][1]) return (void)(clear(root), root = 0);
    if (!son[root][1]) { int t = root; root = son[root][0], fa[root] = 0,clear(t); return; }
    if (!son[root][0]) { int t = root; root = son[root][1], fa[root] = 0,clear(t); return; }
    int p = root, t = pre();  //now the root is t
    fa[son[p][1]] = t, son[t][1] = son[p][1], clear(p), maintain(t);
}
int main()
{
    ins(1 << 30), ins(1 << 31);
    read(n), read(m);
    for (int i = 1, x; i <= n; ++i) read(x), ins(x);
    int last = 0, res = 0;
    for (int i = 1, opt, x; i <= m; ++i)
    {
        read(opt), read(x), x ^= last;
        if (opt == 1) ins(x);
        else if (opt == 2) del(x);
        else if (opt == 3) last = getrnk(x) - 1;
        else if(opt == 4) last = getbyrnk(x + 1);
        else if (opt == 5) ins(x), last = val[pre()], del(x);
        else if (opt == 6) ins(x), last = val[nxt()], del(x);
        if (opt >= 3) res ^= last;
    }
    printf("%d\n", res);
    return 0;
}