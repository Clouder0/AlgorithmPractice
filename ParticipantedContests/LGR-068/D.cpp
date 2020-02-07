#include <cstdio>
#include <cmath>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int mod = 998244353;
int T;
int n,k;
inline long long fastpow(long long x,int k)
{
    long long res = 1,base = x;
    while(k)
    {
        if(k&1)
            res *= base;
        base *= base;
        k >>= 1;
    }
    return res;
}
long long ans;
int main()
{
    read(T);
    while(T--)
    {
        ans = 0;
        read(n);
        read(k);
        for(int i = 1;i<=n;++i)
        {
            long long x = fastpow(i,k);
            for(long long j = 1;j*j<=x;++j)
                if(x % j == 0)
                    ans += 2;
            long long sx = sqrt(x);
            if(sx*sx == x)
                --ans;
            ans %= mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}