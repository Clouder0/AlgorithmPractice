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
const int maxn = 5100;
int n, m, q, x, y, s, t, a[maxn][maxn];
const int mod = 998244353;
int main()
{
    read(n), read(m),read(q);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (((i + j) & 1) == 0) a[i][j] = (i - 1) * m + j;
    while(q--)
    {
        read(x),read(y),read(s),read(t);
        long long res = 0;
        for (int i = x; i <= y; ++i)
            for (int j = s; j <= t; ++j) res = (res + a[i][j]) % mod;
        printf("%lld\n", res);
    }
    return 0;
}