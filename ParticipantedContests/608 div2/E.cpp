#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
long long n,k;
inline bool check(long long p)
{
    long long ll = p,rr = p,ans = 0;
    if(!(p & 1)) ++rr;
    while(ll <= n)
    {
        ans += min(n,rr) - ll + 1;
        ll <<= 1;
        rr = (rr<<1) + 1;
    }
    return ans >= k;
}
int main()
{
    read(n);
    read(k);
    long long ll = 1,rr = (n+1)>>1,mid,ans = 1;
    while(ll<=rr)
    {
        mid = (ll+rr)>>1;
        if(check((mid<<1)-1))
        {
            ans = (mid<<1) - 1;
            ll = mid + 1;
        }
        else
            rr = mid - 1;
    }
    ll = 1,rr = n>>1;
    long long ans2 = 1;
    while(ll<=rr)
    {
        mid = (ll+rr)>>1;
        if(check(mid<<1))
        {
            ans2 = mid<<1;
            ll = mid + 1;
        }
        else
            rr = mid - 1;
    }
    printf("%lld",max(ans,ans2));
    return 0;
}