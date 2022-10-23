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
const int maxn = 5e5 + 100;
int n, m, s;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int dep[maxn], id[maxn << 1], vis[maxn], cnt;
void dfs(int u, int fa)
{
    id[vis[u] = ++cnt] = u, dep[u] = dep[fa] + 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs(v, u), id[++cnt] = u;
    }
}
int st[maxn << 1][20], lg[maxn << 1];
void init()
{
    for (int i = 2; i <= cnt; ++i) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= cnt; ++i) st[i][0] = id[i];
    for (int j = 1; (1 << j) <= cnt; ++j)
        for (int i = 1, len = 1 << (j - 1); i + len <= cnt; ++i)
            st[i][j] = dep[st[i][j - 1]] < dep[st[i + len][j - 1]] ? st[i][j - 1] : st[i + len][j - 1];
}
inline int ask(int l, int r)
{
    int k = lg[r - l + 1], t = r - (1 << k) + 1;
    return dep[st[l][k]] < dep[st[t][k]] ? st[l][k] : st[t][k];
}
int main()
{
    read(n), read(m), read(s);
    for (int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u);
    dfs(s, 0);
    init();
    for (int i = 1, a, b; i <= m; ++i)
    {
        read(a), read(b);
        if (vis[a] <= vis[b]) printf("%d\n", ask(vis[a], vis[b]));
        else printf("%d\n", ask(vis[b], vis[a]));
    }
    return 0;
}