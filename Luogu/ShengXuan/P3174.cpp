#include <cstdio>
using namespace std;
template<typename T>
inline T _max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 3e5 + 100;
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot;
    E[++tot].next = head[x];
    E[tot].to = y;
    head[x] = tot;
}
int n,m;
int f[maxn];
int ans;
void dfs(int u,int from)
{
    int son = 0;
    int maxx = 0,secx = 0;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == from)
            continue;
        dfs(v,u);
        ++son;
        if(f[v] > maxx)
            secx = maxx,maxx = f[v];
        else if(f[v] > secx)
            secx = f[v];
    }
    if(son == 0)
    {
        f[u] = 1;
        if(from == 0)
            ans = _max(ans,f[u]);
        else
            ans = _max(ans,f[u] + 1);
        return;
    }
    if(son == 1)
    {
        f[u] = maxx + 1;
        if (from == 0)
            ans = _max(ans,f[u]);
        else
            ans = _max(ans,f[u] + 1);
        return;
    }
    f[u] = maxx + son;
    if(from == 0)
        ans = _max(ans,maxx + secx + son - 1);
    else
        ans = _max(ans,maxx + secx + son);
}
int main()
{
    read(n);
    read(m);
    int a,b;
    for(int i = 1;i<=m;++i)
    {
        read(a);
        read(b);
        add(a,b);
        add(b,a);
    }
    dfs(1,0);
    printf("%d",ans);
    return 0;
}