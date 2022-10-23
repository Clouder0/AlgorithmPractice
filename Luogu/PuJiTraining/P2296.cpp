#include <cstdio>
#include <cstring>
#include <queue>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxm = 5e5 + 100;
const int maxn = 1e5 + 100;
struct node
{
    int to,next;
}E[maxm],F[maxm];
int head[maxn],headF[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
inline void addF(const int &x,const int &y)
{
    static int tot = 0;
    F[++tot].next = headF[x],F[tot].to = y,headF[x] = tot;
}
int n,m,s,t;
int vis[maxn],dis[maxn],can[maxn],st[maxn],top;
void bfs()
{
    st[++top] = t;
    int u,v;
    while(top)
    {
        u = st[top--];
        can[u] = 1;
        for(int p = headF[u];p;p=F[p].next)
        {
            v = F[p].to;
            if(can[v]) continue;
            st[++top] = v;
        }
    }
}
int vvis[maxn];
void bfs2()
{
    st[top = 1] = s;
    int u,v;
    while(top)
    {
        u = st[top--];
        if(vvis[u]) continue;
        vvis[u] = 1;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(!can[v]) vis[u] = 1;
            if(can[v]) st[++top] = v;
        }
    }
}
using namespace std;
std::priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
void dij2()
{
    memset(dis,0x3f,sizeof(dis));
    dis[s] = 0;
    q.push(make_pair(0,s));
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
            if(!vis[v] && can[v] && dis[v] > dis[u] + 1)
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
    read(m);
    while(m--)
    {
        int x,y;
        read(x),read(y);
        add(x,y),addF(y,x);
    }
    read(s),read(t);
    bfs();
    bfs2();
    if(!can[s])
    {
        puts("-1");
        return 0;
    }
    dij2();
    printf("%d",dis[t]);
    return 0;
}