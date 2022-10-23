#include <cstdio>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
const int maxn = 1e6 + 10;
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x];
    E[tot].to = y;
    head[x] = tot;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n;
long long f[maxn],size[maxn],dep[maxn],ans;
void dfs1(int u,int fa)
{
    size[u] = 1;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == fa)
            continue;
        dep[v] = dep[u] + 1;
        dfs1(v, u);
        size[u] += size[v];
    }
}
void dfs(int u,int fa)
{
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == fa)
            continue;
        f[v] = f[u] + n - (size[v]<<1);
        dfs(v,u);
    }
    if(f[u] > f[ans])
        ans = u;
}
int main()
{
    read(n);
    int x,y;
    for(int i = 1;i<n;++i)
    {
        read(x);
        read(y);
        add(x,y);
        add(y,x);
    }
    dfs1(1,0);
    for(int i = 1;i<=n;++i)
        f[1] += dep[i];
    dfs(1, 0);
    printf("%d", ans);
    return 0;
}