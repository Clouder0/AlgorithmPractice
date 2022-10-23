#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
inline long long get(long double a, long double b)
{
    long long mid = (long double)b / (-a * 2);
    long long ans = mid * mid * a + b * mid;
    ++mid;
    return max(ans,1ll *  (mid * mid * 1ll * a + 1ll * b * mid));
}

int main()
{
    int T;
    read(T);
    while (T--)
    {
        int a, b, c, d;
        read(a), read(b), read(c), read(d);
        if (d > c)
        {
            if (a <= 1ll * b * c) printf("%d\n", a); else puts("-1");
        }
        else
        {
            if (a > 1ll * b * c) puts("-1"); else printf("%lld\n", 1ll * get((long double)-d * b, (long double)d * b + a + a) / 2);
        }
    }
}