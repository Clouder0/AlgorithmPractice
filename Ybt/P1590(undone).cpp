#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int T;
long long L,R;
int num[100];
long long dp[50][50][50];
const long long mod = 1e9 + 7;
long long dfs(int pos,bool limit,int sum,int now,long long origin)
{
    sum %= 7;
    now %= 7;
    if(pos == 0)
        return dp[pos][sum][now] = (sum && now)?(origin % mod * origin) % mod:0;
    if(!limit && dp[pos][sum][now] != -1)
        return dp[pos][sum][now];
    int up = limit?num[pos]:9;
    long long ans = 0;
    for(int i = 0;i<=up;++i)
        if(i != 7)
            ans += dfs(pos-1,limit&&i==num[pos],sum+i,now * 10 + i,origin * 10 + i);
    ans %= mod;
    if(!limit)
        dp[pos][sum][now] = ans;
    return ans;
}
long long solve(long long x)
{
    memset(dp,-1,sizeof(dp));
    int cnt = 0;
    for(;x;num[++cnt] = x % 10,x /= 10);
    return dfs(cnt,true,0,0,0);
}
int main()
{
    read(T);
    while(T--)
    {
        read(L);
        read(R);
        printf("%lld\n",solve(R) - solve(L-1));
    }
    return 0;
}