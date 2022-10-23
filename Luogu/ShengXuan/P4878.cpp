#include <cstdio>
#include <queue>
#include <cstring>
const int maxn = 1e3 + 10;
const int maxm = 2e4 + 10;
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
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,ml,md;
std::queue<int> q;
int dis[maxn],pre[maxn],ins[maxn];
bool spfa(int uu)
{
    q.push(uu);
    int u, v;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        pre[u]++;
        if(pre[u] > n + 2)
            return true;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(dis[v] > dis[u] + E[p].val)
            {
                dis[v] = dis[u] + E[p].val;
                if(!ins[v])
                    q.push(v);
            }
        }
    }
    return false;
}
int main()
{
    read(n);
    read(ml);
    read(md);
    int a,b,c;
    while(ml--)
    {
        read(a);
        read(b);
        read(c);
        add(a,b,c);
    }
    while(md--)
    {
        read(a);
        read(b);
        read(c);
        add(b,a,-c);
    }
    for(int i = 1;i<n;++i)
        add(i+1,i,0);
    memset(dis,0x3f,sizeof(dis));
    dis[1] = 0;
    if(spfa(1))
    {
        puts("-1");
        return 0;
    }
    for(int i = 2;i<=n;++i)
        if(dis[i] > 100000000 && spfa(i))
        {
            puts("-1");
            return 0;
        }
    if(dis[n] > 10000000)
        puts("-2");
    else
        printf("%d",dis[n]);
    return 0;
}