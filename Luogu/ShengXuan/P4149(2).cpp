#include <cstdio>
#include <algorithm>
#include <map>
#include <ctype.h>
using namespace std;
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
    int to,next,val;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int n, k, dep[maxn],size[maxn], son[maxn],vis[maxn];
void dfs1(int u, int fa)
{
    dep[u] = dep[fa] + 1, size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs1(v,u),size[u] += size[v];
        if(size[v] > size[son[u]]) son[u] = v;
    }
}
int ans;
void change(int u, int fa, int val)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;

    }
}
void dfs2(int u, int fa,int keep)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa || v == son[u]) continue;
        dfs(v, u, 0);
    }
    if (son[u]) dfs(son[u], u, 1);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa || v == son[u]) continue;

    }
    if(!keep)
    {

    }
}
int main()
{
    read(n), read(k);
    for (int i = 1, a, b, c; i < n; ++i) read(a), read(b), read(c), ++a, ++b, add(a, b, c), add(b, a, c);
    ans = (1 << 30);
    dfs1(1, 0);
    return 0;
}