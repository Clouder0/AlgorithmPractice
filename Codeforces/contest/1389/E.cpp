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
inline long long gcd(long long a,long long b)
{
    if(a < b) std::swap(a,b);
    return b == 0 ? a : gcd(b,a%b);
}
int T;
long long m,d,w;
int main()
{
    read(T);
    while(T--)
    {
        read(m), read(d), read(w);
        long long w2 = w / gcd(d - 1, w);
        long long t = std::min(d, m) - 1;
        long long g = t / w2;
        long long ans = g * (t + 1) - g * (g + 1) * w2 / 2;
        printf("%lld\n", ans);
    }
    return 0;
}