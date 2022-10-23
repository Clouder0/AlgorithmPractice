#include <cstdio>
#include <cstring>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 3e5 + 100;
struct node
{
    int to,next,val;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int n,m;
int fa[maxn],dep[maxn],size[maxn],son[maxn],dis[maxn],top[maxn];
void dfs1(int u)
{
    size[u] = 1;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u,dep[v] = dep[u] + 1,dis[v] = dis[u] + E[p].val;
        dfs1(v); 
        size[u] += size[v];
        if(size[son[u]] < size[v]) son[u] = v;
    }
}
void dfs2(int u)
{
    if(!son[u]) return;
    top[son[u]] = top[u];
    dfs2(son[u]);
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u] || v == son[u]) continue;
        top[v] = v;
        dfs2(v);
    }
}
inline int lca(int x,int y)
{
    while(top[x] != top[y]) dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}
int W[maxn];
int X[maxn],Y[maxn],D[maxn],L[maxn];
void dfs3(int u)
{
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        dfs3(v);
        W[u] += W[v];
    }
}
int maxD;
inline bool check(int len)
{
    memset(W,0,sizeof(W));
    int num = 0;
    for(int i = 1;i<=m;++i)
        if(D[i] > len)
            W[X[i]]++,W[Y[i]]++,W[L[i]] -= 2,++num;
    dfs3(1);
    for(int i = 1;i<n;i++)
    {
        int u = E[i<<1].to,v = E[(i<<1)-1].to;
        if(dep[u] > dep[v]) std::swap(u,v);
        if(maxD - E[i<<1].val <= len && num == W[v]) return true;
    }
    return false;
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<n;++i)
    {
        int x,y,v;
        read(x),read(y),read(v);
        add(x,y,v),add(y,x,v);
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    for(int i = 1;i<=m;++i)
    {
        read(X[i]),read(Y[i]);
        L[i] = lca(X[i],Y[i]);
        D[i] = dis[X[i]] + dis[Y[i]] - (dis[L[i]] << 1);
        if(D[i] > maxD) maxD = D[i];
    }
    int ll = 0,rr = maxD,mid,ans;
    while(ll <= rr)
    {
        mid = ll + rr >> 1;
        if(check(mid))
            ans = mid,rr = mid - 1;
        else
            ll = mid + 1;
    }
    printf("%d",ans);
    return 0;
}