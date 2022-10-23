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
const int maxn = 1e6 + 100;
struct node
{
    int to,next;
}E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n, dep[maxn], son[maxn], *f[maxn], g[maxn], *ind = g, ans[maxn];
void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v, u);
        if (dep[son[u]] < dep[v]) son[u] = v;
    }
    dep[u] = dep[son[u]] + 1;
}
void dfs2(int u,int fa)
{
    f[u][0] = 1;
    if (son[u]) f[son[u]] = f[u] + 1, dfs2(son[u], u), ans[u] = ans[son[u]] + 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa || v == son[u]) continue;
        f[v] = ind, ind += dep[v], dfs2(v, u);
        for (int i = 1; i <= dep[v]; ++i) 
        {
            f[u][i] += f[v][i - 1];
            if (f[u][i] > f[u][ans[u]] || (f[u][i] == f[u][ans[u]] && i < ans[u])) ans[u] = i;
        }
    }
    if (f[u][ans[u]] == 1) ans[u] = 0;
}
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dfs(1, 0), f[1] = ind, ind += dep[1], dfs2(1, 0);
    for (int i = 1; i <= n; ++i) printf("%d\n",ans[i]);
    return 0;
}