#include <cstdio>
#define WALK for(int p = head[u];p;p=E[p].next)
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 5e4 + 100;
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn],tot;
inline void add(const int &x,const int &y)
{
    E[++tot].next = head[x],head[x] = tot,E[tot].to = y;
}
int n,k;
long long ans;
int size[maxn],maxp[maxn],vis[maxn],treeSize,root;
void getroot(int u,int fa)
{
    size[u] = 1,maxp[u] = 0;
    WALK
    {
        int v = E[p].to;
        if(vis[v] || v == fa) continue;
        getroot(v,u);
        size[u] += size[v];
        maxp[u] = max(maxp[u],size[v]);
    }
    maxp[u] = max(maxp[u],treeSize - size[u]);
    if(maxp[u] < maxp[root]) root = u;
}
int dis[maxn],map[510];
void getdis(int u,int fa)
{
    if(dis[u] > 500) return;
    map[dis[u]]++;
    WALK
    {
        int v = E[p].to;
        if(vis[v] || v == fa) continue;
        dis[v] = dis[u] + 1;
        getdis(v,u);
    }
}
long long calc(int u,int initDis)
{
    long long res = 0;
    dis[u] = initDis;
    getdis(u,0);
    for(int i = 0;i<=k;++i) res += 1ll * map[i] * map[k-i];
    for(int i = 0;i<=k;++i) map[i] = 0;
    return res;
}
void solve(int u)
{
    vis[u] = 1;
    ans += calc(u,0);
    WALK
    {
        int v = E[p].to;
        if(vis[v]) continue;
        ans -= calc(v,1);
        treeSize = size[v],maxp[root = 0] = 1<<30,getroot(v,u);
        solve(root);
    }
}
int main()
{
    read(n),read(k);
    for(int i = 1;i<n;++i)
    {
        int a,b;
        read(a),read(b);
        add(a,b),add(b,a);
    }
    treeSize = n,maxp[root = 1] = n,getroot(1,0);
    solve(1);
    printf("%lld",ans>>1);
    return 0;
}