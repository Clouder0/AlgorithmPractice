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
    int to,next,val;
    node(){}
    node(const int &_to,const int &_next,const int &_val) : to(_to),next(_next),val(_val){}
}lines[201000];
int head[310];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    lines[++tot] = node(y,head[x],val),head[x] = tot;
}
int n,m;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
int dis[310];
bool vis[310];
int prim()
{
    int ans = 0;
    memset(dis,0x3f,sizeof(dis));
    dis[1] = 0;
    q.push(make_pair(0,1));
    int u,v,d;
    while(!q.empty())
    {
        u = q.top().second;
        d = q.top().first;
        q.pop();
        if(vis[u])  
            continue;
        vis[u] = 1;
        ans = ans > d ? ans : d;
        for(int p = head[u];p;p=lines[p].next)
        {
            v = lines[p].to;
            if(!vis[v] && lines[p].val < dis[v])
            {
                dis[v] = lines[p].val;
                q.push(make_pair(lines[p].val,v));
            }
        }
    }
    return ans;
}
int main()
{
    read(n);
    read(m);
    int a,b,c;
    for(;m;--m)
    {
        read(a);
        read(b);
        read(c);
        add(a,b,c);
        add(b,a,c);
    }
    printf("%d %d",n-1,prim());
    return 0;
}