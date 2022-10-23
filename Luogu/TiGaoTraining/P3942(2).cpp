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
const int maxn = 1e5 + 100;
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
const int inf = 1<<30;
int n, k, t, ans;
int f[maxn],g[maxn];
void dfs(int u, int fa)
{
    f[u] = inf, g[u] = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs(v, u);
        if (g[u] >= 0) g[u] = max(g[u], g[v] + 1);
        f[u] = min(f[u], f[v] + 1);
    }
    if (g[u] == k) ++ans, f[u] = 0, g[u] = -1;
    if (f[u] + g[u] <= k) g[u] = -1;
}
int main()
{
    read(n), read(k), read(t);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dfs(1, 0);
    if (g[1] >= 0) ++ans;
    printf("%d\n", ans);
    return 0;
}