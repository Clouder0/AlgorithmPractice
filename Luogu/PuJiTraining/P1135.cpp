#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
void read(int &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
struct node
{
    int next,to;
    node(){}
    node(const int &_to,const int &_next):to(_to),next(_next){}
}lines[41000];
int head[210];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    lines[++tot] = node(y,head[x]),head[x] = tot;
}
int n,a,b;
int dis[210];
bool vis[210];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
void dij()
{
    memset(dis,0x3f,sizeof(dis));
    dis[a] = 0;
    q.push(make_pair(dis[a],a));
    int u,v;
    while(!q.empty())
    {
        u = q.top().second;
        q.pop();
        if(vis[u])
            continue;
        vis[u] = true;
        for(int p = head[u];p;p=lines[p].next)
        {
            v = lines[p].to;
            if(!vis[v] && dis[u] + 1 < dis[v])
            {
                dis[v] = dis[u] + 1;
                q.push(make_pair(dis[v],v));
            }
        }
    }
}
int main()
{
    read(n);
    read(a);
    read(b);
    int k;
    for(int i = 1;i<=n;++i)
    {
        read(k);
        if(i + k <= n)
            add(i,i+k);
        if(i - k >= 1)
            add(i,i-k);
    }
    dij();
    if(dis[b] >= 10000000)
        printf("-1");
    else 
        printf("%d",dis[b]);
    return 0;
}