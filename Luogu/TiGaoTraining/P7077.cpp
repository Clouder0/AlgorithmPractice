#include <algorithm>
#include <cstdio>
#include <cstring>
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
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int mod = 998244353;
const int maxn = 3e6 + 100;
struct node
{
    int to, next;
} E[maxn];
int head[maxn];
inline void addE(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
inline int add(int x, int y) { int res = x + y; return res >= mod ? res - mod : res; }
inline int mul(int x, int y) { return 1ll * x * y % mod; }
int n, m, q, a[maxn], type[maxn], tar[maxn], w[maxn], S, in[maxn];
int prod[maxn], g[maxn];
void dfs1(int u, int fa)
{
    if (prod[u] != -1) return;
    if (type[u] == 2) prod[u] = w[u];
    else prod[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs1(v, u), prod[u] = mul(prod[u], prod[v]);
    }
}
signed main()
{
    memset(prod, -1, sizeof(prod));
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        read(type[i]);
        if (type[i] == 1) read(tar[i]), read(w[i]);
        else if (type[i] == 2) read(w[i]);
        else
        {
            int num, x;
            read(num);
            while (num--) read(x), addE(i, x), in[x]++;
        }
    }
    S = n + m + 1;
    for (int i = 1; i <= n; ++i) type[i + m] = 1, tar[i + m] = i, w[i + m] = a[i], addE(S, i + m), in[i + m]++;
    read(q);
    for (int i = 1, x; i <= q; ++i) read(x), addE(S, x), in[x]++;
    dfs1(S, 0);
    static int q[maxn], qt = 0, qh = 1;
    for (int i = 1; i <= S; ++i) if (!in[i]) q[++qt] = i;
    g[S] = 1;
    while (qt >= qh)
    {
        int u = q[qh++];
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            g[v] = add(g[v], g[u]), g[u] = mul(g[u], prod[v]);
            if (--in[v] == 0) q[++qt] = v;
        }
    }
    for (int i = 1; i <= n; ++i) a[i] = 0;
    for (int i = 1; i <= S; ++i) if (type[i] == 1) a[tar[i]] = add(a[tar[i]], mul(w[i], g[i]));
    for (int i = 1; i <= n; ++i) printf("%d ", a[i]);
    return 0;
}