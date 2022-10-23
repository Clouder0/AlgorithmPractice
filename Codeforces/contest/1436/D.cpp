#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
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
}E[maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n, fa[maxn], w[maxn];
int leafnum[maxn], maxx[maxn], sum[maxn];
void dfs(int u)
{
    sum[u] = w[u];
    if (!head[u]) leafnum[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dfs(v), sum[u] += sum[v], leafnum[u] += leafnum[v];
        maxx[u] = std::max(maxx[u], maxx[v]);
    }
    //divide w[u] to sons
    int rest = w[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        int can = maxx[u] * leafnum[v];
        rest -= can - sum[v];
    }
    if (rest > 0) maxx[u] = maxx[u] + (rest + leafnum[u] - 1) / leafnum[u];
}
signed main()
{
    read(n);
    for (int i = 2; i <= n; ++i) read(fa[i]), add(fa[i], i);
    for (int i = 1; i <= n; ++i) read(w[i]);
    dfs(1);
    printf("%lld\n", maxx[1]);
    return 0;
}