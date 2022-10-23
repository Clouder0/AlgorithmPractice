#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 1100;
struct node
{
    int to,next,val;
    node(){}
    node(const int &_to,const int &_next,const int &_val) : to(_to),next(_next),val(_val){}
}lines[2001000];
int head[maxn];
void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    lines[++tot] = node(y,head[x],val),head[x] = tot;
}
int n,m;
double dis[maxn];
int tdis[maxn];
bool vis[maxn];
priority_queue<pair<double,int> > q;
void dij()
{
    for(int i = 2;i<=n;++i)
        dis[i] = 9999999999.0;
    dis[1] = 0;
    tdis[1] = 1;
    q.push(make_pair(0.0,1));
    int u,v;
    while(!q.empty())
    {
        u = q.top().second;
        q.pop();
        if(vis[u])
            continue;
        for(int p = head[u];p;p=lines[p].next)
        {
            v = lines[p].to;
            if(!vis[v] && dis[v] > dis[u] + log10(lines[p].val))
            {
                dis[v] = dis[u] + log10(lines[p].val);
                tdis[v] = (tdis[u] * lines[p].val) % 9987;
                q.push(make_pair(dis[v],v));
            }
        }
    }
}
void read(int &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int main()
{
    read(n);
    read(m);
    int x,y,z;
    while(m--)
    {
        read(x);
        read(y);
        read(z);
        add(x,y,z);
        add(y,x,z);
    }
    dij();
    printf("%d",tdis[n]);
    return 0;
}