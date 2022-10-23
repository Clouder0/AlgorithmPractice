#include <cstdio>
#include <queue>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 1600;
const int maxm = 5e4 + 10;
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
int n,m;
int in[maxn];
queue<int> q;
int f[maxn];
void topo()
{
    q.push(1);
    for(int i = 2;i<=n;++i)
    {
        f[i] = 1<<31;
        if(!in[i])
            q.push(i);
    }
    int u,v;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(f[v] < f[u] + E[p].val)
                f[v] = f[u] + E[p].val;
            if(--in[v] == 0)
                q.push(v);
        }
    }
}
int main()
{
    read(n);
    read(m);
    int a,b,c;
    while(m--)
    {
        read(a);
        read(b);
        read(c);
        add(a,b,c);
        in[b]++;
    }
    topo();
    if(f[n] == 1<<31)
        puts("-1");
    else
        printf("%d",f[n]);
    return 0;
}