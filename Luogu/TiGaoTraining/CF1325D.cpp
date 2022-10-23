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
long long u, v;
int main()
{
    read(u), read(v);
    if (u == v && v == 0) { puts("0"); goto end; }
    if (u > v) { puts("-1"); goto end; }
    if (u == v) { puts("1"); printf("%lld\n", u); goto end; }
    v -= u;
    if ((v & 1) == 0) 
    {
        v >>= 1;
        if ((v & u) == 0) u |= v, puts("2"), printf("%lld %lld\n", u, v);
        else puts("3"), printf("%lld %lld %lld\n", u, v, v);
        goto end;
    }
    puts("-1");
end:
    return 0;
}