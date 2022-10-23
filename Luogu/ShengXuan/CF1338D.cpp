#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
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
    int to, next;
} E[maxn << 1];
int head[maxn], deg[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int f[maxn][2], res;
void dfs(int u, int fa)
{
    f[u][1] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs(v, u);
        res = std::max(res, f[u][0] + std::max(f[v][0], f[v][1]));
        res = std::max(res, f[u][1] + f[v][0]);
        f[u][0] = std::max(f[u][0], std::max(f[v][0], f[v][1]) + deg[u] - 2);
        f[u][1] = std::max(f[u][1],f[v][0] + 1);
    }
    res = std::max(res,f[u][1]);
}
int main()
{
    read(n);
    for (int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u), ++deg[u], ++deg[v];
    dfs(1, 0);
    printf("%d\n", res);
    return 0;
}