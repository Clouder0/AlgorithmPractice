#include <cstdio>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int L,R,K,B;
long long BT[50];
int digit[50];
long long dp[50][50];
long long dfs(int pos,int num,bool limit)
{
    if(pos + num < K)
        return 0;
    if(num > K)
        return 0;
    if(pos == 0)
        return num == K;
    if(!limit && dp[pos][num] != -1)
        return dp[pos][num];
    int up = (limit&&!digit[pos])?digit[pos]:1;
    int ans = 0;
    for(int i = 0;i<=up;++i)
        ans += dfs(pos-1,num+(i==1),limit&&(i == digit[pos]));
    if(!limit)
        dp[pos][num] = ans;
    return ans;
}
inline long long solve(int x)
{
    memset(dp,-1,sizeof(dp));
    memset(digit,0,sizeof(digit));
    int cnt = 0;
    while(x)
        digit[++cnt] = x % B,x /= B;
    return dfs(cnt,0,true);
}
int main() 
{
    read(L);
    read(R);
    read(K);
    read(B);
    BT[0] = 1;
    for(int i = 1;i<=31;++i)
        BT[i] = BT[i-1] * B;
    printf("%lld",solve(R) - solve(L-1));
    return 0;
}