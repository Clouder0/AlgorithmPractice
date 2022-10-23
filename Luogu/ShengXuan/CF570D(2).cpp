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
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
const int maxn = 1e6 + 100;
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
char s[maxn];
int n, m, dep[maxn], fa[maxn], size[maxn], son[maxn], vis[maxn], ANS[maxn];
void dfs(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        dep[v] = dep[u] + 1,dfs(v),size[u] += size[v];
        if(size[v] > size[son[u]]) son[u] = v;
    }
}
struct node2
{
    int next,k,id;
}Q[maxn];
int qh[maxn];
inline void addq(int x,int k,int id)
{
    static int tot = 0;
    Q[++tot].next = qh[x], qh[x] = tot, Q[tot].k = k, Q[tot].id = id;
}
int status[maxn];
void change(int u)
{
    status[dep[u]] ^= 1 << (s[u] - 'a');
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u] || vis[v]) continue;
        change(v);
    }
}
void dfs2(int u,int keep)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, 0);
    }
    if (son[u]) dfs2(son[u], 1), vis[son[u]] = 1;
    change(u), vis[son[u]] = 0;
    for (int p = qh[u]; p; p = Q[p].next) ANS[Q[p].id] = !status[Q[p].k] || ((status[Q[p].k] & (status[Q[p].k] - 1)) == 0);
    if (!keep) change(u);
}
int main()
{
    read(n),read(m);
    for (int i = 2; i <= n; ++i) read(fa[i]), add(fa[i], i);
    read(s + 1);
    for (int i = 1, x, k; i <= m; ++i) read(x), read(k), addq(x, k, i);
    dep[1] = 1, dfs(1), dfs2(1, 1);
    for (int i = 1; i <= m; ++i) puts(ANS[i] ? "Yes" : "No");
    return 0;
}