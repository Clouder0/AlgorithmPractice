#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using std::max;
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
const int maxn = 3e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(const int& x, const int& y) { E[++tot].next = head[x], E[tot].to = y, head[x] = tot; }
int T, n, dep[maxn], size[maxn], son[maxn], fa[maxn], bel[maxn], secson,root;
void dfs(int u)
{
    son[u] = 0, size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        fa[v] = u, dfs(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    if (max(size[son[u]], n - size[u])  <= n / 2) root = u;
}
void dfs2(int u)
{
    son[u] = 0, size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1, bel[v] = bel[u], dfs2(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
int needsize, ans1[maxn],ans2[maxn],ans3[maxn];
void calc1(int u)
{
    needsize = n;
    while (son[u]) u = son[u];
    for (; u; u = fa[u])
        while (n - 2 * size[u] <= needsize && needsize) ans1[needsize--] = u;
}
void calc2(int u)
{
    needsize = n;
    u = secson;
    while(son[u]) u = son[u];
    for (; u; u = fa[u])
        while (n - 2 * size[u] <= needsize  && needsize) ans2[needsize--] = u;
}
void calc3(int u)
{
    if(son[u]) calc3(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == son[u] || v == fa[u]) continue;
        calc3(v);
    }
    ans3[u] = son[u] ? ans3[son[u]] : u;
    while (size[ans3[u]] * 2 < size[u]) ans3[u] = fa[ans3[u]];
}
inline bool check1(int u,int x)
{
    return x && size[son[x]] * 2 <= size[u] && (size[u] - size[x]) * 2 <= size[u];
}
inline bool check2(int u,int x)
{
    if (x == root) return size[secson] * 2 <= n - size[u];
    return x && size[son[x]] * 2 <= n - size[u] && (n - size[u] - size[x]) * 2 <= n - size[u];
}
inline bool check3(int u,int x)
{
    if(x == root) return size[son[x]] * 2 <= n - size[u];
    return x && size[son[x]] * 2 <= n - size[u] && (n - size[u] - size[x]) * 2 <= n - size[u];
}
inline void clear()
{
    for (int i = 1; i <= n; ++i) head[i] = ans1[i] = ans2[i] = ans3[i] = dep[i] = bel[i] = fa[i] = 0;
    tot = secson = 0;
}
int main()
{
    read(T);
    while(T--)
    {
        clear();
        read(n);
        for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
        dep[1] = 1, dfs(1);
        //printf("root:%d\n",root);
        son[root] = 0, size[root] = 1, dep[root] = 1, fa[root] = 0, bel[root] = root;
        for (int p = head[root]; p; p = E[p].next)
        {
            int v = E[p].to;
            dep[v] = dep[root] + 1, fa[v] = root, bel[v] = v, dfs2(v), size[root] += size[v];
            if (size[v] >= size[son[root]]) secson = son[root], son[root] = v;
            else if(size[v] > size[secson]) secson = v;
        }
        calc1(root), calc2(root), calc3(root);
        long long res = 0;
        for (int u = 1; u <= n; ++u) 
        {
            if(u == root) continue;//u -> fa[u]
            res += ans3[u];
            //printf("%d %d\n", u, ans3[u]);
            if (ans3[u] != u && check1(u, fa[ans3[u]])) 
            {
                res += fa[ans3[u]];
                //printf("%d %d\n", u, fa[ans3[u]]);
            }
            if (bel[u] == son[root])
            {
                if (size[son[root]] - size[u] >= size[secson]) res += root;//printf("%d %d\n",u,root);
                else
                {
                    res += ans2[size[u]];
                    //printf("%d %d\n",u,ans2[size[u]]);
                    if(check2(u,fa[ans2[size[u]]])) res += fa[ans2[size[u]]];//printf("%d %d\n",u,fa[ans2[size[u]]]);
                }
            }
            else
            {
                res += ans1[size[u]];
                //printf("%d %d\n",u,ans1[size[u]]);
                if (check3(u, fa[ans1[size[u]]])) res += fa[ans1[size[u]]];//printf("%d %d\n",u,fa[ans1[size[u]]]);
            }
        }
        printf("%lld\n",res);
    }
    return 0;
}