#include <cstdio>
#include <algorithm>
#include <ctype.h>
#include <cmath>
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
#define int long long
int T, p, q;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
signed main()
{
    read(T);
    while(T--)
    {
        read(p), read(q);
        int g = gcd(p, q), t, sq, a,b;
        p /= g, q /= g;
        if (p * p < 4 * q * q) goto no;
        t = p * p - 4 * q * q;
        sq = std::sqrt(t);
        if(sq * sq == t) goto yes;
        --sq;
        if(sq * sq == t) goto yes;
        sq += 2;
        if(sq * sq == t) goto yes;
        goto no;
        yes:
        a = p + sq;
        b = 2 * q;
        g = gcd(a,b);
        a /= g, b /= g;
        printf("%lld %lld\n", a, b);
        continue;
        no:
        puts("0 0");
        continue;
    }
    return 0;
}