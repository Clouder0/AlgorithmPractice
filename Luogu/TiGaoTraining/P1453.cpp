#include <cstdio>
#include <cstring>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
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
int n;
int p[maxn];
double k;
int vis[maxn];
int r1,r2;
void dfs1(int u,int fa)
{
    if(r1)
        return;
    vis[u] = 1;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == fa)
            continue;
        if(vis[v])
        {
            r1 = u,r2 = v;
            return;
        }
        dfs1(v,u);
    }
}
int f[maxn][2];
void dfs2(int u,int fa)
{
    f[u][0] = 0,f[u][1] = p[u];
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == fa || (u == r1 && v == r2) || (u == r2 && v == r1))
            continue;
        dfs2(v,u);
        f[u][0] += max(f[v][0],f[v][1]);
        f[u][1] += f[v][0];
    }
}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(p[i]);
    for(int i = 1;i<=n;++i)
    {
        int a,b;
        read(a);
        read(b);
        ++a,++b;
        add(a,b);
        add(b,a);
    }
    scanf("%lf",&k);
    dfs1(1, 0);
    dfs2(r1, 0);
    int ans = f[r1][0];
    dfs2(r2,0);
    ans = max(ans,f[r2][0]);
    printf("%.1f",(double)ans * k);
    return 0;
}