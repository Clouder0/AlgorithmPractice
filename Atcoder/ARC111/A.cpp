#include <cstdio>
long long n, m;
long long mod;
inline long long mul(long long a,long long b){return a * b % mod;}
inline long long add(long long a, long long b) { long long t = a + b; return t >= mod ? t - mod : mod; }
long long fastpow(long long x,long long k) 
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
    scanf("%lld %lld", &n, &m);
    mod = m * m;
    printf("%lld\n", fastpow(10, n) / m % m);
    return 0;
}