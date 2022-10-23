#include <cstdio>
using namespace std;
long long k, l, p;
long long s, w;
long long fastpow(long long x, long long t)
{
    long long res = 1, base = x;
    while (t)
    {
        if (t & 1)
            res = (res * base) % p;
        base = (base * base) % p;
        t >>= 1;
    }
    return res;
}
int main()
{
    scanf("%lld %lld %lld %lld %lld", &k, &l, &p, &s, &w);
    long long res = 1;
    if (l >= 1)
        res = (res * (k % p)) % p;
    if (l >= 2)
        res = (res * ((k - 1) % p)) % p;
    res = (res * fastpow((k - 2) % p, l - 2)) % p;
    if (s != 0)
        res = (res * fastpow(k % p, p - 2)) % p;
    printf("%lld", res);
    return 0;
}