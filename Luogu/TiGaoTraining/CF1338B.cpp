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
int n, root, can, sum;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
};
bool dep[maxn], f[maxn][2];
void dfs1(int u, int fa)
{
    if (!E[head[u]].next) return (void)(f[u][dep[u]] = 1);
    int sonleaf = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dep[v] = dep[u] ^ 1, dfs1(v, u),sonleaf += !E[head[v]].next;
        if ((f[v][0] && f[u][1]) || (f[v][1] && f[u][0])) can = 0;
        f[u][0] |= f[v][0],f[u][1] |= f[v][1];
    }
    if (sonleaf) sum += sonleaf - 1;
}
int main()
{
    read(n);
    if (n == 2) return puts("1 1"), 0;
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    for (int i = 1; !root && i <= n; ++i) if (E[head[i]].next) root = i;
    can = 1, dfs1(root, 0);
    printf("%d %d\n", can ? 1 : 3, n - 1 - sum);
    return 0;
}