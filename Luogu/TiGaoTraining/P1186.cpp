#include <cstdio>
#include <memory.h>
#include <queue>
using namespace std;
inline char nc()
{
    return getchar();
}
template<typename T>
inline T read(T &r)
{
    static char c;r = 0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
    return r;
}
const int maxm = 1e6 + 1000;
const int maxn = 1e3 + 100;
struct node
{
    int to,next,val;
}E[maxm];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot] = (node){y,head[x],val},head[x] = tot;
}
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
int dis[maxn],vis[maxn];
int pre[maxn];
int bx,by;
int n,m;
inline void dij()
{
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[n]  = 0;
    q.push(make_pair(0,n));
    int u,v;
    while(!q.empty())
    {
        u = q.top().second;
        q.pop();
        if(vis[u])
            continue;
        vis[u] = 1;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(u == bx && v == by)
                continue;
            if(u == by && v == bx)
                continue;
            if(!vis[v] && dis[v] > dis[u] + E[p].val)
            {
                dis[v] = dis[u] + E[p].val;
                pre[v] = u;
                q.push(make_pair(dis[v],v));
            }
        }
    }
}
int X[maxn],Y[maxn],cnt;
int main()
{
    read(n);
    read(m);
    int a,b,v;
    for(int i = 1;i<=m;++i)
    {
        read(a);
        read(b);
        read(v);
        add(a,b,v);
        add(b,a,v);
    }
    dij();
    int u = pre[1];
    v = 1;
    while(v != n)
    {
        X[++cnt] = u;
        Y[cnt] = v;
        v = u;
        u = pre[u];
    }
    int ans = 0;
    for(int i = 1;i<=cnt;++i)
    {
        bx = X[i],by = Y[i];
        dij();
        if(ans < dis[1])
            ans = dis[1];
    }
    printf("%d",ans);
    return 0;
}