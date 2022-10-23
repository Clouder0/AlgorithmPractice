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
const int maxn = 2e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y; }
int n, m, A[maxn], B[maxn], dep[maxn];
long long val[maxn];
void dfs(int u, int fa)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dep[v] = dep[u] + 1, dfs(v, u);
    }
}
void dfs2(int u,int fa)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        val[v] += val[u], dfs2(v, u);
    }
}
int main()
{
    read(n);
    for (int i = 1; i < n; ++i) read(A[i]), read(B[i]), add(A[i], B[i]), add(B[i], A[i]);
    dfs(1,0);
    read(m);
    for (int i = 1, opt, t, x; i <= m; ++i)
    {
        read(opt), read(t), read(x);
        int a = A[t], b = B[t];
        if (opt == 1)
        {
            if (dep[a] > dep[b]) val[a] += x;
            else val[1] += x, val[b] -= x;
        }
        else
        {
            if (dep[a] < dep[b]) val[b] += x;
            else val[1] += x, val[a] -= x;
        }
    }
    dfs2(1,0);
    for (int i = 1; i <= n; ++i) printf("%lld\n",val[i]);
    return 0;
}