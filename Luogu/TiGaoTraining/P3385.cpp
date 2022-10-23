#include <cstdio>
#include <queue>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-')   flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r*=flag;
}
struct node
{
    int to,next,val;
    node(){}
    node(const int &_to,const int &_next,const int &_val) : to(_to),next(_next),val(_val){}
}E[10000];
int head[2100];
int tot;
inline void add(const int &x,const int &y,const int &val)
{
    E[++tot] = node(y,head[x],val),head[x] = tot;
}
int n,m,T;
queue<int> q;
bool inq[2100];
long long dis[2100];
int pre[2100];
bool spfa()
{
    memset(dis,0x3f,sizeof(dis));
    memset(inq,0,sizeof(inq));
    memset(pre,0,sizeof(pre));
    q.push(1);
    dis[1] = 0;
    pre[1] = 1;
    int u,v;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        if(pre[u] > n + 10)
            return true;
        inq[u] = 0;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(dis[v] > dis[u] + E[p].val)
            {
                dis[v] = dis[u] + E[p].val;
                pre[v] = pre[u] + 1;
                if(!inq[v])
                    q.push(v),inq[v] = 1;
            }
        }
    }
    return false;
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
        int a, b, w;
        for (int i = 1; i <= m; ++i)
        {
            read(a);
            read(b);
            read(w);
            add(a, b, w);
            if (w >= 0)
                add(b, a, w);
        }
        if(spfa())
            puts("YE5");
        else
            puts("N0");
    }
    return 0;
}