#include <cstdio>
#include <ctype.h>
const int bufSize = 1000000;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &r)
{
    static char c;
    r = 0;
    for(c = nc();!isdigit(c);) c = nc();
    for(;isdigit(c);c = nc()) r = r * 10 + c - 48;
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
    E[++tot].to = y,E[tot].next = head[x],head[x] = tot;
}
int n,m,s;
int fa[maxn],size[maxn],son[maxn],dep[maxn],top[maxn];
void dfs1(int u)
{
    size[u] = 1;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u,dep[v] = dep[u] + 1;
        dfs1(v),size[u] += size[v];
        if(size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    if(!son[u]) return;
    top[son[u]] = top[u],dfs2(son[u]);
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u] || v == son[u]) continue;
        top[v] = v,dfs2(v);
    }
}
inline int lca(int x,int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
        {
            int t = x;
            x = y,y = t;
        }
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
int main()
{
    read(n),read(m),read(s);
    for(int i = 1;i<n;++i)
    {
        int x,y;
        read(x),read(y),add(x,y),add(y,x);
    }
    dfs1(s),dfs2(s);
    while(m--)
    {
        int x,y;
        read(x),read(y);
        printf("%d\n",lca(x,y));
    }
    return 0;
}