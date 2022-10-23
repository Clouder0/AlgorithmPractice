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
const int maxn = 1e5 + 100;
struct node
{
    int to,next,val;
}E[maxn*10];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    E[tot].val = val;
    head[x] = tot;
}
int n,m;
queue<int> q;
int inq[maxn];
long long dis[maxn];
int tt[maxn];
bool flag;
void spfa()
{
    memset(dis,~0x3f,sizeof(dis));
    q.push(n+1);
    dis[n+1] = 0;
    inq[n+1] = 1;
    int u,v;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        if(tt[u] >= n + 5)
        {
            flag = 1;
            puts("-1");
            break;
        }
        inq[u] = 0;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(dis[v] < dis[u] + E[p].val)
            {
                dis[v] = dis[u] + E[p].val;
                tt[v] = tt[u] + 1;
                if(!inq[v])
                    q.push(v),inq[v] = 1;
            }
        }
    }
}
int main()
{
    read(n);
    read(m);
    int t,a,b;
    while(m--)
    {
        read(t);
        read(a);
        read(b);
        switch(t)
        {
            case 1:
                add(b,a,0);
                add(a,b,0);
                break;
            case 2:
                if(a==b)
                {
                    puts("-1");
                    return 0;
                }
                add(a,b,1);
                break;
            case 3:
                add(b,a,0);
                break;
            case 4:
                if(a == b)
                {
                    puts("-1");
                    return 0;
                }
                add(b,a,1);
                break;
            case 5:
                add(a,b,0);
                break;
        }
    }
    for(int i = n;i;--i)
        add(n+1,i,1);
    spfa();
    if(flag)
        return 0;
    long long ans = 0;
    for(int i = 1;i<=n;++i)
        ans += dis[i];
    printf("%lld",ans);
    return 0;
}