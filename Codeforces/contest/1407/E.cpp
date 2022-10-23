#include <algorithm>
#include <cstdio>
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
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 500100;
struct node
{
    int to, next, col;
} E[maxn];
int head[maxn];
inline void add(const int& x, const int& y, const int& col)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].col = col, E[tot].to = y, head[x] = tot;
}
int n, m;
int dis[maxn], col[maxn], vis[maxn];
int q[maxn], qh, qt;
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) col[i] = -1;
    while (m--)
    {
        int a, b, c;
        read(a), read(b), read(c), add(b, a, c);
    }
    qh = 1;
    q[++qt] = n;
    vis[n] = 1;
    while (qt >= qh)
    {
        int u = q[qh++];
        if (u == 1) break;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (vis[v]) continue;
            if (col[v] == -1) col[v] = 1 ^ E[p].col;
            else if (col[v] == E[p].col) dis[v] = dis[u] + 1, q[++qt] = v, vis[v] = 1;
        }
    }
    printf("%d\n", vis[1] ? dis[1] : -1);
    for (int i = 1; i <= n; ++i) putchar(col[i] ? '1' : '0');
    return 0;
}