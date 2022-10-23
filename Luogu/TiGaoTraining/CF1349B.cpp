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
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100;
int T, n, a[maxn], k;
int main()
{
    read(T);
    while (T--)
    {
        read(n), read(k);
        bool vis = 0;
        for (int i = 1; i <= n + 10; ++i) a[i] = 0;
        for (int i = 1; i <= n; ++i) read(a[i]), vis |= (a[i] == k);
        if (!vis) { puts("no"); continue; }
        if (n == 1 && a[1] == k) { puts("yes"); goto end; }
        a[0] = a[n + 1] = 0;
        for (int i = 1; i <= n; ++i)
            if (a[i] == k && (a[i - 1] >= k || a[i + 1] >= k)) { puts("yes"); goto end; }
        for (int i = 1; i <= n; ++i)
            if ((a[i] >= k && a[i + 2] >= k) || (a[i] >= k && a[i + 1] >= k)) { puts("yes"); goto end; }
        puts("no");
        continue;
        end:;
    }
    return 0;
}