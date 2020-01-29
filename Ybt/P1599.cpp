#include <cstdio>
using namespace std;
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
const int maxn = 1e5 + 10;
int n,k;
int a[maxn];
long long sum[maxn];
long long dp[maxn];
long long q[maxn];
int head = 1,tail;
int main()
{
    read(n);
    read(k);
    for(int i =1;i<=n;++i)
        read(a[i]),sum[i] = sum[i-1] + a[i];
    for(int i = 1;i<=k;++i)
    {
        dp[i] = sum[i];
        while(tail>=head && dp[i-1] - sum[i] >= dp[q[tail] - 1] - sum[q[tail]])
            --tail;
        q[++tail] = i;
        while(tail>=head && q[tail] - q[head] + 1 > k)
            ++head;
    }
    for(int i = k+1;i<=n;++i)
    {
        dp[i] = dp[q[head]-1] - sum[q[head]] + sum[i];
        while(tail>=head && dp[i-1] - sum[i] >= dp[q[tail] - 1] - sum[q[tail]])
            --tail;
        q[++tail] = i;
        while(tail>=head && q[tail] - q[head] + 1 > k)
            ++head;
    }
    //dp[i] = max(dp[p-1] - sum[p]) + sum[i] p in [i-k,i-1]
    printf("%lld",dp[n]);
    return 0;
}