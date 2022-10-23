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
const int maxn = 1e5 + 100;
int n;
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
int c[maxn],size[maxn],son[maxn],isson[maxn],vis[maxn],cnt[maxn],maxx;
long long sum[maxn];
void dfs(int u,int fa)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v,u),size[u] += size[v];
        if(size[v] > size[son[u]]) son[u] = v;
    }
    if(son[u]) isson[son[u]] = 1;
}
void update(int u,int fa,int val)
{
    sum[cnt[c[u]]] -= c[u];
    cnt[c[u]] += val;
    sum[cnt[c[u]]] += c[u];
    if(sum[maxx + 1]) ++maxx;
    if(!sum[maxx]) --maxx;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v != fa && !vis[v]) update(v,u,val);
    }
}
long long ANS[maxn];
void dfs2(int u,int fa,int keep)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa || v == son[u]) continue;
        dfs2(v, u, 0);
    }
    if (son[u]) dfs2(son[u], u, 1), vis[son[u]] = 1;
    update(u, fa, 1);
    vis[son[u]] = 0, ANS[u] = sum[maxx];
    if (!keep) update(u, fa, -1);
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(c[i]);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dfs(1, 0), dfs2(1, 0, 1);
    for (int i = 1; i <= n; ++i) printf("%lld ",ANS[i]);
    return 0;
}