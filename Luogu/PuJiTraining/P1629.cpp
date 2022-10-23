#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e3 + 10;
const int maxm = 1e5 + 10;
struct node
{
    int next,to,val;
}E[maxm],Ef[maxm];
int head[maxn],headf[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot1 = 0;
    E[++tot1].to = y;
    E[tot1].next = head[x];
    E[tot1].val = val;
    head[x] = tot1;
    static int tot2 = 0;
    Ef[++tot2].to = x;
    Ef[tot2].next = headf[y];
    Ef[tot2].val = val;
    headf[y] = tot2;
}
int n,m;
int dis[maxn];
int dis2[maxn];
int vis[maxn];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
inline void dij()
{
    memset(dis,0x3f,sizeof(dis));
    memset(dis2,0x3f,sizeof(dis2));
    dis[1] = 0;
    dis2[1] = 0;
    q.push(make_pair(0,1));
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
            if(!vis[v] && dis[v] > dis[u] + E[p].val)
            {
                dis[v] = dis[u] + E[p].val;
                q.push(make_pair(dis[v],v));
            }
        }
    }
    memset(vis,0,sizeof(vis));
    q.push(make_pair(0,1));
    while(!q.empty())
    {
        u = q.top().second;
        q.pop();
        if(vis[u])
            continue;
        vis[u] = 1;
        for(int p = headf[u];p;p=Ef[p].next)
        {
            v = Ef[p].to;
            if(!vis[v] && dis2[v] > dis2[u] + Ef[p].val)
            {
                dis2[v] = dis2[u] + Ef[p].val;
                q.push(make_pair(dis2[v],v));
            }
        }
    }
}
int main()
{
    read(n);
    read(m);
    int a,b,c;
    for(int i = 1;i<=m;++i)
    {
        read(a);
        read(b);
        read(c);
        add(a,b,c);
    }
    dij();
    int ans = 0;
    for(int i = 2;i<=n;++i)
        ans += dis[i] + dis2[i];
    printf("%d",ans);
    return 0;
}