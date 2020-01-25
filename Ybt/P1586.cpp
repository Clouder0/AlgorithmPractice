#include <iostream>
#include <cstdio>
#include <memory.h>
using namespace std;
int a,b;
long long dp[50][50];
int num[50];
int cnt;
long long dfs(int pos,int limit,int last)
{
    if(!limit && dp[pos][last] != -1)
        return dp[pos][last];
    if(pos == 0)
        return dp[pos][last] = 1;
    long long ans = 0;
    int up = limit?num[pos]:9;
    for(int i = last;i<=up;++i)
        ans += dfs(pos-1,(i==num[pos])&&limit,i);
    if(!limit)
        dp[pos][last] = ans;
    return ans;
}
long long solve(int x)
{
    memset(dp,-1,sizeof(dp));
    for(cnt = 0;x;num[++cnt] = x % 10,x /= 10);
    return dfs(cnt,true,0);
}
int main()
{
    while(cin >> a >> b)
        printf("%lld\n",solve(b) - solve(a-1));
    return 0;
}