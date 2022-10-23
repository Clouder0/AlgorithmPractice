#include <cstdio>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int gcd(int a,int b)
{
    return b == 0 ? a : gcd(b,a%b);
}
const int maxn = 2e4 + 100;
int to[maxn<<1],val[maxn<<1],next[maxn<<1],head[maxn],tot;
inline void add(const int &a,const int &b,const int &c)
{
    to[++tot] = b,val[tot] = c,next[tot] = head[a],head[a] = tot;
}
int n,treeSize,root,ans;
int vis[maxn],size[maxn],maxp[maxn],dis[maxn],f[3];
void getroot(int u,int fa)
{
    size[u] = 1,maxp[u] = 0;
    for(int p = head[u];p;p=next[p])
    {
        int v = to[p];
        if(v == fa || vis[v]) continue;
        getroot(v,u);
        size[u] += size[v];
        maxp[u] = max(maxp[u],size[v]);
    }
    maxp[u] = max(maxp[u],treeSize - size[u]);
    if(maxp[u] < maxp[root]) root = u;
}
void getdis(int u,int fa)
{
    f[dis[u]]++;
    for(int p = head[u];p;p=next[p])
    {
        int v = to[p];
        if(v == fa || vis[v]) continue;
        dis[v] = (((dis[u] + val[p]) % 3) + 3) % 3;
        getdis(v,u);
    }
}
int calc(int u)
{
    int res = 0;
    f[0] = f[1] = f[2] = 0;
    getdis(u,0);
    res += f[0] * f[0];
    res += f[1] * f[2];
    res += f[2] * f[1];
    return res;
}
void solve(int u)
{
    vis[u] = 1;
    dis[u] = 0,ans += calc(u);
    for(int p = head[u];p;p=next[p])
    {
        int v = to[p];
        if(vis[v]) continue;
        dis[v] = ((val[p] % 3) + 3) % 3,ans -= calc(v);
        treeSize = size[v],maxp[root = 0] = 1<<30,getroot(v,u);
        solve(root);
    }
}
int main()
{
    read(n);
    for(int i = 1;i<n;++i)
    {
        int a,b,c;
        read(a),read(b),read(c);
        add(a,b,c),add(b,a,c);
    }
    root = 1,treeSize = n;
    getroot(1,0);
    solve(root);
    int g = gcd(n*n,ans);
    printf("%d/%d",ans/g,n*n/g);
    return 0;
}