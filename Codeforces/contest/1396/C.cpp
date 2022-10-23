#include <cstdio>
#include <cstring>
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
const int maxn = 1e6 + 100;
int n,r1,r2,r3,d;
int a[maxn];
long long f[maxn][2];
int main()
{
    read(n), read(r1), read(r2), read(r3), read(d);
    for (int i = 1; i <= n; ++i) read(a[i]);
    memset(f, 0x3f, sizeof(f));
    f[1][0] = 1ll * a[1] * r1 + r3;
    f[1][1] = std::min(1ll * a[1] * r1 + r1, 1ll * r2);
    for (int i = 1; i < n; ++i)
    {
        // 1 2 3
        f[i + 1][0] = std::min(f[i + 1][0], f[i][0] + d + 1ll * r1 * a[i + 1] + r3);
        f[i + 1][0] = std::min(f[i + 1][0], f[i][1] + d + std::min(1ll * r1 * a[i + 1] + r1, 1ll * r2) + d + r1 + d + r1);
        f[i + 1][1] = std::min(f[i + 1][1], f[i][0] + d + std::min(1ll * a[i + 1] * r1 + r1, 1ll * r2));
        f[i + 1][1] = std::min(f[i + 1][1], f[i][1] + d + std::min(1ll * r1 * a[i + 1] + r1, 1ll * r2) + d + r1 + d);
        if (i == n - 1) f[n][0] = std::min(f[n][0], f[n - 1][1] + d + 1ll * a[n] * r1 + r3 + d + r1);
    }
    printf("%lld\n", f[n][0]);
    return 0;
}