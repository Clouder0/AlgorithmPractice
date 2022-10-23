#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
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
const int maxn = 2e5 + 100;
int n, a[maxn], b[maxn],res;
signed main()
{
    read(n);
    long long now = 0;
    for (int i = 1; i <= n; ++i) read(a[i]),read(b[i]),now -= a[i],a[i] = b[i] + 2 * a[i];
    std::sort(a + 1,a + 1 + n);
    for(int i = n;i;--i)
    {
        if (now > 0) { printf("%lld\n", res); return 0; }
        now += a[i], ++res;
    }
    printf("%lld\n", res);
    return 0;
}