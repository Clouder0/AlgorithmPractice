#include <cstdio>
#include <iostream>
#include <memory.h>
using namespace std;
int n,m;
int dp[100][100];
int num[100];
int dfs(int pos,int lim,int last)
{
    if(pos == 0)
        return dp[pos][last] = 1;
    if(!lim && dp[pos][last] != -1)
        return dp[pos][last];
    int up = lim?num[pos]:9;
    int ans = 0;
    for(int i = 0;i<=up;++i)
    {
        if(i == 4 || (last == 6 && i == 2))
            continue;
        ans += dfs(pos - 1,lim&&i==num[pos],i);
    }
    if(!lim)
        dp[pos][last] = ans;
    return ans;
}
int solve(int x)
{
    memset(dp,-1,sizeof(dp));
    int cnt = 0;
    for(;x;num[++cnt] = x % 10,x /= 10);
    return dfs(cnt,true,0);
}
int main()
{
    while(cin >> n >> m && n != 0 && m != 0)
        cout << solve(m) - solve(n - 1) << endl;
    return 0;
}