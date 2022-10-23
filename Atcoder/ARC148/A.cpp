#include <algorithm>
#include <cstdio>
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
const int maxn = 2e5 + 100;
int n, a[maxn], has[maxn], cnt;
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    std::sort(a + 1, a + 1 + n);
    n = std::unique(a + 1, a + 1 + n) - a - 1;
    if (n == 1) goto one;
    for (int i = n; i; --i) a[i] = a[i] - a[i - 1];
    for (int i = 2; i * i <= a[2]; ++i)
        if ((a[2] % i) == 0) has[++cnt] = i, has[++cnt] = a[2] / i;
    if (a[2] >= 2) has[++cnt] = a[2];
    for (int i = 2; i <= n; ++i) a[i] += a[i - 1];
    for (int m = 1; m <= cnt; ++m)
    {
        
        int t = a[1] % has[m];
        for (int i = 2; i <= n; ++i)
            if ((a[i] % has[m]) != t)
                goto fail;
//        printf("m:%d\n",has[m]);
        puts("1");
        return 0;
    fail:;
    }
    goto no;
one:
    puts("1");
    return 0;
no:
    puts("2");
    return 0;
}