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
const int maxn = 1e5 + 100, maxm = 2 * maxn;
struct node
{
    int to, next, val;
} E[maxm];
int head[maxn];
inline void add(const int& x, const int& y, const int& val)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot;
}
int n, sum[maxn];
void dfs(int u, int fa)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        sum[v] = sum[u] ^ E[p].val, dfs(v, u);
    }
}
int to[maxn * 40][2], cnt;
void ins(int x)
{
    int p = 0;
    for (int i = 30; i >= 0; --i)
    {
        int c = (x >> i) & 1;
        if (!to[p][c]) to[p][c] = ++cnt;
        p = to[p][c];
    }
}
int ask(int x)
{
    int p = 0,res = 0;
    for (int i = 30; i >= 0; --i)
    {
        int c = (x >> i) & 1;
        if (to[p][c ^ 1]) res |= 1 << i, p = to[p][c ^ 1];
        else p = to[p][c];
    }
    return res;
}
int main()
{
    read(n);
    for (int i = 1, a, b, c; i < n; ++i) read(a), read(b), read(c), add(a, b, c), add(b, a, c);
    dfs(1, 0);
    ins(sum[1]);
    int res = 0;
    for (int i = 2; i <= n; ++i) res = std::max(res, ask(sum[i])), ins(sum[i]);
    printf("%d\n", res);
    return 0;
} 