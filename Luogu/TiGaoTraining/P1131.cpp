#include <cstdio>
using namespace std;
const int maxn = 5e5 + 10;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
struct node
{
    int to,next,val;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    E[tot].val = val;
    head[x] = tot;
}
int n,s;
long long f[maxn];
long long ans;
void dfs(int u,int from)
{
    int v,sum = 0,size = 0;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == from)
            continue;
        dfs(v,u);
        f[u] = (f[u] > E[p].val + f[v] ? f[u] : E[p].val + f[v]);
        sum += E[p].val + f[v];
        ++size;
    }
    ans += f[u] * size - sum;
}
int main()
{
    read(n);
    read(s);
    int a,b,c;
    for(int i = 1;i<n;++i)
    {
        read(a);
        read(b);
        read(c);
        add(a,b,c);
        add(b,a,c);
    }
    dfs(s,0);
    printf("%lld",ans);
    return 0;
}