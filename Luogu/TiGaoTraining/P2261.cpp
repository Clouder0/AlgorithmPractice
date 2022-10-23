#include <cstdio>
#define int long long
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,k;
long long ans;
signed main()
{
    read(n),read(k);
    ans = n * k;
    int l,r = 0,t;
    for(l = 1;l<=n;l = r + 1)
    {
        t = k / l;
        if(t == 0) r = n;
        else r = k / t > n ? n : k / t;
        ans -= t * (r - l + 1) * (l + r) >> 1;
    }
    printf("%lld",ans);
    return 0;
}