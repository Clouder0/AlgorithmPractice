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
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void addE(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int n, m, fa[maxn], in[maxn], out[maxn], ind, size[maxn], son[maxn], dep[maxn], top[maxn],id[maxn];
void dfs(int u)
{
    in[u] = ++ind, id[ind] = u, size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dep[v] = dep[u] + 1, dfs(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    out[u] = ind;
}
void dfs2(int u)
{
    if(!son[u]) return;
    top[son[u]] = top[u],dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == son[u]) continue;
        top[v] = v, dfs2(v);
    }
}
int lca(int x,int y)
{
    for (; top[x] != top[y]; x = fa[top[x]]) if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    return dep[x] < dep[y] ? x : y;
}
long long sum1[maxn], sum2[maxn];
inline int lowbit(int x) { return x & -x; }
void add(int x, int k)
{
    int k2 = k * dep[id[x]];
    for (; x <= n; x += lowbit(x)) sum1[x] += k, sum2[x] += k2;
}
long long ask(int x, int k)
{
    if (!x) return 0;
    int u = id[x];
    long long res1 = 0, res2 = 0;
    for (; x > 0; x -= lowbit(x)) res1 += sum1[x], res2 += sum2[x];
    return res2 - (k - 1) * res1;
}
char s[10];
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), ++a, ++b, fa[b] = a, addE(a, b);
    dep[1] = 1, dfs(1), top[1] = 1, dfs2(1);
    read(m);
    for (int i = 1, a, b, c; i <= m; ++i)
    {
        read(s);
        if (s[0] == 'A')
        {
            read(a), read(b), read(c), ++a, ++b;
            int l = lca(a, b);
            add(in[a], c), add(in[b], c), add(in[l], -c);
            if (fa[l]) add(in[fa[l]], -c);
        }
        else read(a), ++a, printf("%lld\n", ask(out[a], dep[a]) - ask(in[a] - 1, dep[a]));
    }
    return 0;
}