#include <cstdio>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());r*=flag;
}
const int maxn = 5e5 + 10;
int n,d,k;
int x[maxn],s[maxn];
int q[maxn],head = 1,tail;
long long dp[maxn];
inline bool check(int g)
{
    memset(dp,~0x3f,sizeof(dp));
    head = 1, tail = 0;
    int ll = d-g>1?d-g:1;
    int rr = d+g;
    //i <- [i-rr,i-ll]
    dp[0] = 0;
    int p = 0;
    for (int i = 1; i <= n; ++i)
    {
        while(x[p] < x[i] - rr)
            ++p;
        while(x[p] <= x[i] - ll)
        {
            while (tail >= head && dp[q[tail]] <= dp[p])
                --tail;
            q[++tail] = p;
            ++p;
        }
        while (tail >= head && x[q[head]] < x[i] - rr)
            ++head;
        if(tail >= head)
            dp[i] = dp[q[head]] + s[i];
        if(dp[i] >= k)
            return true;
    }
    return false;
}
int main()
{
    read(n);
    read(d);
    read(k);
    for(int i = 1;i<=n;++i)
        read(x[i]),read(s[i]);
    int ll = 0,rr = x[n]>d?x[n]:d,mid,ans = -1;
    while(ll <= rr)
    {
        mid = (ll+rr)>>1;
        if(check(mid))
        {
            ans = mid;
            rr = mid - 1;
        }
        else
            ll = mid + 1;
    }
    printf("%d",ans);
    return 0;
}