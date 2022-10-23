#include <cstdio>
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
template <typename T>
inline T read(T &r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c);)
        c = nc();
    for (; isdigit(c); c = nc())
        r = r * 10 + c - 48;
    return r;
}
int T, n, r;
int main()
{
    read(T);
    while (T--)
    {
        long long ans = 0;
        read(n), read(r);
        if (r >= n)
            r = n - 1, ans = 1ll * r * (r + 1) / 2 + 1;
        else
            ans = 1ll * r * (r + 1) / 2;
        printf("%lld\n", ans);
    }
    return 0;
}