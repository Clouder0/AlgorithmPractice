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
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n,m,s;
int fa[maxn];
inline int find(const int &x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x,int y){fa[find(y)] = find(x);}
int vis[maxn];
struct ask
{
    int id,next,to;
}Q[maxn<<1];
int qhead[maxn],ans[maxn];
inline void addq(const int &x,const int &y,const int &id)
{
    static int tot = 0;
    Q[++tot].next = qhead[x],qhead[x] = tot,Q[tot].to = y,Q[tot].id = id;
}
void dfs(int u)
{
    vis[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(vis[v]) continue;
        dfs(v), merge(u, v);
    }
    for (int p = qhead[u]; p; p = Q[p].next)
    {
        int v = Q[p].to;
        if (!vis[v] || ans[Q[p].id]) continue;
        ans[Q[p].id] = find(v);
    }
}
int main()
{
    read(n),read(m),read(s);
    for (int i = 1; i < n; ++i) 
    {
        int a,b;
        read(a),read(b),add(a,b),add(b,a);
    }
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) 
    {
        int a,b;
        read(a),read(b),addq(a,b,i),addq(b,a,i);
    }
    dfs(s);
    for (int i = 1; i <= m; ++i) printf("%d\n",ans[i]);
    return 0;
}