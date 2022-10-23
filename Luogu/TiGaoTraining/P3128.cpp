#include <cstdio>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
const int bufSize = 1000000;
inline char gc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=gc();c>'9'||c<'0';c=gc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=gc());
}
const int maxn = 5e4 + 100;
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
int n,m;
int fa[maxn],dep[maxn],size[maxn],son[maxn];
void dfs1(int u)
{
    size[u] = 1;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u,dep[v] = dep[u] + 1;
        dfs1(v);
        size[u] += size[v];
        if(size[son[u]] < size[v]) son[u] = v;
    }
}
int top[maxn];
void dfs2(int u,int topf)
{
    top[u] = topf;
    if(!son[u]) return;
    dfs2(son[u],topf);
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v,v);
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
int w[maxn],ans;
void dfs(int u)
{
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        dfs(v);
        w[u] += w[v];
    }
    ans = max(ans,w[u]);
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<n;++i)
    {
        int a,b;
        read(a),read(b);
        add(a,b);
        add(b,a);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i = 1;i<=m;++i)
    {
        int x,y;
        read(x);
        read(y);
        int l = lca(x,y);
        w[x]++,w[y]++;
        w[l]--,w[fa[l]]--;
    }
    dfs(1);
    printf("%d",ans);
    return 0;
}