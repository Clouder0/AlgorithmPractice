#include <cstdio>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());r *= flag;
}
int n,l,r;
int a[201000];
int q[201000],head = 1,tail = 0;
int dp[201000];
int main()
{
    read(n);
    read(l);
    read(r);
    ++n;
    for(int i = 1;i<=n;++i)
        read(a[i]);
    // i-> max in [i-r,i-l]
    // [i-r+l,i] -> i+l
    // i - i + r - l = r - l
    memset(dp,~0x3f,sizeof(dp));
    dp[1] = 0;
    for(int i = 1;i+l<=n;++i)
    {
        while(tail >= head && dp[q[tail]] <= dp[i])
            --tail;
        q[++tail] = i;
        while(tail >= head && q[tail] - q[head] > r - l)
            ++head;
        dp[i+l] = dp[q[head]] + a[i+l];
    }
    int ans = 0;
    for(int i = n-r+1;i<=n;++i)
        if(dp[i] > ans)
            ans = dp[i];
    printf("%d",ans);
    return 0;
}