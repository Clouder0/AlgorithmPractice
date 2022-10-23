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
long long a[maxn], sum[maxn], n, m;
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]), sum[i] = sum[i - 1] + a[i];
    long long now = 0;
    for (int i = 1; i <= m; ++i) now += i * a[i];
    long long ans = now;
    for (int i = m + 1; i <= n; ++i) now -= sum[i - 1] - sum[i - m - 1], now += m * a[i], ans = std::max(ans, now);
    printf("%lld\n", ans);
    return 0;
}