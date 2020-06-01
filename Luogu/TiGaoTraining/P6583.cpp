#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1000000;
long long n,ans;
long long a[maxn],tot;
inline long long calc(long long x)
{
    return x - x / 2 - x / 5 + x / 10;
}
int main()
{
    read(n);
    for(long long i = 1;i<=n;i<<=1)
        for(long long j = 1;i*j<=n;j*=5)
            a[++tot] = i*j;
    std::sort(a+1,a+1+tot);
    long long w1,w2;
    for(long long i = 1;i<=n;i = w2 + 1)
    {
        w1 = n / i,w2 = n / w1;
        while(a[tot] > w1 && tot) --tot;
        ans = ans + w1 * (calc(w2) - calc(i - 1)) * tot;
    }
    printf("%lld",ans);
    return 0;
}