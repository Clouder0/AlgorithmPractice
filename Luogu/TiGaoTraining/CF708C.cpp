#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
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
int n;
struct node
{
    int to,next;
}E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],head[x] = tot,E[tot].to = y;
}
int fa[maxn],son[maxn],size[maxn],f[maxn],g[maxn],fson[maxn];
void dfs(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u, dfs(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
        int val = (size[v] <= n / 2) ? size[v] : f[v];
        if (val > f[u]) g[u] = f[u], f[u] = val,fson[u] = v;
        else if (val > g[u]) g[u] = val;
    }
}
int ANS[maxn];
void dfs2(int u,int now)
{
    ANS[u] = 1;
    if (size[son[u]] > n / 2) ANS[u] = ((size[son[u]] - f[son[u]]) <= (n / 2));
    else if (n - size[u] > n / 2) ANS[u] = ((n - size[u] - now) <= n / 2);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        int nex = ((n - size[u]) <= (n / 2)) ? (n - size[u]) : now;
        nex = max(nex, fson[u] != v ? f[u] : g[u]);
        dfs2(v,nex);
    }
}
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dfs(1), dfs2(1, 0);
    for (int i = 1; i <= n; ++i) printf("%d ", ANS[i]);
    return 0;
}