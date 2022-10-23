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
const int maxm = 5e6;
const int maxn = 1e5 + 10;
struct node
{
    int to,next,val;
}E[maxm];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    E[tot].val = val;
    head[x] = tot;
}
int n,m,c,A,B;
int dis[maxn],vis[maxn];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
void dij()
{
    memset(dis,0x3f,sizeof(dis));
    dis[A] = 0;
    q.push(make_pair(0,A));
    int u,v;
    while(!q.empty())
    {
        u = q.top().second;
        q.pop();
        if(vis[u])
            continue;
        vis[u] = 1;
        if(u == B)
            return;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(!vis[v] && dis[u] + E[p].val < dis[v])
            {
                dis[v] = dis[u] + E[p].val;
                q.push(make_pair(dis[v],v));
            }
        }
    }
}
int main()
{
    read(n);
    read(m);
    read(c);
    int f,t,v;
    for(int i = 1;i<=m;++i)
    {
        read(f);
        read(t);
        read(v);
        add(f,t,v);
    }
    read(A);
    read(B);
    for(int i = 0;i<=n;++i)
        for(int j = 1;j<=n;j<<=1)
            if((i^j) <= n)
                add(i,i^j,j*c);
    dij();
    printf("%d",dis[B]);
    return 0;
}