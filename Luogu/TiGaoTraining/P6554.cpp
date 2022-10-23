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
const int maxn = 5e5 + 100;
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
int n,val[maxn],lnum[maxn],rt,isleaf[maxn];
long long g[maxn];
void dfs(int u, int fa)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v, u), lnum[u] += lnum[v], g[u] += g[v];
    }
    if(lnum[u] == 0) lnum[u] = isleaf[u] = 1;
    g[u] += 1ll * val[u] * lnum[u];
}
long long f[maxn];
double ans;
void dfs2(int u, int fa)
{
    ans = max(ans,1.0 * f[u] / (lnum[rt] - isleaf[u]));
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        if(isleaf[v]) f[v] = f[u] - val[u] + 1ll * (lnum[rt] - 2) * val[v];
        else f[v] = f[u] - 1ll * lnum[v] * val[u] + 1ll * (lnum[rt] - lnum[v]) * val[v];
        dfs2(v,u);
    }
}
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    for (int i = 1; i <= n; ++i) read(val[i]);
    for (int i = 1; !rt && i <= n; ++i) if(E[head[i]].next) rt = i;
    ans = -1e16;
    dfs(rt, 0), f[rt] = g[rt], dfs2(rt, 0);
    printf("%.4f",ans);
    return 0;
}