#include <cstdio>
#include <memory.h>
using namespace std;
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e4 + 100;
const int maxm = 1e5 + 100;
struct node
{
    int to,next;
}E[maxm];
int head[maxn];
int tot = 0;
inline void add(const int &x,const int &y)
{
    E[++tot] = (node){y,head[x]},head[x] = tot;
}
int w[maxn];
int n,m;
int dfn[maxn],low[maxn],s[maxn],st;
int belong[maxn];
bool vis[maxn];
int time;
void dfs(int u)
{
    vis[u] = true;
    low[u] = dfn[u] = ++time;
    s[++st] = u;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u],low[v]);
        }
        else if(vis[v])
            low[u] = min(low[u],low[v]);
    }
    if(dfn[u] == low[u])
    {
        int p;
        while(p = s[st--])
        {
            belong[p] = u;
            vis[p] = false;
            if(u == p)
                break;
            w[u] += w[p];
        }
    }
}
int dp[maxn];
int dfs2(int u)
{
    if(dp[u] != -1)
        return dp[u];
    int v;
    int maxx = 0;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        dfs2(v);
        if(maxx < dp[v])
            maxx = dp[v];
    }
    return dp[u] = maxx + w[u];
}
int X[maxm],Y[maxm];
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(w[i]);
    int x,y;
    for(int i = 1;i<=m;++i)
    {
        read(X[i]);
        read(Y[i]);
        add(X[i],Y[i]);
    }
    for(int i = 1;i<=n;++i)
        if(!dfn[i])
            dfs(i);
    memset(head,0,sizeof(head));
    tot = 0;
    for(int i = 1;i<=m;++i)
        if(belong[X[i]] != belong[Y[i]])
            add(belong[X[i]],belong[Y[i]]);
    memset(dp,-1,sizeof(dp));
    int ans = 0;
    for(int i = 1;i<=n;++i)
        if(dp[i] == -1 && dfs2(i) > ans)
            ans = dp[i];
    printf("%d",ans);
    return 0;
}