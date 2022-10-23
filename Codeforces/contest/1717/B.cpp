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
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc())
        ;
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
int T, n, k, r, c;
const int maxn = 510;
int a[maxn][maxn], mark[maxn];
int main()
{
    read(T);
    while (T--)
    {
        read(n), read(k), read(r), read(c);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) a[i][j] = 0;
        for (int i = 0; i <= 3 * n; ++i) mark[i] = 0;
        int p = c;
        for (int i = 1; i <= n / k; ++i)
        {
            mark[p - r + n] = 1;
            if (p - r > 0) mark[p - r] = 1;
            else mark[p - r + 2 * n] = 1;
            p = p + k;
            if (p > n) p -= n;
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) a[i][j] = mark[j - i + n];
        for (int i = 1; i <= n; puts(""), ++i)
            for (int j = 1; j <= n; ++j) putchar(a[i][j] ? 'X' : '.');
    }
    return 0;
}