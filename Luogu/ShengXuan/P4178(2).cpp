#include <cstdio>
#include <algorithm>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 4e4 + 100;
struct node
{
    int to,next,val;
}E[maxn<<1];
int head[maxn],tot;
inline void add(const int &x,const int &y,const int &val)
{
    E[++tot].next = head[x],E[tot].to  =y,E[tot].val = val,head[x] = tot;
}
int n,k,treeSize,root,ans;
int vis[maxn],size[maxn],maxp[maxn],dis[maxn],color[maxn];
void getroot(int u,int fa)
{
    size[u] = 1,maxp[u] = 0;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa || vis[v]) continue;
        getroot(v,u);
        size[u] += size[v];
        maxp[u] = max(maxp[u],size[v]);
    }
    maxp[u] = max(maxp[u],treeSize - size[u]);
    if(maxp[u] < maxp[root]) root = u;
}
int help[maxn],f[maxn];
void getdis(int u,int fa)
{
    help[++help[0]] = u;
    color[u] = color[fa],f[color[u]]++;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(vis[v] || v == fa) continue;
        dis[v] = dis[u] + E[p].val;
        getdis(v,u);
    }
}
bool cmp(const int &x,const int &y)
{
    return dis[x] < dis[y];
}
int calc(int u)
{
    dis[u] = 0,help[help[0] = 1] = u,color[u] = u,f[u] = 1;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(vis[v]) continue;
        color[v] = v,dis[v] = E[p].val;
        f[color[v]] = 0;
        getdis(v,v);
    }
    std::sort(help + 1,help + 1 + help[0],cmp);
    int l = 1,r = help[0],res = 0;
    while(l < r)
    {
        if(dis[help[l]] + dis[help[r]] <= k)
        {
            res += r - l - f[color[help[l]]] + 1;
            f[color[help[l]]]--,++l;
        }
        else f[color[help[r]]]--,--r;
    }
    return res;
}
void solve(int u)
{
    vis[u] = 1;
    ans += calc(u);
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(vis[v]) continue;
        treeSize = size[v],maxp[root = 0] = 1<<30,getroot(v,u);
        solve(root);
    }
}
int main()
{
    read(n);
    for(int i = 1;i<n;++i)
    {
        int u,v,w;
        read(u),read(v),read(w);
        add(u,v,w),add(v,u,w);
    }
    read(k);
    treeSize = n,root = 1;
    getroot(1,0);
    solve(root);
    printf("%d",ans);
    return 0;
}