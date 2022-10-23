#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
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
int n;
template<typename T>
inline T _gcd(T a,T b)
{
    if (a < b) std::swap(a, b);
    return b == 0 ? a : _gcd(b, a % b);
}
struct fraction
{
    long long x,y;
    fraction() {}
    fraction(long long _x, long long _y)
    {
        x = _x, y = _y;
        fix();
    }
    void fix()
    {
        long long g = _gcd(x, y);
        x /= g, y /= g;
    }
    fraction operator+(fraction b)
    {
        fraction c;
        long long g = y / _gcd(y,b.y) * b.y;
        long long t1 = g / y,t2 = g / b.y;
        c.x = x * t1 + b.x * t2;
        c.y = g;
        c.fix();
        return c;
    }
};
int main()
{
    read(n);
    fraction a(n,1);
    for (int i = 2; i <= n; ++i) a = a + fraction(n, i);
    long long left = a.x / a.y;
    a.x -= left * a.y;
    if(a.x == 0)
    {
        printf("%lld\n",left);
        return 0;
    }
    int leftlen = 0,ylen = 0;
    for (long long x = left; x; x /= 10) ++leftlen;
    for (long long x = a.y; x; x /= 10) ++ylen;
    for (int i = 1; i <= leftlen; ++i) putchar(' ');
    printf("%lld\n",a.x);
    printf("%lld", left);
    for (int i = 1; i <= ylen; ++i) putchar('-');
    putchar('\n');
    for (int i = 1; i <= leftlen; ++i) putchar(' ');
    printf("%lld", a.y);
    return 0;
}