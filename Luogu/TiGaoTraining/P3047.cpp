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
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    head[x] = tot;
}
int w[maxn];
int n,k;
int f[maxn][21],d[maxn][21];
void dfs1(int u,int fa)
{
    for(int i = 0;i<=k;++i)
        d[u][i] = w[u];
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == fa)
            continue;
        dfs1(v,u);
        for(int i = 1;i<=k;++i)
            d[u][i] += d[v][i-1];
    }
}
void dfs2(int u,int fa)
{
    f[u][0] = w[u];
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == fa)
            continue;
        f[v][1] = f[u][0] + d[v][1];
        for(int i = 2;i<=k;++i)
            f[v][i] = f[u][i-1] + d[v][i] - d[v][i-2];
        dfs2(v,u);
    }
}
int main()
{
    read(n);
    read(k);
    for(int i = 1;i<n;++i)
    {
        int a,b;
        read(a);
        read(b);
        add(a,b);
        add(b,a);
    }
    for(int i = 1;i<=n;++i)
        read(w[i]);
    dfs1(1,0);
    for(int i = 1;i<=k;++i)
        f[1][i] = d[1][i];
    dfs2(1,0);
    for(int i = 1;i<=n;++i)
        printf("%d\n",f[i][k]);
    return 0;
}