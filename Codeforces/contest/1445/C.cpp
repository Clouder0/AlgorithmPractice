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
int T;
long long p, q;
long long fastpow(long long x,long long k)
{
    long long res = 1;
    while(k)
    {
        if(k & 1) res = res * x;
        x = x * x;
        k >>= 1;
    }
    return res;
}
int main()
{
    read(T);
    while(T--)
    {
        read(p), read(q);
        long long res = 0;
        for (int i = 2; 1ll * i * i <= q; ++i)
        {
            if ((q % i) == 0)
            {
                int times = 0;
                while ((q % i) == 0) q /= i, ++times;
                int ptimes = 0;
                long long x = p;
                while ((x % i) == 0) x /= i, ++ptimes;
                if (ptimes < times) { res = p; break; }
                else res = std::max(res, x * fastpow(i, times - 1));
            }
        }
        if(q != 1)
        {
            int times = 1;
            int ptimes = 0;
            long long x = p;
            while ((x % q) == 0) x /= q, ++ptimes;
            if (ptimes < times) res = p;
            else res = std::max(res, x * fastpow(q, times - 1));
        }
        printf("%lld\n", res);
    }
    return 0;
}