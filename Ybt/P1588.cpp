#include <cstdio>
#include <iostream>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int a,b,N;
long long dp[100][100];
int num[100];
long long dfs(int pos,int limit,int sum)
{
    sum %= N;
    if(pos == 0)
        return dp[pos][sum] = (sum == 0);
    if(!limit && dp[pos][sum] != -1)
        return dp[pos][sum];
    int up = limit?num[pos]:9;
    int ans = 0;
    for(int i = 0;i<=up;++i)
        ans += dfs(pos - 1,i == num[pos] && limit,sum + i);
    if(!limit)
        dp[pos][sum] = ans;
    return ans;
}
long long solve(int x)
{
    memset(dp,-1,sizeof(dp));
    int cnt = 0;
    for(;x;num[++cnt] = x % 10,x /= 10);
    return dfs(cnt,true,0);
}
int main()
{
    while(cin >> a >> b >> N)
        printf("%lld\n",solve(b) - solve(a-1));
    return 0;
}