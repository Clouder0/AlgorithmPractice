#include <cstdio>
#include <queue>
#include <time.h>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 10;
struct node
{
    int to,next,val;
}E[maxn<<2];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot] = (node){y,head[x],val},head[x] = tot;
}
int dis[maxn];
int n,m;
bool cyc;
priority_queue<int,vector<int>,greater<int> > q;
clock_t start;
int cnt[maxn];
inline void sbfa()
{
    int times = 0;
    start = clock();
    memset(dis,0x3f,sizeof(dis));
    q.push(0);
    dis[0] = 0;
    int u,v;
    while(!q.empty())
    {
        /*
        ++times;
        if(times >= 1000)
        {
            times = 0;
            if(clock() - start >= 0.7 * CLOCKS_PER_SEC)
            {
                cyc = 1;
                return;
            }
        }
        */
        u = q.top();
        q.pop();
        ++cnt[u];
        if(cnt[u] > n)
        {
            cyc = 1;
            break;
        }
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(dis[v] > dis[u] + E[p].val)
            {
                dis[v] = dis[u] + E[p].val;
                q.push(v);
            }
        }
    }
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
    {
        add(i-1,i,1);
        add(i,i-1,0);
    }
    int l,r;
    for(int i = 1;i<=m;++i)
    {
        read(l);
        read(r);
        add(l-1,r,1);
        add(r,l-1,-1);
    }
    memset(dis,0x3f,sizeof(dis));
    sbfa();
    if(cyc)
        printf("-1");
    else
        printf("%d",dis[n]);
    return 0;
}