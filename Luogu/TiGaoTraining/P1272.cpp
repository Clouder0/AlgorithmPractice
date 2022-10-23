#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
const int maxn = 160;
struct node
{
    int to,next;
}E[maxn];
int head[maxn],fa[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    head[x] = tot;
}
int n,P;
int dp[maxn][maxn];
int size[maxn],son[maxn];
void dfs(int u)
{
    int v;
    size[u] = 1;
    dp[u][1] = son[u];
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        dfs(v);
        for(int i = size[u];i;--i)
            for(int j = 1;j<=size[v] && i+j <= P;++j)
                dp[u][i+j] = min(dp[u][i+j],dp[u][i] + dp[v][j] - 1);
        size[u] += size[v];
    }
}
int ans = 1<<30;
void dfs2(int u)
{
    if(ans > dp[u][P])
        ans = dp[u][P] + 1;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        dfs2(v);
    }
}
bool root[maxn];
int main()
{
    memset(dp,0x3f,sizeof(dp));
    scanf("%d%d",&n,&P);
    int x,y;
    for(int i = 1;i<n;++i)
        scanf("%d%d",&x,&y),fa[y] = x,add(x,y),root[y] = true,son[x]++;
    int r = 0;
    for(int i = 1;!r&&i<=n;++i)
        if(!root[i])
            r = i;
    dfs(r);
    ans = dp[r][P];
    dfs2(r);
    printf("%d",ans);
    return 0;
}