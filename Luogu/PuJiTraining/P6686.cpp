#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 4e5 + 100;
const int mod = 998244353;
int n;
long long a[maxn],cnt[maxn],sum[maxn];
inline long long mul(const long long a,const long long b){return (a * b) % mod;}
inline long long add(const long long a,const long long b){return (a + b) % mod;}
inline long long fastpow(long long x,long long k)
{
    long long res = 1;
    for(;k;k>>=1)
    {
        if(k & 1) res = mul(res,x);
        x = mul(x,x);
    }
    return res;
}
int main()
{
    read(n);
    long long maxx = 0;
    for (int i = 1; i <= n; ++i) read(a[i]), cnt[a[i]]++,maxx = std::max(maxx,a[i]);
    for(int i = 1;i<=maxx*2;++i) sum[i] = sum[i-1] + cnt[i];
    long long ans = 0;
    long long inv = fastpow(6,mod - 2),inv2 = fastpow(2,mod - 2);
    for (int i = 1; i <= maxx; ++i) 
    {
        if (cnt[i] > 2)
            ans = add(ans, mul(mul(mul(cnt[i], cnt[i] - 1), cnt[i] - 2),inv));
        ans = add(ans, mul(mul(mul(cnt[i],cnt[i] - 1),inv2),sum[i * 2 - 1] - cnt[i]));
    }
    printf("%lld\n",ans);
    return 0;
}