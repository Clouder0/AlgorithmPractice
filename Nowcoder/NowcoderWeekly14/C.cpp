#include <cstdio>
#define int long long
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 100;
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],head[x] = tot,E[tot].to = y;
}
const long long mod = 1e9 + 7;
int n;
long long f[maxn],ans[maxn],g[maxn];
int fa[maxn];
void dfs1(int u)
{
    f[u] = 1;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u,dfs1(v);
        f[u] = f[u] * (f[v] + 1) % mod;
    }
}
inline long long fastpow(long long x,int k)
{
    long long res = 1,t = x;
    while(k) 
    {
        if(k & 1) res  = res * t % mod;
        t = t * t % mod;
        k >>= 1;
    }
    return res;
}
inline long long inv(long long x){return fastpow(x,mod - 2);}
void dfs2(int u)
{
    if(fa[u])
    {
        long long gu;
        if((f[u] + 1) % mod == 0)
        {
            gu = g[fa[u]] + 1;
            for(int p = head[fa[u]];p;p=E[p].next)
            {
                int v = E[p].to;
                if(v == u || v == fa[fa[u]]) continue;
                gu = gu * (f[v] + 1) % mod;
            }
        }
        else gu = ans[fa[u]] * inv(f[u] + 1) % mod;
        g[u] = gu, ans[u] = (gu + 1) * f[u] % mod;
    }
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        dfs2(v);
    }
}
signed main()
{
    read(n);
    for(int i = 1;i<n;++i)
    {
        int x,y;
        read(x),read(y);
        add(x,y),add(y,x);
    }
    dfs1(1), ans[1] = f[1], dfs2(1);
    for (int i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
    return 0;
}