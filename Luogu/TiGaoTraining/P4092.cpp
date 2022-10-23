#include <cstdio>
#include <algorithm>
#include <set>
#include <ctype.h>
using std::set;
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
int n, m, size[maxn], c[maxn], top[maxn], son[maxn], dep[maxn], fa[maxn], dfn[maxn], id[maxn], ind;
void dfs1(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        dep[v] = dep[u] + 1, fa[v] = u, dfs1(v), size[u] += size[v];
        if(size[son[u]] < size[v]) son[u] = v;
    }
}
void dfs2(int u)
{
    dfn[u] = ++ind, id[ind] = u;
    if (son[u]) top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v);
    }
}
set<int> S[maxn];
char s[10];
void change(int x)
{
    if (c[x]) return;
    S[top[x]].insert(-dfn[x]), c[x] = 1;
}
int ask(int x)
{
    while(x)
    {
        if (S[top[x]].size())
        {
            set<int>::iterator it = S[top[x]].lower_bound(-dfn[x]);
            if (it != S[top[x]].end()) return id[-*it];
        }
        x = fa[top[x]];
    }
    return 1;
}
int main()
{
    read(n), read(m);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dep[1] = 1, dfs1(1), top[1] = 1, dfs2(1);
    c[1] = 1, S[1].insert(-1);
    for (int i = 1, a, b; i <= m; ++i)
    {
        read(s), read(b);
        if(s[0] == 'C') change(b);
        else printf("%d\n",ask(b));
    }
    return 0;
}