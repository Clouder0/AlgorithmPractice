#include <cstdio>
#include <memory.h>
using namespace std;
int n;
long long dp[20][20];
int num[20];
long long dfs(int pos,int lim,int sum)
{
    if(pos == 0)
        return sum;
    if(!lim && dp[pos][sum] != -1)
        return dp[pos][sum];
    int up = lim?num[pos]:9;
    long long ans = 0;
    for(int i = 0;i<=up;++i)
        ans += dfs(pos-1,lim&&i==up,sum+(i==1));
    if(!lim)
        dp[pos][sum] = ans;
    return ans;
}
inline long long solve(int x)
{
    memset(dp,-1,sizeof(dp));
    int cnt = 0;
    for(;x;x/=10)
        num[++cnt] = x%10;
    return dfs(cnt,1,0);
}
int main()
{
    scanf("%d",&n);
    printf("%lld\n",solve(n));
    return 0;
}