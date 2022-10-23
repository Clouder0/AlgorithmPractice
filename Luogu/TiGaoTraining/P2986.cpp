#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
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
long long w[maxn];
int n;
long long depth[maxn],size[maxn];
long long f[maxn];
void dfs1(int u,int fa)
{
    size[u] = w[u];
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == fa)
            continue;
        depth[v] = depth[u] + E[p].val;
        dfs1(v,u);
        size[u] += size[v];
    }
}
void dfs2(int u,int fa)
{
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == fa)
            continue;
        f[v] = f[u] + (long long)(size[1] - 2 * size[v]) * E[p].val;
        dfs2(v,u);
    }
}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(w[i]);
    int a,b,c;
    for(int i = 1;i<n;++i)
    {
        read(a);
        read(b);
        read(c);
        add(a,b,c);
        add(b,a,c);
    }
    dfs1(1,0);
    for(int i = 2;i<=n;++i)
        f[1] += w[i] * depth[i];
    dfs2(1,0);
    long long ans = 1ll<<60;
    for(int i = 1;i<=n;++i)
        if(f[i] < ans)
            ans = f[i];
    printf("%lld",ans);
    return 0;
}