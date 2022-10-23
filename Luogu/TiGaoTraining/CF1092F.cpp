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
const int maxn = 2e5 + 100;
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
int n,dep[maxn],a[maxn];
long long sum[maxn];
void dfs(int u,int fa)
{
    sum[u] = a[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dep[v] = dep[u] + 1, dfs(v, u), sum[u] += sum[v];
    }
}
long long f[maxn];
void dfs2(int u, int fa)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        f[v] = f[u] - sum[v] + sum[1] - sum[v], dfs2(v, u);
    }
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) f[1] += 1ll * dep[i] * a[i];
    dfs2(1,0);
    long long ans = 0;
    for (int i = 1; i <= n; ++i) ans = max(ans, f[i]);
    printf("%lld\n",ans);
    return 0;
}