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
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(const int& x, const int& y) { E[++tot].next = head[x], E[tot].to = y, head[x] = tot; }
int T, n, a, b, da, db, d;
int dep[maxn], maxx[maxn], secx[maxn];
void dfs(int u, int fa)
{
    maxx[u] = secx[u] = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dep[v] = dep[u] + 1, dfs(v, u);
        if (maxx[v] + 1 > maxx[u]) secx[u] = maxx[u], maxx[u] = maxx[v] + 1;
        else if (maxx[v] + 1 > secx[u]) secx[u] = maxx[v] + 1;
    }
    d = std::max(maxx[u] + secx[u], d);
}
int main()
{
    read(T);
    while (T--)
    {
        tot = d = 0;
        read(n), read(a), read(b), read(da), read(db);
        for (int i = 1; i <= n; ++i) head[i] = maxx[i] = secx[i] = dep[i] = 0;
        for (int i = 1; i < n; ++i)
        {
            int x, y;
            read(x), read(y), add(x, y), add(y, x);
        }
        dfs(a, 0);
        int dis = dep[b];
        if (dis <= da) puts("Alice");
        else if (da * 2 >= d) puts("Alice");
        else if (db > da * 2) puts("Bob");
        else puts("Alice");
    }
    return 0;
}