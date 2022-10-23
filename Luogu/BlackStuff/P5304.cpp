#include <cstdio>
#include <queue>
#include <memory.h>
using namespace std;
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
const int maxn = 1e5 + 10;
const int maxm = 5e5 + 10;
struct node
{
    int to,next,val;
    node(){}
    node(const int &_to,const int &_next,const int &_val): to(_to),next(_next),val(_val){}
}E[maxm];
int X[maxm],Y[maxm],W[maxm];
int head[maxn];
int tot = 0;
inline void add(const int &x,const int &y,const int &val)
{
    E[++tot] = node(y,head[x],val),head[x] = tot;
}
int T;
int n,m,k;
int pos[maxn];
int col[2][maxn];
bool vis[maxn];
long long dis[2][maxn];
priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > q;
inline void dij(long long *dis,int *col)
{
    for(int i = 0;i<=n;++i)
        vis[i] = col[i] = 0,dis[i] = 1ll<<60;
    for(int i = 1;i<=k;++i)
    {
        dis[pos[i]] = 0;
        col[pos[i]] = pos[i];
        q.push(make_pair(0ll,pos[i]));
    }
    int u,v;
    while(!q.empty())
    {
        u = q.top().second;
        q.pop();
        if(vis[u])
            continue;
        vis[u] = true;
        for(int e = head[u];e;e=E[e].next)
        {
            v = E[e].to;
            if(!vis[v] && dis[v] > dis[u] + E[e].val)
            {
                dis[v] = dis[u] + E[e].val;
                col[v] = col[u];
                q.push(make_pair(dis[v],v));
            }
        }
    }
}
int main()
{
    read(T);
    while(T--)
    {
        memset(head,0,sizeof(head));
        tot = 0;
        read(n);
        read(m);
        read(k);
        int x,y,z;
        for(int i = 1;i<=m;++i)
        {
            read(X[i]),read(Y[i]),read(W[i]);
            if(X[i] != Y[i])
                add(X[i],Y[i],W[i]);
        }
        for(int i = 1;i<=k;++i)
            read(pos[i]);
        dij(dis[0],col[0]);
        memset(head,0,sizeof(head));
        tot = 0;
        for(int i = 1;i<=m;++i)
            if(X[i] != Y[i])
                add(Y[i],X[i],W[i]);
        dij(dis[1],col[1]);
        long long ans = 1ll<<60;
        int u,v,val;
        for(int i = 1;i<=m;++i)
        {
            u = X[i],v = Y[i],val = W[i];
            if(col[0][u] && col[1][v] && col[0][u] != col[1][v] && ans > dis[0][u] + dis[1][v] + val)
                ans = dis[0][u] + dis[1][v] + val;
        }
        printf("%lld\n",ans);
    }
    return 0;
}