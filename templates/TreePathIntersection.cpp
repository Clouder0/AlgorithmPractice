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
int n, m;
int dep[maxn], id[maxn << 1], vis[maxn], ind;
void dfs(int u,int fa)
{
    id[vis[u] = ++ind] = u, dep[u] = dep[fa] + 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v, u), id[++ind] = u;
    }
}
int st[maxn << 1][20], lg[maxn << 1];
void init()
{
    for (int i = 2; i <= ind; ++i) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= ind; ++i) st[i][0] = id[i];
    for (int j = 1; (1 << j) <= ind; ++j)
        for (int i = 1, len = (1 << (j - 1)); i + len <= ind; ++i)
            st[i][j] = dep[st[i][j - 1]] < dep[st[i + len][j - 1]] ? st[i][j - 1] : st[i + len][j - 1];
}
inline int ask(int l, int r)
{
    int k = lg[r - l + 1], t = r - (1 << k) + 1;
    return dep[st[l][k]] < dep[st[t][k]] ? st[l][k] : st[t][k];
}
inline int lca(int x, int y) { return vis[x] <= vis[y] ? ask(vis[x], vis[y]) : ask(vis[y], vis[x]); }
inline bool cmp(const int& x, const int& y) { return dep[x] > dep[y]; }
int main()
{
    read(n), read(m);
    for (int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u);
    dfs(1, 0), init();
    for (int i = 1, a, b, c, d; i <= m; ++i)
    {
        read(a), read(b), read(c), read(d);
        static int l[4];
        l[0] = lca(a, c), l[1] = lca(a, d), l[2] = lca(b, c), l[3] = lca(b, d);
        std::sort(l, l + 4, cmp);
        if(l[0] != l[1])
        {
            //intersect, and the path is l[0] -> l[1]
            int ll = lca(l[0],l[1]);
            printf("%d\n", dep[l[0]] + dep[l[1]] - dep[ll] * 2 + 1);
        }
        else if (l[0] == l[1] && dep[l[0]] >= dep[lca(a, b)] && dep[l[0]] >= dep[lca(c, d)])
        {
            //intersect, and the point is l[0]
            puts("1");
        }
        else puts("0"); //no intersect
    }
    return 0;
}