#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 100;
struct node
{
    int to,next;
}E[maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n,t;
int fa[maxn],P[maxn],Q[maxn];
long long dis[maxn],lim[maxn];
int size[maxn],maxSon[maxn],root;
int vis[maxn];
void getdis(int u){for(int p = head[u];p;p=E[p].next) dis[E[p].to] += dis[u],getdis(E[p].to);}
void getroot(int u,int treeSize)
{
    size[u] = 1, maxSon[u] = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(vis[v]) continue;
        getroot(v,treeSize);
        size[u] += size[v];
        if(size[v] > maxSon[u]) maxSon[u] = size[v];
    }
    if(treeSize - size[u] > maxSon[u]) maxSon[u] = treeSize - size[u];
    if(maxSon[root] >= maxSon[u]) root = u;
}
int points[maxn],cnt;
void dfs1(int u)
{
    points[++cnt] = u;
    for(int p = head[u];p;p=E[p].next) if(!vis[E[p].to]) dfs1(E[p].to);
}
bool cmp(const int &a,const int &b){return dis[a] - lim[a] > dis[b] - lim[b];}
int s[maxn],top;
long long dp[maxn];
inline double slope(int x1,int x2) {return (double)(dp[x1] - dp[x2]) / (dis[x1] - dis[x2]);}
double sl[maxn];
inline void insert(int x)
{
    while(top >= 2 && sl[top - 1] < slope(s[top],x)) --top;
    s[++top] = x,sl[top - 1] = slope(s[top - 1],s[top]),sl[top] = -1e30;
}
inline int binary_search(double val)
{
    int l = 1,r = top,mid,ans = 0;
    while(l <= r)
    {
        mid = l + r >> 1;
        if(sl[mid] <= val) ans = mid,r = mid - 1;
        else l = mid + 1;
    }
    return s[ans];
}
void solve(int u,int treeSize)
{
    if(treeSize == 1) return;
    maxSon[root = 0] = 1ll << 60, getroot(u, treeSize);
    int x = root;
    for (int p = head[x]; p; p = E[p].next) vis[E[p].to] = 1, treeSize -= size[E[p].to];
    solve(u, treeSize);

    cnt = 0;
    for (int p = head[x]; p; p = E[p].next) dfs1(E[p].to);
    std::sort(points + 1,points + 1 + cnt,cmp);

    top = 0;
    int pointer = x;
    for (int i = 1; i <= cnt; ++i)
    {
        int a = points[i];
        while(pointer != fa[u] && dis[a] - lim[a] <= dis[pointer]) insert(pointer),pointer = fa[pointer];
        if(top)
        {
            int k = binary_search(P[a]);
            dp[a] = std::min(dp[a],dp[k] + (dis[a] - dis[k]) * P[a] + Q[a]);
        }
    }

    for (int p = head[x]; p; p = E[p].next) solve(E[p].to, size[E[p].to]);
}
signed main()
{
    read(n),read(t);
    for(int i = 2;i<=n;++i)
    {
        read(fa[i]),read(dis[i]),read(P[i]),read(Q[i]),read(lim[i]);
        add(fa[i],i);
    }
    memset(dp,0x3f,sizeof(dp));
    dp[1] = 0;
    getdis(1);
    solve(1,n);
    for(int i = 2;i<=n;++i) printf("%lld\n",dp[i]);
    return 0;
}