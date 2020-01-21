#include <cstdio>
using namespace std;
int n,x;
int to[100010],nxt[100010],head[50010],dp[50010];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    nxt[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
}
int ans = 0;
bool vis[50010];
void dfs(int u,int fa)
{
    for(int p = head[u];p;p=nxt[p])
    {
    	if(to[p] == fa)
            continue;
        dfs(to[p],u);
        if(dp[u] + dp[to[p]] + 1 > ans)
            ans = dp[u] + dp[to[p]] + 1;
        if(dp[to[p]] + 1 > dp[u])
            dp[u] = dp[to[p]] + 1;
    }
}
int main()
{
    scanf("%d",&x);
    for(int n = 2;n<=x;++n)
    {
        int sum = 1;
        for(int i = 2;i*i<=n;++i)
            if(n % i == 0)
            {
                if(i * i == n)
                    sum += i;
                else
                    sum += i + n/i;
            }
        if(sum < n)
        {
            add(n,sum);
            add(sum,n);
        }
    }
    dfs(1,0);
    printf("%d",ans);
    return 0;
}