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
int n,m;
int a[200100];
int dp[200100];
int q[200100],head = 1,tail = 0;
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    //dp[i] : i chosen min value.
    //dp[i] = a[i] + min(dp[i-1],dp[i-m])
    memset(dp,0x3f,sizeof(dp));
    dp[0] = 0;
    q[++tail] = 0;
    for(int i = 1;i<=n;++i)
    {
        while(tail >= head && dp[q[tail]] >= dp[i])
            --tail;
        q[++tail] = i;
        while(tail >= head && q[tail] - q[head] + 1 > m)
            ++head;
        dp[i+1] = dp[q[head]] + a[i+1];
    }
    int ans = 1<<30;
    for(int i = n-m+1;i<=n;++i)
        if(dp[i] < ans)
            ans = dp[i];
    printf("%d",ans);
    return 0;
}