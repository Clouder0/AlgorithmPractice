#include <algorithm>
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
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 19;
const int maxs = 1 << 20;
int n, m, a[maxn], num[maxs], f[maxs];
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) num[1 << (i - 1)] = i, a[i] |= 1 << (i - 1);
    for (int i = 1, x, y; i <= m; ++i) read(x), read(y), a[x] |= 1 << (y - 1), a[y] |= 1 << (x - 1);
    int maxx = 1 << n;
    for (int i = 1; i < maxx; ++i) f[i] = n;
    for (int i = 1; i < maxx; ++i)
    {
        for (int j = i; j; --j &= i) if ((~a[num[j & -j]]) & i) goto no;
        f[i] = 1;
    no:;
    }
    for (int i = 1; i < maxx; ++i) for (int j = i; j; --j&=i) f[i] = std::min(f[i], f[j] + f[i ^ j]);
    printf("%d\n", f[maxx - 1]);
    return 0;
}