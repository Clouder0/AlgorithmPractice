#include <cmath>
#include <cstdio>
#include <ctype.h>
#define int long long
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c); c = nc()) ;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
int a, m, b;
inline int euler(int x)
{
    int top = std::sqrt(x);
    int res = x;
    for (int i = 2; i <= top; ++i)
    {
        if ((x % i) == 0)
        {
            res = res / i * (i - 1);
            while ((x % i) == 0) x /= i;
        }
    }
    if (x != 1) res = res / x * (x - 1);
    return res;
}
inline int mul(int x, int y)
{
    int res = 0;
    for (; y > 0; y >>= 1)
    {
        if (y & 1) res = (res + x) % m;
        x = (x + x) % m;
    }
    if (res < 0) res += m;
    return res;
}
inline int fastpow(int x, int k)
{
    int res = 1;
    for (; k; k >>= 1)
    {
        if (k & 1) res = mul(res, x);
        x = mul(x, x);
    }
    return res;
}
signed main()
{
    read(a), read(m);
    int phi = euler(m);
    static char c;
    b = 0;
    for (c = nc(); !isdigit(c); c = nc());
    bool flag = 0;
    for (; isdigit(c); c = nc())
    {
        b = b * 10 + c - 48;
        if (b >= phi) b %= phi, flag = 1;
    }
    printf("%lld\n", fastpow(a, b + phi * flag));
    return 0;
}