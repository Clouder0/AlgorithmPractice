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
const int maxn = 5e4 + 10;
int n,t;
int a[maxn];
int q[maxn],head,tail;
int dp[maxn];
inline bool check(int len)
{
    memset(dp,0x3f,sizeof(dp));
    head = 1,tail = 0;
    // [i-len,i] -> i+1
    dp[0] = 0;
    q[++tail] = 0;
    dp[1] = a[1];
    for(int i = 1;i<=n;++i)
    {
        while(tail >= head && dp[q[tail]] >= dp[i])
            --tail;
        q[++tail] = i;
        while(tail >= head && q[tail] - q[head] > len)
            ++head;
        dp[i+1] = dp[q[head]] + a[i+1];
    }
    int ans = 1<<30;
    for(int i = n-len;i<=n;++i)
        if(dp[i] < ans)
            ans = dp[i];
    return ans <= t;
}
int main()
{
    read(n);
    read(t);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    int ll = 0,rr = n,mid,ans;
    while(ll <= rr)
    {
        mid = (ll+rr)>>1;
        if(check(mid))
        {
            rr = mid - 1;
            ans = mid;
        }
        else
            ll = mid + 1;
    }
    printf("%d",ans);
    return 0;
}