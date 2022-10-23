#include <cstdio>
#include <cstring>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
inline char nc()
{
    static char buf[10000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
struct node
{
    int to,next,val;
    node(){}
    node(const int &_to,const int &_next,const int &_val) : to(_to),next(_next),val(_val){}
}lines[50000];
int head[110];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    lines[++tot] = node(y,head[x],val),head[x] = tot;
}
bool vis[110];
int dis[110];
int ans;
__gnu_pbds::priority_queue<pair<int,int>,greater<pair<int,int> >,__gnu_pbds::pairing_heap_tag> q;
__gnu_pbds::priority_queue<pair<int,int>,greater<pair<int,int> >,__gnu_pbds::pairing_heap_tag>::point_iterator id[110];
void prim()
{
    memset(dis,0x3f,sizeof(dis));
    int u,v,d;
    id[1] = q.push(make_pair(0,1));
    while(!q.empty())
    {
        u = q.top().second;
        d = q.top().first;
        q.pop();
        if(vis[u])
            continue;
        vis[u] = true;
        ans += d;
        for(int p = head[u];p;p=lines[p].next)
        {
            v = lines[p].to;
            if(!vis[v] && dis[v] > lines[p].val)
            {
                dis[v] = lines[p].val;
                if(id[v] != 0)
                    q.modify(id[v],make_pair(lines[p].val,v));
                else
                    id[v] = q.push(make_pair(lines[p].val,v));
            }
        }
    }
}
int n;
int main()
{
    read(n);
    int temp;
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=n;++j)
        {
            read(temp);
            if(i != j)
                add(i,j,temp);
        }
    prim();
    printf("%d",ans);
    return 0;
}