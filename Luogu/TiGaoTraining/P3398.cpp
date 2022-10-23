#include <cstdio>
template<typename T>
inline void swap(T &a,T &b)
{
    T t = a;
    a = b,b = t;
}
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
const int maxn = 1e5 + 100;
int n,m;
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
int dep[maxn],size[maxn],son[maxn],fa[maxn],top[maxn];
void dfs1(int u)
{
    size[u] = 1;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u,dep[v] = dep[u] + 1,dfs1(v);
        size[u] += size[v];
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
int lca(int x,int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        x = fa[top[x]];
    }
    return dep[x] > dep[y] ? y : x;
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<n;++i)
    {
        int u,v;
        read(u),read(v);
        add(u,v),add(v,u);
    }
    dep[1] = top[1] = 1;
    dfs1(1),dfs2(1);
    while(m--)
    {
        int a,b,c,d;
        read(a),read(b),read(c),read(d);
        int l1 = lca(a,b),l2 = lca(c,d);
        if(dep[l1] < dep[l2]) swap(a,c),swap(b,d),swap(l1,l2);
        if(lca(l1,c) == l1 || lca(l1,d) == l1) puts("Y");
        else puts("N");
    }
    return 0;
}